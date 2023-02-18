COMMAND_ENABLE = no

# Custom options
# CAPS_WORD_ENABLED = yes
# HAPPY_HACKING_ENABLED = yes
# KAOMOJI_ENABLED = yes
# LAYER_MASK_ENABLED = yes
# LIGHTS_OUT_ENABLED = yes
# LIGHTS_OUT_RGB_MODE = yes
# SARCASM_ENABLED = yes

SRC += $(USER_PATH)/postliminary.c
SRC += $(USER_PATH)/features/hold_to_reset.c

ifeq ($(strip $(CAPS_WORD_ENABLED)), yes)
    OPT_DEFS += -DCAPS_WORD_ENABLED
	SRC += $(USER_PATH)/features/caps_word.c
endif

ifeq ($(strip $(HAPPY_HACKING_ENABLED)), yes)
    OPT_DEFS += -DHAPPY_HACKING_ENABLED
	SRC += $(USER_PATH)/features/happy_hacking.c
endif

ifeq ($(strip $(KAOMOJI_ENABLED)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
    OPT_DEFS += -DKAOMOJI_ENABLED
	SRC += $(USER_PATH)/features/kaomoji.c
endif

ifeq ($(strip $(LAYER_MASK_ENABLED)), yes)
    OPT_DEFS += -DLAYER_MASK_ENABLED
	SRC += $(USER_PATH)/features/layer_mask.c
endif

ifeq ($(strip $(LIGHTS_OUT_ENABLED)), yes)
    OPT_DEFS += -DLIGHTS_OUT_ENABLED
	SRC += $(USER_PATH)/features/lights_out.c
endif

ifeq ($(strip $(LIGHTS_OUT_RGB_MODE)), yes)
    OPT_DEFS += -DLIGHTS_OUT_RGB_MODE
endif

ifeq ($(strip $(SARCASM_ENABLED)), yes)
    OPT_DEFS += -DSARCASM_ENABLED
    SRC += $(USER_PATH)/features/sarcasm.c
endif
