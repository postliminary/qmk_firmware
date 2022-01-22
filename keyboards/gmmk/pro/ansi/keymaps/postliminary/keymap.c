/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define MILLISECONDS_IN_SECOND 1000         // Conversion factor
#define RGB_DEFAULT_TIME_OUT 600            // 10 minutes in seconds

static uint16_t idle_timer;                 // Idle LED timeout timer
static uint16_t idle_second_counter;        // Idle LED seconds counter, counts seconds not milliseconds
static uint16_t key_event_counter;          // This counter is used to check if any keys are being held
static bool rgb_enabled_flag;               // Current LED state flag. If false then LED is off.
static bool rgb_time_out_enable;            // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
static bool rgb_time_out_user_value;        // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
static uint16_t rgb_time_out_seconds;       // Idle LED timeout value, in seconds not milliseconds
static led_flags_t rgb_time_out_saved_flag; // Store LED flg before timeout so it can be restored when LED is turned on again.

enum custom_keycodes {
    RGB_OUT = SAFE_RANGE,  // Toggle RGB Timeout
    BOOT_AT,               // Restart into bootloader after hold timeout
};

enum layout_names {
    _BASE,
    _FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
        BOOT_AT, _______, _______, _______, _______, _______, _______, _______, _______, RGB_OUT, RGB_VAD, RGB_VAI, RGB_TOG, KC_CALC,          _______,
        NK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,          KC_MUTE,
        _______, _______, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,RGB_RMOD, RGB_MOD, _______,          KC_MSTP,
        _______, RGB_HUD, RGB_SAD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_MPRV,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, KC_MNXT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, KC_PGDN, _______
    ),
};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}
#endif // ENCODER_ENABLE

void matrix_init_user(void) {
    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_DEFAULT_TIME_OUT;        // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable = true;                         // Enable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value = true;                     // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag = true;                            // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_saved_flag = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from ide.
};

void matrix_scan_user(void) {
    if(rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    switch (keycode) {
        case BOOT_AT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle();
                if (rgb_matrix_is_enabled()) {
                    rgb_time_out_enable = rgb_time_out_user_value;
                } else {
                    rgb_time_out_enable = false;
                }
            }
            return false;
        case RGB_OUT:
            if (record->event.pressed) {
                // Toggle idle LED timeout on or off
                rgb_time_out_enable = !rgb_time_out_enable;
                rgb_time_out_user_value = rgb_time_out_enable;
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Apply led matrix mask to only light up active layer keys
    // TODO cache/precalc the led assignments
    const uint16_t layer_id = get_highest_layer(layer_state|default_layer_state);
    if (layer_id == _BASE) {
        return;
    }

    const uint16_t (*layer)[MATRIX_COLS] = keymaps[layer_id];
    for (uint8_t x = 0; x <= MATRIX_ROWS; x++) {
        for (uint8_t y = 0; y <= MATRIX_COLS; y++) {
            if (layer[x][y] == _______) {
                uint8_t led_i = g_led_config.matrix_co[x][y];
                if (led_min <= led_i && led_i <= led_max) {
                    rgb_matrix_set_color(led_i, 0, 0, 0);
                }
            }
        }
    }
}
