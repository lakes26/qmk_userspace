
// This keymap uses Ikcelaks' Magic Sturdy layout for the base layer (see
// https://github.com/Ikcelaks/keyboard_layouts). I've also made some twists of
// my own. The "magic" is a key whose function depends on the last pressed key,
// implemented using the Alternate Repeat Key. This key is used to remove the
// top SFBs and type common n-grams.
//
// The following describes the magic key functionality, where * represents the
// magic key and @ the repeat key. For example, tapping A and then the magic key
// types "ao". Most of this is coded in my `get_alt_repeat_key_keycode_user()`
// definition below.
//
// SFB removal and common n-grams:
//
//     A * -> AO     L * -> LK      S * -> SK
//     C * -> CY     M * -> MENT    T * -> TMENT
//     D * -> DY     O * -> OA      U * -> UE
//     E * -> EU     P * -> PY      Y * -> YP
//     G * -> GY     Q * -> QUEN    spc * -> THE
//     I * -> ION    R * -> RL
//
// When the magic key types a letter, following it with the repeat key produces
// "n". This is useful to type certain patterns without SFBs.
//
//     A * @ -> AON             (like "kaon")
//     D * @ -> DYN             (like "dynamic")
//     E * @ -> EUN             (like "reunite")
//     O * @ -> OAN             (like "loan")
//
// Other patterns:
//
//     spc * @ -> THEN
//     I * @ -> IONS            (like "nations")
//     M * @ -> MENTS           (like "moments")
//     Q * @ -> QUENC           (like "frequency")
//     T * @ -> TMENTS          (lite "adjustments")
//     = *   -> ===             (JS code)
//     ! *   -> !==             (JS code)
//     " *   -> """<cursor>"""  (Python code)
//     ` *   -> ```<cursor>```  (Markdown code)
//     # *   -> #include        (C code)
//     . *   -> ../             (shell)
//     . * @ -> ../../

enum layers {
    BASE,
    SYM,
    NUM,
    NAV,
    EXT,
    FUN,
};

enum custom_keycodes {
    USRNAME = SAFE_RANGE,
    UPDIR,

    // OS-aware hotkeys: Cmd-based on macOS, Ctrl-based otherwise.
    HK_UNDO,
    HK_CUT,
    HK_COPY,
    HK_PSTE,
    HK_SALL,
    HK_BACK,

    // Macros invoked through the Magic key.
    M_DOCSTR,
    M_EQEQ,
    M_INCLUDE,
    M_ION,
    M_MENT,
    M_MKGRVS,
    M_QUEN,
    M_THE,
    M_TMENT,
    M_UPDIR,
    M_NBSP,
    M_NOOP,
};

#define MAGIC QK_AREP

// Short aliases for home row mods and other tap-hold keys.
#define HOME_S LALT_T(KC_S)
#define HOME_T LCTL_T(KC_T)
#define HOME_R LGUI_T(KC_R)
#define HOME_D LSFT_T(KC_D)
#define HOME_N RSFT_T(KC_N)
#define HOME_E RGUI_T(KC_E)
#define HOME_A RCTL_T(KC_A)
#define HOME_I RALT_T(KC_I)

#define NUM_G LT(NUM, KC_G)
#define NAV_ESC LT(NAV, KC_ESC)
// Tap: ':' (handled in process_record_user), hold: EXT layer.
#define EXT_COL LT(EXT, KC_SCLN)

#define SYMBOLS OSL(SYM)
#define TO_BASE TO(BASE)

// App switcher, handled by Cyclotab (see CYCLOTAB_KEYS in config_lakes26.h).
// Cmd+Tab on macOS, Super+Tab (switch applications) on GNOME.
#define APPSWCH G(KC_TAB)
#define PREVTAB C(S(KC_TAB))  // Previous / next tab in browsers and most apps.
#define NEXTTAB C(KC_TAB)

// Note: get_tap_keycode() (MT/LT keycode -> tap keycode) is provided by QMK
// core since 0.29.0 (quantum/action.h), so it must not be redefined here.

/// Combos
const uint16_t caps_combo[] PROGMEM = {KC_J, KC_COMM, COMBO_END};
const uint16_t f_n_combo[] PROGMEM = {KC_F, HOME_N, COMBO_END};

combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG),    // J and , => activate Caps Word.
    COMBO(f_n_combo, OSL(FUN)),    // F and N => FUN layer (one-shot).
};

///////////////////////////////////////////////////////////////////////////////
// Key Overrides (https://docs.qmk.fm/features/key_overrides), as in getreuer's
// keymap. Shift + , and Shift + . produce ! and ? for easier punctuation; < and
// > remain on the SYM layer.
///////////////////////////////////////////////////////////////////////////////
#ifdef KEY_OVERRIDE_ENABLE
const key_override_t dot_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);  // Shift . is ?
const key_override_t comm_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_EXLM);  // Shift , is !
const key_override_t slsh_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);  // Shift / is backslash
const key_override_t mply_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_MPLY, KC_MNXT);  // Shift play is next

const key_override_t* key_overrides[] = {
    &dot_key_override,
    &comm_key_override,
    &slsh_key_override,
    &mply_key_override,
};
#endif  // KEY_OVERRIDE_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold), following getreuer.
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    // A shorter tapping term for the Shift home row mods makes it easier to
    // type capital letters.
    case HOME_D:
    case HOME_N:
      return TAPPING_TERM - 45;
    default:
      return TAPPING_TERM;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:  // For MT and LT tap-hold keys.
      switch (keycode) {
        case HOME_N:  // Keep key repeat on N, e.g. for "n" in Vim.
          return QUICK_TAP_TERM;
        default:
          return 0;  // Disable Quick Tap for other MT and LT keys.
      }
    default:
      // Enable for tap-hold keys besides MT and LT.
      return QUICK_TAP_TERM;
  }
}

#ifdef FLOW_TAP_TERM
// Flow Tap: when a home row mod is pressed within a short time after a letter,
// it is immediately settled as tapped. This prevents misfires in fast typing.
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode) {
  // Only apply Flow Tap when following a letter key, and not hotkeys.
  if (get_tap_keycode(prev_keycode) <= KC_Z &&
      (get_mods() & MOD_MASK_CAG) == 0) {
    switch (keycode) {
      case HOME_S:
      case HOME_R:
      case HOME_E:
      case HOME_I:
        return FLOW_TAP_TERM;

      case HOME_T:
      case HOME_A:
        return FLOW_TAP_TERM - 25;
    }
  }

  return 0;  // Disable Flow Tap otherwise, including on the Shift keys D, N.
}
#endif  // FLOW_TAP_TERM

#ifdef SPECULATIVE_HOLD
// Speculative Hold applies a mod-tap's modifier immediately on key down, so
// that e.g. Cmd + mouse click doesn't have to wait for the tapping term.
bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {
  return true;  // Enable for all mods.
}
#endif  // SPECULATIVE_HOLD

/// Caps word
#ifdef CAPS_WORD_ENABLE
bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT_LSHIFT);  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case KC_COLN:
    case M_THE:
    case M_ION:
    case M_MENT:
    case M_QUEN:
    case M_TMENT:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}
#endif  // CAPS_WORD_ENABLE

// The following describes the magic key functionality, where * represents the
// magic key and @ the repeat key. For example, tapping A and then the magic key
// types "ao". Most of this is coded in my `get_alt_repeat_key_keycode_user()`
// definition below.
//
// SFB removal and common n-grams:
//
//     A * -> AO     L * -> LK      S * -> SK
//     C * -> CY     M * -> MENT    T * -> TMENT
//     D * -> DY     O * -> OA      U * -> UE
//     E * -> EU     P * -> PY      Y * -> YP
//     G * -> GY     Q * -> QUEN    spc * -> THE
//     I * -> ION    R * -> RL
//
// When the magic key types a letter, following it with the repeat key produces
// "n". This is useful to type certain patterns without SFBs.
//
//     A * @ -> AON             (like "kaon")
//     D * @ -> DYN             (like "dynamic")
//     E * @ -> EUN             (like "reunite")
//     O * @ -> OAN             (like "loan")
//
// Other patterns:
//
//     spc * @ -> THEN
//     I * @ -> IONS            (like "nations")
//     M * @ -> MENTS           (like "moments")
//     Q * @ -> QUENC           (like "frequency")
//     T * @ -> TMENTS          (like "adjustments")
//     = *   -> ===             (JS code)
//     ! *   -> !==             (JS code)
//     " *   -> """<cursor>"""  (Python code)
//     ` *   -> ```<cursor>```  (Markdown code)
//     # *   -> #include        (C code)
//     & *   -> &nbsp;          (HTML code)
//     . *   -> ../             (shell)
//     . * @ -> ../../
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  keycode = get_tap_keycode(keycode);

  // Check if shift is the only mod activated if any.
  if ((mods & ~MOD_MASK_SHIFT) == 0) {
    // This is where most of the "magic" for the MAGIC key is implemented.
    switch (keycode) {
      case KC_SPC:  // spc -> THE
      case KC_ENT:
      case KC_TAB:
        return M_THE;

      // For navigating next/previous search results in Vim:
      // N -> Shift + N, Shift + N -> N.
      case KC_N:
        if ((mods & MOD_MASK_SHIFT) == 0) {
          return S(KC_N);
        }
        return KC_N;

      // Fix SFBs and awkward strokes.
      case KC_A: return KC_O;         // A -> O
      case KC_O: return KC_A;         // O -> A
      case KC_E: return KC_U;         // E -> U
      case KC_U: return KC_E;         // U -> E
      case KC_I:
        if ((mods & MOD_MASK_SHIFT) == 0) {
          return M_ION;  // I -> ON
        } else {
          return KC_QUOT;  // Shift I -> '
        }
      case KC_M: return M_MENT;       // M -> ENT
      case KC_Q: return M_QUEN;       // Q -> UEN
      case KC_T: return M_TMENT;      // T -> TMENT

      case KC_C: return KC_Y;         // C -> Y
      case KC_D: return KC_Y;         // D -> Y
      case KC_G: return KC_Y;         // G -> Y
      case KC_P: return KC_Y;         // P -> Y
      case KC_Y: return KC_P;         // Y -> P

      case KC_L: return KC_K;         // L -> K
      case KC_S: return KC_K;         // S -> K

      case KC_R: return KC_L;         // R -> L
      case KC_DOT:
        if ((mods & MOD_MASK_SHIFT) == 0) {
          return M_UPDIR;  // . -> ./
        }
        return M_NOOP;
      case KC_HASH: return M_INCLUDE;  // # -> include
      case KC_AMPR: return M_NBSP;     // & -> nbsp;
      case KC_EQL: return M_EQEQ;      // = -> ==
      case KC_AT: return USRNAME;      // @ -> <username>
      case KC_COMM:
        if ((mods & MOD_MASK_SHIFT) != 0) {
          return KC_EQL;  // ! -> = (Shift , is ! via key override)
        }
        return M_NOOP;
      case KC_QUOT:
        if ((mods & MOD_MASK_SHIFT) != 0) {
          return M_DOCSTR;  // " -> ""<cursor>"""
        }
        return KC_T;
      case KC_DQUO:  // " typed from the SYM layer (KC_DQUO, not Shift+').
        return M_DOCSTR;  // " -> ""<cursor>"""
      case KC_GRV:  // ` -> ``<cursor>``` (for Markdown code)
        return M_MKGRVS;
      case KC_SLSH:
        return KC_SLSH;  // / -> / (easier reach than Repeat)

      case KC_F:
      case KC_V:
      case KC_X:
      case KC_SCLN:
      case KC_1 ... KC_0:
        return M_NOOP;
    }
  }

  // Magic after mouse wheel or Select Word reverses the direction.
  switch (keycode) {
    case MS_WHLU: return MS_WHLD;
    case MS_WHLD: return MS_WHLU;
#ifdef COMMUNITY_MODULE_SELECT_WORD_ENABLE
    case SELWBAK: return SELWORD;
    case SELWORD: return SELWBAK;
#endif  // COMMUNITY_MODULE_SELECT_WORD_ENABLE
  }

  return KC_TRNS;
}

////////////////////////////////////////////////////////////////////////////////
// OS-aware hotkeys
////////////////////////////////////////////////////////////////////////////////
// True when the host is detected as macOS/iOS, in which case Cmd is used for
// shortcuts like copy and paste instead of Ctrl.
static bool host_is_mac(void) {
#ifdef OS_DETECTION_ENABLE
  switch (detected_host_os()) {
    case OS_MACOS:
    case OS_IOS:
      return true;
    default:
      break;
  }
#endif  // OS_DETECTION_ENABLE
  return false;
}

// Maps an HK_* keycode to the hotkey for the current host OS.
static uint16_t os_hotkey(uint16_t keycode) {
  const bool mac = host_is_mac();
  switch (keycode) {
    case HK_UNDO: return mac ? G(KC_Z) : C(KC_Z);
    case HK_CUT:  return mac ? G(KC_X) : C(KC_X);
    case HK_COPY: return mac ? G(KC_C) : C(KC_C);
    case HK_PSTE: return mac ? G(KC_V) : C(KC_V);
    case HK_SALL: return mac ? G(KC_A) : C(KC_A);
    case HK_BACK: return mac ? G(KC_LBRC) : A(KC_LEFT);  // Browser back.
  }
  return KC_NO;
}

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`. This helper is
// used for several macros below in my process_record_user() function.
#define MAGIC_STRING(str, repeat_keycode) \
  magic_send_string_P(PSTR(str), (repeat_keycode))
static void magic_send_string_P(const char* str, uint16_t repeat_keycode) {
  uint8_t saved_mods = 0;
  // If Caps Word is on, save the mods and hold Shift.
  if (is_caps_word_on()) {
    saved_mods = get_mods();
    register_mods(MOD_BIT_LSHIFT);
  }

  send_string_P(str);  // Send the string.
  set_last_keycode(repeat_keycode);

  // If Caps Word is on, restore the mods.
  if (is_caps_word_on()) {
    set_mods(saved_mods);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Process User Record
////////////////////////////////////////////////////////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  const uint8_t mods = get_mods();
  const uint8_t all_mods = (mods | get_weak_mods());

  const uint8_t shift_mods = all_mods & MOD_MASK_SHIFT;

  // If alt repeating key A, E, I, O, U, Y with no mods other than Shift, set
  // the last key to KC_N. Above, alternate repeat of KC_N is defined to be
  // again KC_N. This way, either tapping alt repeat and then repeat (or
  // equivalently double tapping alt repeat) is useful to type certain patterns
  // without SFBs:
  //
  //   D <altrep> <rep> -> DYN (as in "dynamic")
  //   O <altrep> <rep> -> OAN (as in "loan")
  if (get_repeat_key_count() < 0 && !shift_mods &&
      (keycode == KC_A || keycode == KC_E || keycode == KC_I ||
       keycode == KC_O || keycode == KC_U || keycode == KC_Y)) {
    set_last_keycode(KC_N);
    set_last_mods(0);
  }

  switch (keycode) {
    // Hold behavior: switches to EXT layer.
    // Tap behavior: types ':' (LT() can't take a shifted keycode directly).
    case EXT_COL:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16_delay(KC_COLN, TAP_CODE_DELAY);
        }
        return false;
      }
      return true;

    case HK_UNDO ... HK_BACK:  // OS-aware hotkeys.
      if (record->event.pressed) {
        register_code16(os_hotkey(keycode));
      } else {
        unregister_code16(os_hotkey(keycode));
      }
      return false;
  }

  if (record->event.pressed) {
    switch (keycode) {
      case UPDIR:
        SEND_STRING_DELAY("../", TAP_CODE_DELAY);
        return false;

      case USRNAME:
        SEND_STRING_DELAY("ericlagos", TAP_CODE_DELAY);
        return false;

      // Macros invoked through the MAGIC key.
      case M_THE:
        // Only capitalize first letter of 'the' when shifted.
        if (shift_mods) {
          MAGIC_STRING(/* */"The", KC_N); break;
        } else {
          MAGIC_STRING(/* */"the", KC_N); break;
        }
      case M_ION:     MAGIC_STRING(/*i*/"on", KC_S); break;
      case M_MENT:    MAGIC_STRING(/*m*/"ent", KC_S); break;
      case M_QUEN:    MAGIC_STRING(/*q*/"uen", KC_C); break;
      case M_TMENT:   MAGIC_STRING(/*t*/"ment", KC_S); break;
      case M_UPDIR:   MAGIC_STRING(/*.*/"./", UPDIR); break;
      case M_INCLUDE: SEND_STRING_DELAY(/*#*/"include ", TAP_CODE_DELAY); break;
      case M_EQEQ:    SEND_STRING_DELAY(/*=*/"==", TAP_CODE_DELAY); break;
      case M_NBSP:    SEND_STRING_DELAY(/*&*/"nbsp;", TAP_CODE_DELAY); break;
      case M_DOCSTR:
        SEND_STRING_DELAY(/*"*/"\"\"\"\"\""
            SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT), TAP_CODE_DELAY);
        break;
      case M_MKGRVS:
        SEND_STRING_DELAY(/*`*/"``\n\n```" SS_TAP(X_UP), TAP_CODE_DELAY);
        break;
    }
  }

  return true;
}


