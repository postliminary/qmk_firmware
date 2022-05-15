#pragma once

#include "postliminary.h"

#ifndef LIGHTS_OUT_TIMEOUT
#define LIGHTS_OUT_TIMEOUT 600 // Default 10 minutes backlight timeout
#endif

void lights_out_init();

void lights_out_task(void);

bool process_lights_out(uint16_t keycode, keyrecord_t* record);
