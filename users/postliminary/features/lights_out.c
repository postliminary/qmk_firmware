#include "lights_out.h"

#define MILLISECONDS_IN_SECOND 1000     // Timeout conversion factor

static uint16_t idle_timer;             // Idle LED timeout timer
static uint16_t idle_second_counter;    // Idle LED seconds counter, counts seconds not milliseconds
static uint16_t key_event_counter;      // This counter is used to check if any keys are being held
static bool lights_enabled;             // Current LED state flag. If false then LED is off.
static bool timeout_enabled;            // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
static bool timeout_user_value;         // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
static uint16_t timeout_seconds;        // Idle LED timeout value, in seconds not milliseconds
#ifdef LIGHTS_OUT_RGB_MODE
static led_flags_t timeout_saved_flags; // Store LED flg before timeout so it can be restored when LED is turned on again.
#else
static uint8_t timeout_saved_level;     // Store LED flg before timeout so it can be restored when LED is turned on again.
#endif

void lights_out_init(void)
{
    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    lights_enabled = true;                              // Initially, keyboard backlight is enabled. Change to false config.h initializes bakclight disabled.
    timeout_seconds = LIGHTS_OUT_TIMEOUT;               // Backlight timeout initialized to its default configure in keymap.h
    timeout_enabled = true;                             // Enable RGB timeout by default. Enable using toggle key.
    timeout_user_value = true;                          // Has to have the same initial value as timeout_enabled.
#ifdef LIGHTS_OUT_RGB_MODE
    timeout_saved_flags = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from idle.
#else
    timeout_saved_level = get_backlight_level();        // Save backlight level for when keyboard comes back from idle.
#endif
}

void lights_out_task(void) {
    if(timeout_enabled && lights_enabled) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= timeout_seconds) {
#ifdef LIGHTS_OUT_RGB_MODE
            timeout_saved_flags = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
#else
            timeout_saved_level = get_backlight_level();
            backlight_level_noeeprom(0);
#endif
            lights_enabled = false;
            idle_second_counter = 0;
        }
    }
}

void preprocess_lights_out(uint16_t keycode, keyrecord_t* record) {
    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (timeout_enabled) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!lights_enabled) {
#ifdef LIGHTS_OUT_RGB_MODE
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(timeout_saved_flags);
#else
            backlight_level_noeeprom(timeout_saved_level);
#endif
            lights_enabled = true;
        }
    }    
}

bool process_lights_out(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
#ifdef LIGHTS_OUT_RGB_MODE
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle();
                if (rgb_matrix_is_enabled()) {
                    timeout_enabled = timeout_user_value;
                } else {
                    timeout_enabled = false;
                }
            }
            return true;
#else
        case BL_TOGG:
            if (record->event.pressed) {
                backlight_toggle();
                if (is_backlight_enabled()) {
                    timeout_enabled = timeout_user_value;
                } else {
                    timeout_enabled = false;
                }
            }
            return true;
#endif
        case LO_TOGG:
            if (record->event.pressed) {
                // Toggle idle LED timeout on or off
                timeout_enabled = !timeout_enabled;
                timeout_user_value = timeout_enabled;
            }
            return true;
        default:
            return false; //Process all other keycodes normally
    }
}
