
#include "keebo.h"
#include "print.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            print("Encoder 2 Rotate CW");
        } else {
            print("Encoder 2 Rotate CCW");
        }
    }
    return true;
}
