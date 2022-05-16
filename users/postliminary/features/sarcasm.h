#pragma once

#include "postliminary.h"

void sarcasm_init(void);

void sarcasm_task(led_t led_state);

bool process_sarcasm(uint16_t keycode, keyrecord_t* record);