// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "layout.h"
#include "lakes26.c"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    XXXXXXX, XXXXXXX, XXXXXXX, KC_DOWN, KC_UP  , XXXXXXX,
    KC_TAB , KC_V   , KC_M   , KC_L   , KC_C   , KC_P   ,
    KC_BSPC, HOME_S , HOME_T , HOME_R , HOME_D , KC_Y   ,
    EXT_COL, KC_X   , KC_K   , KC_J   , NUM_G  , KC_W   ,
                                                 KC_SPC , NAV_ESC,

                      KC_HOME, KC_LEFT, KC_RGHT, KC_END , APPSWCH, KC_MPLY,
                      KC_B   , MAGIC  , KC_U   , KC_O   , KC_Q   , KC_SLSH,
                      KC_F   , HOME_N , HOME_E , HOME_A , HOME_I , XXXXXXX,
                      KC_Z   , KC_H   , KC_COMM, KC_DOT , KC_SCLN, KC_ENT ,
             QK_REP , SYMBOLS
  ),
  [SYM] = LAYOUT_LR(  // Symbol layer (one-shot).
    KC_GRV , KC_PERC, KC_LPRN, KC_RPRN, KC_SCLN, KC_COMM,
    KC_EXLM, KC_LCBR, KC_QUOT, KC_DQUO, KC_RCBR, KC_QUES,
    KC_HASH, KC_CIRC, KC_EQL , KC_UNDS, KC_DLR , KC_ASTR,
    KC_TILD, KC_LABK, KC_PIPE, KC_MINS, KC_RABK, KC_SLSH,
                                                 KC_COLN, KC_BSLS,

                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, KC_LSFT, KC_LGUI, KC_LCTL, KC_LALT, XXXXXXX,
                      KC_PLUS, KC_BSPC, KC_TAB , KC_SPC , KC_DOT , USRNAME,
                      KC_SLSH, KC_AMPR, KC_LBRC, KC_RBRC, KC_AT  , _______,
             KC_LSFT, TO_BASE
  ),
  [NUM] = LAYOUT_LR(  // Number layer (hold G).
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
  [NAV] = LAYOUT_LR(  // Navigation layer (hold Esc).
    _______, _______, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, PREVTAB, NEXTTAB, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, SELLINE,
    XXXXXXX, HK_UNDO, HK_CUT , HK_COPY, HK_PSTE, XXXXXXX,
                                                 _______, _______,

                      _______, _______, _______, _______, _______, _______,
                      KC_PGUP, KC_HOME, KC_UP  , KC_END , XXXXXXX, _______,
                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
                      XXXXXXX, SELWBAK, SELWORD, XXXXXXX, XXXXXXX, _______,
             _______, QK_LLCK
  ),
  [EXT] = LAYOUT_LR(  // Mouse (Orbital Mouse) and extras (hold :).
    _______, _______, _______, _______, _______, _______,
    OM_FAST, HK_UNDO, OM_W_L , KC_BSPC, KC_SPC , OM_W_R ,
    OM_SLOW, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, SELLINE,
    _______, XXXXXXX, HK_PSTE, HK_SALL, HK_COPY, HK_CUT ,
                                                 HK_BACK, OM_BTN1,

                      _______, _______, _______, _______, _______, _______,
                      OM_W_U , OM_BTN1, OM_U   , OM_BTN2, OM_FAST, _______,
                      OM_W_D , OM_L   , OM_D   , OM_R   , OM_SLOW, _______,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
             OM_BTN1, QK_LLCK
  ),
  [FUN] = LAYOUT_LR(  // F-keys, media, RGB lighting, bootloader (F + N combo).
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    LUMINO , RGBNEXT, RGBHUP , RGBHRND, RGBDEF1, RGBDEF2,
    XXXXXXX, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,
    XXXXXXX, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE,
                                                 XXXXXXX, XXXXXXX,

                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
                      XXXXXXX, KC_F8  , KC_F9  , KC_F4  , KC_F11 , XXXXXXX,
                      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F12 , XXXXXXX,
                      XXXXXXX, KC_F7  , KC_F6  , KC_F5  , XXXXXXX, QK_RBT ,
             KC_F10 , QK_LLCK
  ),
};

#ifdef CHORDAL_HOLD
// Handedness for Chordal Hold. '*' keys may be held with keys on either hand:
// the top row, the outer columns, and the NAV (Esc) thumb key.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT_LR(
  '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
                                               'L'    , '*'    ,

                    '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                    'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
           'R'    , 'R'
);
#endif  // CHORDAL_HOLD
// clang-format on
