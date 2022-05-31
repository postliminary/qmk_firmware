/**
 * TODO
 * Layer mask
 * Unicode kaomojis
 * Sarcasm
 */
#include "postliminary.h"

__attribute__ ((weak)) 
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
#ifdef LIGHTS_OUT_ENABLED
    lights_out_init();
#endif
    sarcasm_init();
    matrix_init_keymap();
};

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    caps_word_task();
#ifdef LIGHTS_OUT_ENABLED
    lights_out_task();
#endif
    matrix_scan_keymap();
};

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef LIGHTS_OUT_ENABLED
    preprocess_lights_out(keycode, record);
#endif
    if (process_caps_word(keycode, record)) { return false; }
    if (process_hold_to_reset(keycode, record)) { return false; }
#ifdef LIGHTS_OUT_ENABLED
    if (process_lights_out(keycode, record)) { return false; }
#endif
    if (process_sarcasm(keycode, record)) { return false; }
    if (process_kaomoji(keycode, record)) { return false;}

    return process_record_keymap(keycode, record);
}

__attribute__ ((weak))
bool led_update_keymap(led_t led_state) { return true; }

bool led_update_user(led_t led_state) {
    sarcasm_task(led_state);
    return led_update_keymap(led_state);
}

__attribute__ ((weak))
void rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#ifdef LAYER_MASK_ENABLED
    apply_layer_mask(led_min, led_max);
#endif
    rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
