#include "postliminary.h"

__attribute__ ((weak)) 
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
#ifdef LIGHTS_OUT_ENABLED
    lights_out_init();
#endif
#ifdef SARCASM_ENABLED
    sarcasm_init();
#endif
    matrix_init_keymap();
};

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#ifdef CAPS_WORD_ENABLED
    caps_word_task();
#endif    
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
#ifdef CAPS_WORD_ENABLED
    if (process_caps_word(keycode, record)) { return false; }
#endif
    if (process_hold_to_reset(keycode, record)) { return false; }
#ifdef HAPPY_HACKING_ENABLED
    if (process_happy_hacking(keycode, record)) { return false; }
#endif
#ifdef LIGHTS_OUT_ENABLED
    if (process_lights_out(keycode, record)) { return false; }
#endif
#ifdef SARCASM_ENABLED
    if (process_sarcasm(keycode, record)) { return false; }
#endif
#ifdef KAOMOJI_ENABLED
    if (process_kaomoji(keycode, record)) { return false;}
#endif

    return process_record_keymap(keycode, record);
}

__attribute__ ((weak))
bool led_update_keymap(led_t led_state) { return true; }

bool led_update_user(led_t led_state) {
#ifdef SARCASM_ENABLED
    sarcasm_task(led_state);
#endif
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
