#pragma once

// Unfortunately, some applications drop or misorder fast key events. This is a
// partial fix to slow down the rate at which macros are sent.
#define TAP_CODE_DELAY 5

// Tap-hold configuration for home row mods (same tuning as getreuer's keymap).
// https://docs.qmk.fm/tap_hold
#define TAPPING_TERM 240
#define TAPPING_TERM_PER_KEY  // See get_tapping_term() in lakes26.c.
#define FLOW_TAP_TERM 100     // See get_flow_tap_term() in lakes26.c.
#define CHORDAL_HOLD          // Handedness map: chordal_hold_layout in keymap.c.
#define PERMISSIVE_HOLD
#define SPECULATIVE_HOLD      // See get_speculative_hold() in lakes26.c.
#define SPECULATIVE_HOLD_ONE_KEY
#define SPECULATIVE_HOLD_FLOW_TERM 200
#define QUICK_TAP_TERM_PER_KEY  // See get_quick_tap_term() in lakes26.c.

// Speculative Hold may send a lone Alt or GUI press and release. Tap a dummy
// key in between so that this doesn't e.g. open GNOME Activities, the Windows
// Start menu, or focus an app's menu bar. (Harmless on macOS.)
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RCTL
#define MODS_TO_NEUTRALIZE                          \
  { MOD_BIT(KC_LALT), MOD_BIT(KC_LGUI),             \
    MOD_BIT(KC_RALT), MOD_BIT(KC_RGUI) }

// Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_INVERT_ON_SHIFT
// When idle, turn off Layer Lock after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000

// Cyclotab: tapping the app switcher holds Cmd/GUI for a moment, so you can
// tap repeatedly to cycle; the next other key press completes the switch.
#define CYCLOTAB_KEYS G(KC_TAB)

// Speed curve for Orbital Mouse (getreuer's).
#define ORBITAL_MOUSE_SPEED_CURVE \
      {24, 24, 24, 32, 62, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72}
//     |               |               |               |           |
// t = 0.000           1.024           2.048           3.072       3.840 s
