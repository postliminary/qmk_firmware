#pragma once

#include QMK_KEYBOARD_H

enum userspace_keycodes {
    BOOT_AT = SAFE_RANGE,
    LO_TOGG,
    NEW_SAFE_RANGE //use "NEW_SAFE_RANGE" for keymap specific codes
};

enum userspace_layers {
    _BASE,
    _FN
};