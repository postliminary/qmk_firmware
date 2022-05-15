#include "lights_out.h"

#define MILLISECONDS_IN_SECOND 1000     // Timeout conversion factor

static uint16_t feature_toggle_keycode; // Which key toggles the feature
static uint16_t lights_toggle_keycode;  // Which key toggles the backlight
static uint16_t idle_timer;             // Idle LED timeout timer
static uint16_t idle_second_counter;    // Idle LED seconds counter, counts seconds not milliseconds
static uint16_t key_event_counter;      // This counter is used to check if any keys are being held
static bool lights_enabled;             // Current LED state flag. If false then LED is off.
static bool timeout_enabled;            // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
static bool timeout_user_value;         // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
static uint16_t timeout_seconds;        // Idle LED timeout value, in seconds not milliseconds
static uint8_t timeout_saved_level;     // Store LED flg before timeout so it can be restored when LED is turned on again.

void lights_out_init(uint16_t lights_out_toggle_keycode, uint16_t backlight_toggle_keycode)
{
    feature_toggle_keycode = lights_out_toggle_keycode;
    backlight_toggle_keycode = lights_toggle_keycode;
    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    lights_enabled = true;                              // Initially, keyboard backlight is enabled. Change to false config.h initializes bakclight disabled.
    timeout_seconds = LIGHTS_OUT_TIMEOUT;               // Backlight timeout initialized to its default configure in keymap.h
    timeout_enabled = true;                             // Enable RGB timeout by default. Enable using toggle key.
    timeout_user_value = true;                          // Has to have the same initial value as bl_time_out_enable.
    timeout_saved_level = get_backlight_level();        // Save RGB matrix state for when keyboard comes back from ide.
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
            timeout_saved_level = get_backlight_level();
            backlight_level_noeeprom(0);
            lights_enabled = false;
            idle_second_counter = 0;
        }
    }
}

bool process_lights_out(uint16_t keycode, keyrecord_t* record) {
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
            backlight_level_noeeprom(timeout_saved_level);
            lights_enabled = true;
        }
    }

    switch (keycode) {
        case lights_toggle_keycode:
            if (record->event.pressed) {
                backlight_toggle();
                if (is_backlight_enabled()) {
                    timeout_enabled = timeout_user_value;
                } else {
                    timeout_enabled = false;
                }
            }
            return true;
        case feature_toggle_keycode:
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
