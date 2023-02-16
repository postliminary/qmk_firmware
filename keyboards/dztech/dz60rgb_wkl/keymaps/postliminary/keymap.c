#include "postliminary.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_tsangan_hhkb(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN),
        ___X___, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, MO(_FN), ___X___
    ),
    [_FN] = LAYOUT_60_tsangan_hhkb(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_F13, KC_INS,
        _______, KC_HOME, KC_UP,   KC_END,  ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, KC_PSCR, KC_VOLD, KC_VOLU, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, KC_CAPS,          _______,
        _______,          ___X___, ___X___, ___X___, ___X___, KC_PGUP, ___X___, ___X___, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______,
        ___X___,MO(_KBFN),_______,                            KC_PGDN,                                     _______, _______, ___X___
    ),
    [_KBFN] = LAYOUT_60_tsangan_hhkb(
        BOOT_AT, _______, _______, _______, _______, _______, _______, _______, LO_TOGG, RGB_RMOD,RGB_MOD, RGB_VAD, RGB_VAI, RGB_TOG, _______,
        _______, _______, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,
        _______, RGB_HUD, RGB_SAD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______, _______,
        ___X___, _______, _______,                            _______,                                     _______, _______, ___X___
    )
};

void matrix_init_keymap(void) {
#ifdef LAYER_MASK_ENABLED
    LAYER_MASK_INIT(keymaps);
#endif
};
