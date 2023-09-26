/**
 * config.h
 *
 */

#pragma once

#define MATRIX_IO_DELAY 10

/* key matrix size */

#define MATRIX_ROWS 5
#define MATRIX_COLS 18

#define MATRIX_ROW_PINS { B9,  B8, C10, C11, C12 }
#define MATRIX_COL_PINS { C9,  C8,  C7,  C6, B15, B14, B13, B12, B10, B2, B1, B0, C5, C4, A7, A6, A5, A4 }

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE    2

#define ENCODERS_PAD_A { C1, C13 }
#define ENCODERS_PAD_B { C2, C14 }
#define ENCODER_RESOLUTIONS { 2, 2 }

// i2c setting
#define I2C_DRIVER          I2CD1
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_CLOCK_SPEED    400000
#define I2C1_DUTY_CYCLE     FAST_DUTY_CYCLE_2
#define PAL_MODE_STM32_ALTERNATE_OPENDRAIN ( PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN )

// rgb matrix setting
#define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_GND // 0x30, this must be the 7 bit address not the 8 bit address 0x60!
#define IS31FL3741_I2C_ADDRESS_2 IS31FL3741_I2C_ADDRESS_VCC
// #define DRIVER_COUNT 2 // no longer necessary
#define DRIVER_1_LED_TOTAL 102
#define DRIVER_2_LED_TOTAL 78

// #define RGB_MATRIX_LED_COUNT ( DRIVER_1_LED_TOTAL )
#define RGB_MATRIX_IS31FL3741
#define RGB_MATRIX_LED_COUNT ( DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL )
#define ADDITIONAL_LED_PER_KEY

// #define IS31FL3741_I2C_TIMEOUT 0xFF

#define IS31FL3741_GLOBAL_CURRENT 0xFF
#define IS31FL3741_PWM_FREQUENCY 0x90

// Not entirely sure why they set the default to 32K for UP/DN
// I didnt install any res on the board, my STM32 bare metal program didnt
// set any res either and all other ISSI define 0Ohm as default...
// So we go with 0 zero.
#define IS31FL3741_SW_PULLUP IS31FL3741_PUR_0_OHM
#define IS31FL3741_CS_PULLDOWN IS31FL3741_PDR_0_OHM

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_DEFAULT_VAL 80
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_HUE_WAVE

#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
// #    define ENABLE_RGB_MATRIX_PIXEL_RAIN
// #    define ENABLE_RGB_MATRIX_PIXEL_FLOW
// #    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH


// tapping setting
//#define TAPPING_TERM 200
//#define RETRO_TAPPING
//#define PERMISSIVE_HOLD
