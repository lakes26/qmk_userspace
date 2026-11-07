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

// RGB lighting: Lumino (brightness control) + PaletteFx (palette-based effects),
// configured as in getreuer's keymap.
#define LUMINO_TRANSITION 850
#define LUMINO_BOOT_COLOR RGB_WHITE
#define LUMINO_NO_EEPROM

#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES

#ifdef RGB_MATRIX_ENABLE
// Since we have PaletteFx, disable the built-in RGB Matrix effects.
#  undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#  undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#  undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#  undef ENABLE_RGB_MATRIX_BREATHING
#  undef ENABLE_RGB_MATRIX_BAND_SAT
#  undef ENABLE_RGB_MATRIX_BAND_VAL
#  undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#  undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#  undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#  undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#  undef ENABLE_RGB_MATRIX_CYCLE_ALL
#  undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#  undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#  undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#  undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#  undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#  undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#  undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#  undef ENABLE_RGB_MATRIX_DUAL_BEACON
#  undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#  undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#  undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#  undef ENABLE_RGB_MATRIX_RAINDROPS
#  undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#  undef ENABLE_RGB_MATRIX_HUE_BREATHING
#  undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#  undef ENABLE_RGB_MATRIX_HUE_WAVE
#  undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#  undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#  undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#  undef ENABLE_RGB_MATRIX_STARLIGHT
#  undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#  undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#  undef ENABLE_RGB_MATRIX_RIVERFLOW

#  undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#  undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#  undef ENABLE_RGB_MATRIX_SPLASH
#  undef ENABLE_RGB_MATRIX_MULTISPLASH
#  undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#  undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif  // RGB_MATRIX_ENABLE
