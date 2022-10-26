#pragma once

#include QMK_KEYBOARD_H
#include "features/caps_word.h"
#include "features/happy_hacking.h"
#include "features/hold_to_reset.h"
#include "features/kaomoji.h"
#include "features/layer_mask.h"
#include "features/lights_out.h"
#include "features/sarcasm.h"

#define ___X___ KC_NO

enum userspace_keycodes {
    BOOT_AT = SAFE_RANGE,   // Hold to reset
    HH_TOGG,                // HHKB toggle
    LO_TOGG,                // Lights out toggle
    UC_ANML,                // Random animal kaomoji
    UC_SHRG,                // Shrug kaomoji
    UC_DISS,                // Dissapointed kaomoji
    UC_FLIP,                // Table flip kaomoji
    UC_GIVE,                // Gimme kaomoji
    UC_HNGY,                // Hungry kaomoji
    UC_JOYF,                // Joy kaomoji
    UC_KAOK,                // Karaoke kaomoji
    UC_LOVE,                // Love kaomoji
    UC_NRVS,                // Nervous kaomoji
    UC_SURP,                // Wow kaomoji
    NEW_SAFE_RANGE          // Use "NEW_SAFE_RANGE" for keymap specific codes
};

enum userspace_layers {
    _BASE,
    _HHKB,                  // HHKB-ish base layer
    _FN,                    // FN key layer
    _CAPS,                  // CAPS key layer
    _KBFN                   // Keyboard FN layer
};