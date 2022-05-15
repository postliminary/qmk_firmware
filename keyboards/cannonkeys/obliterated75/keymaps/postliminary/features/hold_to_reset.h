#pragma once

#include "quantum.h"

#ifndef HOLD_TO_RESET_DELAY
#define HOLD_TO_RESET_DELAY 1000 // Default 1 second hold delay for reset
#endif

void hold_to_reset_init(uint16_t hold_to_reset_keycode);

bool process_hold_to_reset(uint16_t keycode, keyrecord_t* record);