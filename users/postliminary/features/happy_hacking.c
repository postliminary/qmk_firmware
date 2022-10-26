#include "happy_hacking.h"

bool process_happy_hacking(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case HH_TOGG:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_HHKB)) {
                    set_single_persistent_default_layer(_BASE);
                } else {
                    set_single_persistent_default_layer(_HHKB);
                }
            }
            return true;
        default:
            return false; //Process all other keycodes normally
    }
}