#pragma once

#include "quantum.h"

#ifndef LIGHTS_OUT_TIMEOUT
#define LIGHTS_OUT_TIMEOUT 60 // Default 1 minute backlight timeout
#endif

void lights_out_init(uint16_t lights_out_toggle_keycode, uint16_t backlight_toggle_keycode);

void lights_out_task(void);

bool process_lights_out(uint16_t keycode, keyrecord_t* record);
