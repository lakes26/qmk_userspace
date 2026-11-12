#pragma once

#include "config_lakes26.h"

// Drive the Voyager's 4 status LEDs from lakes26.c (layer active, Sentence
// Case primed, Caps Word, Layer Lock) instead of the default binary layer
// number display.
#define VOYAGER_USER_LEDS

// ZSA Navigator trackball (module lakes26/navigator_trackball).
//
// Automatic mouse layer (https://docs.qmk.fm/features/pointing_device): moving
// the ball turns on the MOUSE layer, which has the mouse buttons. It turns off
// 650 ms after the last mouse activity, or as soon as any other key is
// pressed.
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// The numbers of the MOUSE and EXT layers. config.h can't see `enum layers`,
// so static asserts in lakes26.c check that these match it.
#define AUTO_MOUSE_DEFAULT_LAYER 1
#define TRACKBALL_SCROLL_LAYER 5
// While the EXT layer is on (hold ':'), the ball scrolls instead of moving the
// pointer.
#define NAVIGATOR_DRAG_SCROLL_LAYERS { TRACKBALL_SCROLL_LAYER }
