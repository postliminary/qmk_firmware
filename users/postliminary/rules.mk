SRC += postliminary.c
SRC += features/caps_word.c
SRC += features/hold_to_reset.c
SRC += features/kaomoji.c
SRC += features/sarcasm.c

ifeq ($(strip $(LIGHTS_OUT_ENABLED)), yes)
    OPT_DEFS += -DLIGHTS_OUT_ENABLED
	SRC += features/lights_out.c
endif

ifeq ($(strip $(LIGHTS_OUT_RGB_ENABLED)), yes)
    OPT_DEFS += -DLIGHTS_OUT_RGB_ENABLED
endif

ifeq ($(strip $(LAYER_MASK_ENABLED)), yes)
    OPT_DEFS += -DLAYER_MASK_ENABLED
	SRC += features/layer_mask.c
endif