#pragma once

#include QMK_KEYBOARD_H
#include "features/caps_word.h"
#include "features/hold_to_reset.h"
#include "features/kaomoji.h"
#include "features/layer_mask.h"
#include "features/lights_out.h"
#include "features/sarcasm.h"

enum userspace_keycodes {
    BOOT_AT = SAFE_RANGE,
    LO_TOGG,
    NEW_SAFE_RANGE // Use "NEW_SAFE_RANGE" for keymap specific codes
};

enum userspace_layers {
    _BASE,
    _FN,
    _CAPS
};