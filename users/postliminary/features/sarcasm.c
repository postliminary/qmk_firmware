#include "sarcasm.h"

static uint8_t sarcasm_enabled;

void sarcasm_init() {
    sarcasm_enabled = host_keyboard_led_state().caps_lock;
}

void sarcasm_task(led_t led_state) {
    if (sarcasm_enabled != led_state.caps_lock) {
        if (sarcasm_enabled) {
            unregister_weak_mods(MOD_BIT(KC_LSFT));
        }
        sarcasm_enabled = led_state.caps_lock;
    }
}

bool process_sarcasm(uint16_t keycode, keyrecord_t* record) {
    if (!sarcasm_enabled) {
        return false;
    }

    switch (keycode) {
        case KC_A ... KC_Z:
            if (record->event.time % 2) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            } 
            return true;
        default:
            return false; //Process all other keycodes normally
    }
}