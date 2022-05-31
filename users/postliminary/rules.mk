UNICODE_ENABLE = yes
COMMAND_ENABLE = no

SRC += $(USER_PATH)/postliminary.c
SRC += $(USER_PATH)/features/caps_word.c
SRC += $(USER_PATH)/features/hold_to_reset.c
SRC += $(USER_PATH)/features/kaomoji.c
SRC += $(USER_PATH)/features/sarcasm.c

ifeq ($(strip $(LIGHTS_OUT_ENABLED)), yes)
    OPT_DEFS += -DLIGHTS_OUT_ENABLED
	SRC += $(USER_PATH)/features/lights_out.c
endif

ifeq ($(strip $(LIGHTS_OUT_RGB_MODE)), yes)
    OPT_DEFS += -DLIGHTS_OUT_RGB_MODE
endif

ifeq ($(strip $(LAYER_MASK_ENABLED)), yes)
    OPT_DEFS += -DLAYER_MASK_ENABLED
	SRC += $(USER_PATH)/features/layer_mask.c
endif