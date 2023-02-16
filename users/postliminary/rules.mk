COMMAND_ENABLE = no

# Custom options
HAPPY_HACKING_ENABLED = no
KAOMOJI_ENABLED = no
LAYER_MASK_ENABLED = no
LIGHTS_OUT_ENABLED = no
LIGHTS_OUT_RGB_MODE = no
SARCASM_ENABLED = no

# Firmware optimizations
NO_TAPPING				 = no
NO_PRINT				 = yes

SRC += $(USER_PATH)/postliminary.c
SRC += $(USER_PATH)/features/caps_word.c
SRC += $(USER_PATH)/features/hold_to_reset.c

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

ifeq ($(strip $(NO_PRINT)), yes)
    OPT_DEFS += -DNO_PRINT -DNO_DEBUG
endif

ifeq ($(strip $(NO_TAPPING)), yes)
    OPT_DEFS += -DNO_ACTION_TAPPING
endif
