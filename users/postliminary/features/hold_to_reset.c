#include "hold_to_reset.h"

static uint32_t key_timer;      // How long has the key been pressed

bool process_hold_to_reset(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case BOOT_AT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= HOLD_TO_RESET_DELAY) {
                    reset_keyboard();
                }
            }
            return true;
        default:
            return false; //Process all other keycodes normally
    }
}
