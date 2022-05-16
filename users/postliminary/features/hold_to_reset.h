#pragma once

#include "postliminary.h"

#ifndef HOLD_TO_RESET_DELAY
#define HOLD_TO_RESET_DELAY 3000 // Default 3 seconds hold delay for reset
#endif

bool process_hold_to_reset(uint16_t keycode, keyrecord_t* record);