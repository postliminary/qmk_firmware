#pragma once

#include "postliminary.h"

#define LAYER_MASK_INIT(keymaps) layer_mask_init(keymaps, sizeof(keymaps) / sizeof(keymaps[0]))

void layer_mask_init(const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS], const size_t keymaps_size);

void apply_layer_mask(uint8_t led_min, uint8_t led_max);