// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "voyager.h"
#include "layout.h"
#include "lakes26.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    XXXXXXX, XXXXXXX, XXXXXXX, KC_DOWN, KC_UP  , XXXXXXX,
    KC_TAB , KC_V   , KC_M   , KC_L   , KC_C   , KC_P   ,
    KC_BSPC, HOME_S , HOME_T , HOME_R , HOME_D , KC_Y   ,
    KC_COLN, KC_X   , KC_K   , KC_J   , NUM_G  , KC_W   ,
                                                 KC_SPC , KC_ESC ,

                      XXXXXXX, KC_LEFT, KC_RGHT , XXXXXXX, XXXXXXX, XXXXXXX,
                      KC_B   , MAGIC  , KC_U   , KC_O   , KC_Q   , KC_SLSH,
                      KC_F   , HOME_N , HOME_E , HOME_A , HOME_I , XXXXXXX,
                      KC_Z   , KC_H   , KC_COMM, KC_DOT , KC_SCLN, KC_ENT ,
             QK_REP , SYMBOLS
  ),
  [SYM] = LAYOUT_LR(
    KC_GRV , KC_PERC, KC_LPRN, KC_RPRN, KC_SCLN, KC_COMM,
    KC_EXLM, KC_LCBR, KC_QUOT, KC_DQUO, KC_RCBR, KC_QUES,
    KC_HASH, KC_CIRC, KC_EQL , KC_UNDS, KC_DLR , KC_ASTR,
    KC_TILD, KC_LABK, KC_PIPE, KC_MINS, KC_RABK, KC_SLSH,
                                                 KC_COLN, KC_BSLS,

                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX,
                      KC_PLUS, KC_BSPC, KC_TAB , KC_SPC , KC_DOT , USRNAME,
                      KC_SLSH, KC_AMPR, KC_LBRC, KC_RBRC, KC_AT  , _______,
             KC_LSFT, TO_BASE

  ),
  [NUM] = LAYOUT_LR(  // Number layer.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, _______, XXXXXXX,
                                                 TO_BASE, KC_ESC ,

                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      KC_TAB , KC_8   , KC_9   , KC_4   , KC_PLUS, KC_SLSH,
                      KC_COLN, KC_1   , KC_2   , KC_3   , KC_MINS, KC_ASTR,
                      KC_COMM, KC_7   , KC_6   , KC_5   , KC_DOT , _______,
             KC_0   , QK_LLCK
  ),
};

#ifdef CHORDAL_HOLD
// Handedness for Chordal Hold.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT_LR(
  '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
                                               'L'    , 'L'    ,

                    '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
           'R'    , 'R'
);
#endif  // CHORDAL_HOLD

