#include "layer_mask.h"

static uint16_t** layer_masks;
static uint16_t* layer_mask_sizes;

void layer_mask_init(const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS], size_t keymaps_size) {
    // layers = keymaps;
    layer_masks = (uint16_t**)malloc(keymaps_size * sizeof(uint16_t*));
    layer_mask_sizes = (uint16_t*)malloc(keymaps_size * sizeof(uint16_t));
    
    uint16_t layer_stack[MATRIX_ROWS * MATRIX_COLS];
    uint16_t layer_stack_size = 0;
    for (uint16_t z = 0; z < keymaps_size; z++) {
        const uint16_t (*layer)[MATRIX_COLS] = keymaps[z];
        layer_stack_size = 0;

        // Make stack of masked leds
        for (uint16_t x = 0; x <= MATRIX_ROWS; x++) {
            for (uint16_t y = 0; y <= MATRIX_COLS; y++) {
                if (layer[x][y] == _______ || layer[x][y] == XXXXXXX) {
                    layer_stack[layer_stack_size] = g_led_config.matrix_co[x][y];
                    layer_stack_size++;
                }
            }
        }

        // Copy stack to layer mask
        layer_masks[z] = (uint16_t*)malloc(layer_stack_size * sizeof(uint16_t));
        layer_mask_sizes[z] = layer_stack_size;
        for (uint16_t i = 0; i < layer_stack_size; i++) {
            layer_masks[z][i] = layer_stack[i];
        }
    }
}

void apply_layer_mask(uint8_t led_min, uint8_t led_max) {
    // Apply led matrix mask to only light up active layer keys
    const uint16_t layer_id = get_highest_layer(layer_state|default_layer_state);
    if (layer_id == _BASE) {
        return;
    }

    // const uint16_t (*layer)[MATRIX_COLS] = keymaps[layer_id];
    // for (uint8_t x = 0; x <= MATRIX_ROWS; x++) {
    //     for (uint8_t y = 0; y <= MATRIX_COLS; y++) {
    //         if (layer[x][y] == _______ || layer[x][y] == XXXXXXX) {
    //             uint8_t led_i = g_led_config.matrix_co[x][y];
    //             if (led_min <= led_i && led_i <= led_max) {
    //                 rgb_matrix_set_color(led_i, 0, 0, 0);
    //             }
    //         }
    //     }
    // }

    const uint16_t* layer_mask = layer_masks[layer_id];
    const uint16_t layer_mask_size = layer_mask_sizes[layer_id];
    for (uint16_t i = 0; i < layer_mask_size; i++) {
        uint16_t led_i = layer_mask[i];
        if (led_min <= led_i && led_i <= led_max) {
            rgb_matrix_set_color(led_i, 0, 0, 0);
        }
    }
}