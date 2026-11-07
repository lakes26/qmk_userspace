#pragma once

#include "config_lakes26.h"

// Drive the Voyager's 4 status LEDs from lakes26.c (layer active, Sentence
// Case primed, Caps Word, Layer Lock) instead of the default binary layer
// number display.
#define VOYAGER_USER_LEDS
