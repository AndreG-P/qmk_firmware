#include "keebo.h"
#include "print.h"
// #include "i2c_master.h"
// #include "drivers/led/issi/is31fl3741.h"
// #include "gpio.h"

char *status;
uint8_t id = 0xFF;

#ifdef RGB_MATRIX_ENABLE

#define CAPS_LOCK_LED_INDEX 35

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
// ISSI 1 Bottom LEDs
// ROW 1
    {0, CS3_SW1,   CS2_SW1,   CS1_SW1}, // 1
    {0, CS3_SW2,   CS2_SW2,   CS1_SW2},
    {0, CS6_SW1,   CS5_SW1,   CS4_SW1},
    {0, CS6_SW2,   CS5_SW2,   CS4_SW2},
    {0, CS9_SW1,   CS8_SW1,   CS7_SW1},
    {0, CS9_SW2,   CS8_SW2,   CS7_SW2},
    {0, CS12_SW1,  CS11_SW1,  CS10_SW1},
    {0, CS12_SW2,  CS11_SW2,  CS10_SW2},
    {0, CS15_SW1,  CS14_SW1,  CS13_SW1},
    {0, CS15_SW2,  CS14_SW2,  CS13_SW2},
    {0, CS18_SW1,  CS17_SW1,  CS16_SW1},
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2},
    {0, CS21_SW1,  CS20_SW1,  CS19_SW1},
    {0, CS21_SW2,  CS20_SW2,  CS19_SW2},
    {0, CS24_SW1,  CS23_SW1,  CS22_SW1},
    {0, CS24_SW2,  CS23_SW2,  CS22_SW2},
    {0, CS27_SW1,  CS26_SW1,  CS25_SW1}, // 17

// ROW 2
    {0, CS3_SW3,   CS2_SW3,   CS1_SW3}, // tab // 18
    {0, CS3_SW4,   CS2_SW4,   CS1_SW4}, // Q
    {0, CS6_SW3,   CS5_SW3,   CS4_SW3}, // W
    {0, CS6_SW4,   CS5_SW4,   CS4_SW4}, // E
    {0, CS9_SW3,   CS8_SW3,   CS7_SW3}, // R
    {0, CS9_SW4,   CS8_SW4,   CS7_SW4}, // T
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3}, // Y
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4}, // U
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3}, // I
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4}, // O
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3}, // P
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4}, // [
    {0, CS21_SW3,  CS20_SW3,  CS19_SW3}, // ]
    {0, CS21_SW4,  CS20_SW4,  CS19_SW4}, // |
    {0, CS24_SW3,  CS23_SW3,  CS22_SW3}, // Print
    {0, CS24_SW4,  CS23_SW4,  CS22_SW4}, // F1
    {0, CS27_SW3,  CS26_SW3,  CS25_SW3}, // F6 // 34

// ROW 3
    {0, CS3_SW5,   CS2_SW5,   CS1_SW5},  // Capslock // 35
    {0, CS3_SW6,   CS2_SW6,   CS1_SW6},  // A
    {0, CS6_SW5,   CS5_SW5,   CS4_SW5},  // S
    {0, CS6_SW6,   CS5_SW6,   CS4_SW6},  // D
    {0, CS9_SW5,   CS8_SW5,   CS7_SW5},  // F
    {0, CS9_SW6,   CS8_SW6,   CS7_SW6},  // G
    {0, CS12_SW5,  CS11_SW5,  CS10_SW5}, // H
    {0, CS12_SW6,  CS11_SW6,  CS10_SW6}, // J
    {0, CS15_SW5,  CS14_SW5,  CS13_SW5}, // K
    {0, CS15_SW6,  CS14_SW6,  CS13_SW6}, // L
    {0, CS18_SW5,  CS17_SW5,  CS16_SW5}, // ;
    {0, CS21_SW5,  CS20_SW5,  CS19_SW5}, // '
    {0, CS21_SW6,  CS20_SW6,  CS19_SW6}, // enter
    {0, CS24_SW5,  CS23_SW5,  CS22_SW5}, // end
    {0, CS27_SW5,  CS26_SW5,  CS25_SW5}, // F2
    {0, CS27_SW4,  CS26_SW4,  CS25_SW4}, // F7 // 50

// ROW 4
    {0, CS3_SW7,   CS2_SW7,   CS1_SW7},  // Shift L // 51
    {0, CS6_SW8,   CS5_SW8,   CS4_SW8},  // Z
    {0, CS6_SW7,   CS5_SW7,   CS4_SW7},  // X
    {0, CS9_SW8,   CS8_SW8,   CS7_SW8},  // C
    {0, CS9_SW7,   CS8_SW7,   CS7_SW7},  // V
    {0, CS12_SW8,  CS11_SW8,  CS10_SW8}, // B
    {0, CS12_SW7,  CS11_SW7,  CS10_SW7}, // N
    {0, CS15_SW8,  CS14_SW8,  CS13_SW8}, // M
    {0, CS15_SW7,  CS14_SW7,  CS13_SW7}, // <
    {0, CS18_SW6,  CS17_SW6,  CS16_SW6}, // >
    {0, CS18_SW7,  CS17_SW7,  CS16_SW7}, // ?
    {0, CS21_SW7,  CS20_SW7,  CS19_SW7}, // Shift R
    {0, CS24_SW6,  CS23_SW6,  CS22_SW6}, // UP
    {0, CS24_SW7,  CS23_SW7,  CS22_SW7}, // FN
    {0, CS27_SW6,  CS26_SW6,  CS25_SW6}, // F4
    {0, CS27_SW7,  CS26_SW7,  CS25_SW7}, // F9 // 66

// ROW 5
    {0, CS3_SW8,   CS2_SW8,   CS1_SW8},  // Ctrl // 67
    {0, CS3_SW9,   CS2_SW9,   CS1_SW9},  // Win
    {0, CS6_SW9,   CS5_SW9,   CS4_SW9},  // Alt L
    {0, CS9_SW9,   CS8_SW9,   CS7_SW9},  // Space L
    {0, CS12_SW9,  CS11_SW9,  CS10_SW9}, // Space M
    {0, CS15_SW9,  CS14_SW9,  CS13_SW9}, // Space R
    {0, CS18_SW9,  CS17_SW9,  CS16_SW9}, // Fn
    {0, CS18_SW8,  CS17_SW8,  CS16_SW8}, // Alt R
    {0, CS21_SW9,  CS20_SW9,  CS19_SW9}, // Win
    {0, CS21_SW8,  CS20_SW8,  CS19_SW8}, // Left
    {0, CS24_SW9,  CS23_SW9,  CS22_SW9}, // UP
    {0, CS24_SW8,  CS23_SW8,  CS22_SW8}, // FN
    {0, CS27_SW9,  CS26_SW9,  CS25_SW9}, // F4
    {0, CS27_SW8,  CS26_SW8,  CS25_SW8}, // F9 // 80

// Window
    {0, CS33_SW3,  CS32_SW3,  CS31_SW3}, // 81
    {0, CS33_SW7,  CS32_SW7,  CS31_SW7}, // 82
    {0, CS33_SW8,  CS32_SW8,  CS31_SW8}, // 83
    {0, CS33_SW6,  CS32_SW6,  CS31_SW6}, // 84

// Underglow
    {0, CS30_SW1,  CS29_SW1,  CS28_SW1}, // Center Top R (near +) now clockwise // 85
    {0, CS30_SW2,  CS29_SW2,  CS28_SW2},
    {0, CS30_SW4,  CS29_SW4,  CS28_SW4},
    {0, CS30_SW3,  CS29_SW3,  CS28_SW3},
    {0, CS30_SW5,  CS29_SW5,  CS28_SW5},
    {0, CS30_SW7,  CS29_SW7,  CS28_SW7},
    {0, CS30_SW6,  CS29_SW6,  CS28_SW6},
    {0, CS30_SW8,  CS29_SW8,  CS28_SW8},
    {0, CS30_SW9,  CS29_SW9,  CS28_SW9},

    {0, CS36_SW1,  CS35_SW1,  CS34_SW1}, // Center Top L (near *) now counter clockwise
    {0, CS36_SW2,  CS35_SW2,  CS34_SW2},
    {0, CS36_SW4,  CS35_SW4,  CS34_SW4},
    {0, CS36_SW3,  CS35_SW3,  CS34_SW3},
    {0, CS36_SW5,  CS35_SW5,  CS34_SW5},
    {0, CS36_SW7,  CS35_SW7,  CS34_SW7},
    {0, CS36_SW8,  CS35_SW8,  CS34_SW8},
    {0, CS36_SW6,  CS35_SW6,  CS34_SW6},
    {0, CS36_SW9,  CS35_SW9,  CS34_SW9},


// ISSI 2 Bottom LEDs
// ROW 1
    {1, CS36_SW1,  CS35_SW1,  CS34_SW1},
    {1, CS36_SW2,  CS35_SW2,  CS34_SW2},
    {1, CS39_SW1,  CS38_SW1,  CS37_SW1},
    {1, CS39_SW2,  CS38_SW2,  CS37_SW2},
    {1, CS3_SW1,   CS2_SW1,   CS1_SW1},
    {1, CS3_SW2,   CS2_SW2,   CS1_SW2},
    {1, CS6_SW1,   CS5_SW1,   CS4_SW1},
    {1, CS6_SW2,   CS5_SW2,   CS4_SW2},
    {1, CS9_SW1,   CS8_SW1,   CS7_SW1},
    {1, CS9_SW2,   CS8_SW2,   CS7_SW2},
    {1, CS12_SW1,  CS11_SW1,  CS10_SW1},
    {1, CS12_SW2,  CS11_SW2,  CS10_SW2},
    {1, CS15_SW1,  CS14_SW1,  CS13_SW1},
    {1, CS15_SW2,  CS14_SW2,  CS13_SW2},
    {1, CS18_SW1,  CS17_SW1,  CS16_SW1},
    {1, CS18_SW2,  CS17_SW2,  CS16_SW2},
    {1, CS21_SW1,  CS20_SW1,  CS19_SW1},

// ROW 2
    {1, CS36_SW3,  CS35_SW3,  CS34_SW3},
    {1, CS36_SW4,  CS35_SW4,  CS34_SW4},
    {1, CS39_SW3,  CS38_SW3,  CS37_SW3},
    {1, CS39_SW4,  CS38_SW4,  CS37_SW4},
    {1, CS3_SW3,   CS2_SW3,   CS1_SW3},
    {1, CS3_SW4,   CS2_SW4,   CS1_SW4},
    {1, CS6_SW3,   CS5_SW3,   CS4_SW3},
    {1, CS6_SW4,   CS5_SW4,   CS4_SW4},
    {1, CS9_SW3,   CS8_SW3,   CS7_SW3},
    {1, CS9_SW4,   CS8_SW4,   CS7_SW4},
    {1, CS12_SW3,  CS11_SW3,  CS10_SW3},
    {1, CS12_SW4,  CS11_SW4,  CS10_SW4},
    {1, CS15_SW3,  CS14_SW3,  CS13_SW3},
    {1, CS15_SW4,  CS14_SW4,  CS13_SW4},
    {1, CS18_SW3,  CS17_SW3,  CS16_SW3},
    {1, CS18_SW4,  CS17_SW4,  CS16_SW4},
    {1, CS21_SW3,  CS20_SW3,  CS19_SW3},

// ROW 3
    {1, CS36_SW5,  CS35_SW5,  CS34_SW5}, // Caps
    {1, CS36_SW6,  CS35_SW6,  CS34_SW6}, // A
    {1, CS39_SW5,  CS38_SW5,  CS37_SW5}, // S
    {1, CS39_SW6,  CS38_SW6,  CS37_SW6}, // D
    {1, CS3_SW5,   CS2_SW5,   CS1_SW5},  // F
    {1, CS3_SW6,   CS2_SW6,   CS1_SW6},  // G
    {1, CS6_SW5,   CS5_SW5,   CS4_SW5},  // H
    {1, CS6_SW6,   CS5_SW6,   CS4_SW6},  // J
    {1, CS9_SW5,   CS8_SW5,   CS7_SW5},  // K
    {1, CS9_SW6,   CS8_SW6,   CS7_SW6},  // L
    {1, CS12_SW5,  CS11_SW5,  CS10_SW5}, // ;
    {1, CS15_SW5,  CS14_SW5,  CS13_SW5}, // "
    {1, CS15_SW6,  CS14_SW6,  CS13_SW6}, // Enter
    {1, CS18_SW5,  CS17_SW5,  CS16_SW5}, // End
    {1, CS21_SW5,  CS20_SW5,  CS19_SW5}, // F3
    {1, CS21_SW4,  CS20_SW4,  CS19_SW4}, // F8

// ROW 4
    {1, CS36_SW7,  CS35_SW7,  CS34_SW7}, // Shift L
    {1, CS39_SW8,  CS38_SW8,  CS37_SW8}, // Z
    {1, CS39_SW7,  CS38_SW7,  CS37_SW7}, // X
    {1, CS3_SW8,   CS2_SW8,   CS1_SW8},  // C
    {1, CS3_SW7,   CS2_SW7,   CS1_SW7},  // V
    {1, CS6_SW8,   CS5_SW8,   CS4_SW8},  // B
    {1, CS6_SW7,   CS5_SW7,   CS4_SW7},  // N
    {1, CS9_SW8,   CS8_SW8,   CS7_SW8},  // M
    {1, CS9_SW7,   CS8_SW7,   CS7_SW7},  // <
    {1, CS12_SW6,  CS11_SW6,  CS10_SW6}, // >
    {1, CS12_SW7,  CS11_SW7,  CS10_SW7}, // ?
    {1, CS15_SW7,  CS14_SW7,  CS13_SW7}, // Shift R
    {1, CS18_SW6,  CS17_SW6,  CS16_SW6}, // Up
    {1, CS18_SW7,  CS17_SW7,  CS16_SW7}, // Fn
    {1, CS21_SW6,  CS20_SW6,  CS19_SW6}, // F4
    {1, CS21_SW7,  CS20_SW7,  CS19_SW7}, // F9

// ROW 5
    {1, CS36_SW8,  CS35_SW8,  CS34_SW8}, // Ctrl
    {1, CS36_SW9,  CS35_SW9,  CS34_SW9}, // Win
    {1, CS39_SW9,  CS38_SW9,  CS37_SW9}, // Alt L
    //{1, CS3_SW9,   CS2_SW9,   CS1_SW9},// Space L
    {1, CS6_SW9,   CS5_SW9,   CS4_SW9},  // Space M
    //{1, CS9_SW9,   CS8_SW9,   CS7_SW9},// Space R
    {1, CS12_SW9,  CS11_SW9,  CS10_SW9}, // Fn
    {1, CS12_SW8,  CS11_SW8,  CS10_SW8}, // Alt R
    {1, CS15_SW9,  CS14_SW9,  CS13_SW9}, // Win
    {1, CS15_SW8,  CS14_SW8,  CS13_SW8}, // Left
    {1, CS18_SW9,  CS17_SW9,  CS16_SW9}, // Down
    {1, CS18_SW8,  CS17_SW8,  CS16_SW8}, // Right
    {1, CS21_SW9,  CS20_SW9,  CS19_SW9}, // F5
    {1, CS21_SW8,  CS20_SW8,  CS19_SW8}  // F10
};

#define __ NO_LED

#define NORTH_LED       ( LED_FLAG_KEYLIGHT  )
#define SOUTH_LED       ( LED_FLAG_KEYLIGHT  )
#define NORTH_MODIFIER  ( LED_FLAG_MODIFIER  )
#define SOUTH_MODIFIER  ( LED_FLAG_MODIFIER  )
#define NORTH_INDICATOR ( LED_FLAG_INDICATOR )
#define SOUTH_INDICATOR ( LED_FLAG_INDICATOR )
#define NORTH_CAPSLOCK  ( NORTH_MODIFIER | NORTH_INDICATOR )
#define SOUTH_CAPSLOCK  ( SOUTH_MODIFIER | SOUTH_INDICATOR )

// #define NORTH_LED       (        32 | LED_FLAG_KEYLIGHT  )
// #define SOUTH_LED       (        64 | LED_FLAG_KEYLIGHT  )
// #define NORTH_MODIFIER  ( NORTH_LED | LED_FLAG_MODIFIER  )
// #define SOUTH_MODIFIER  ( SOUTH_LED | LED_FLAG_MODIFIER  )
// #define NORTH_INDICATOR ( NORTH_LED | LED_FLAG_INDICATOR )
// #define SOUTH_INDICATOR ( SOUTH_LED | LED_FLAG_INDICATOR )
// #define NORTH_CAPSLOCK  ( NORTH_MODIFIER | NORTH_INDICATOR )
// #define SOUTH_CAPSLOCK  ( SOUTH_MODIFIER | SOUTH_INDICATOR )

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, __ },
  {  18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, __ },
  {  35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, __, 47, 48, 49, 50, __ },
  {  51, 52, 53, 54, 55, 56, 57, 58, 59, __, 60, 61, 62, 63, 64, 65, 66, __ },
  {  67, 68, 69, __, __, __, 71, __, 73, __, 74, 75, 76, 77, 78, 79, 80, __ }
}, {
  // LED Index to Physical Position
  // North Facing LEDs ISSI 1
  {6, 2}, 	{18, 2}, 	{29, 2}, 	{41, 2}, 	{53, 2}, 	{65, 2}, 	{77, 2}, 	{88, 2}, 	{100, 2}, 	{112, 2}, 	{124, 2}, 	{136, 2}, 	{147, 2}, 	{165, 2}, 	{183, 2}, 		{200, 2}, 	{212, 2},
  {9, 15}, 	{24, 15}, 	{35, 15}, 	{47, 15}, 	{59, 15}, 	{71, 15}, 	{83, 15}, 	{94, 15}, 	{106, 15}, 	{118, 15}, 	{130, 15}, 	{141, 15}, 	{153, 15}, 	{168, 15}, 	{183, 15}, 		{200, 15}, 	{212, 15},
  {10, 27}, {27, 27}, 	{38, 27}, 	{50, 27}, 	{62, 27}, 	{74, 27}, 	{85, 27}, 	{97, 27}, 	{109, 27}, 	{121, 27}, 	{133, 27}, 	{144, 27}, 		        {164, 27}, 	{183, 27}, 		{200, 27}, 	{212, 27},
  {13, 40}, {32, 40}, 	{44, 40}, 	{56, 40}, 	{68, 40}, 	{80, 40}, 	{91, 40}, 	{103, 40}, 	{115, 40}, 		        {127, 40}, 	{139, 40}, 	{150, 40}, 	{167, 40}, 	{183, 40}, 		{200, 40}, 	{212, 40},
  {7, 53}, 	{22, 53}, 	{37, 53}, 	{50, 53}, 		        {81, 53}, 		        {112, 53}, 	{124, 53}, 		        {136, 53}, 	{147, 53}, 	{159, 53}, 	{171, 53}, 	{183, 53}, 		{200, 53}, 	{212, 53},

  // Window
  {221, 22},
  {218, 38},
  {218, 51},
  {218, 63},

  // Underglow
  {130, 0}, {177, 0},   {206, 0},   {224, 0},   {224, 22},  {224, 55},  {206, 64},  {165, 64},  {130, 64},
  {94, 0},  {51, 0},    {24, 0},    {0, 13},    {0, 37},    {0, 58},    {29, 64},   {59, 64},   {97, 64},

  // South Facing LEDs ISSI 2
  {6, 11}, 	{18, 11}, 	{29, 11}, 	{41, 11}, 	{53, 11}, 	{65, 11}, 	{77, 11}, 	{88, 11}, 	{100, 11}, 	{112, 11}, 	{124, 11}, 	{136, 11}, 	{147, 11}, 	{165, 11}, 	{183, 11}, 		{200, 11}, 	{212, 11},
  {9, 24}, 	{24, 24}, 	{35, 24}, 	{47, 24}, 	{59, 24}, 	{71, 24}, 	{83, 24}, 	{94, 24}, 	{106, 24}, 	{118, 24}, 	{130, 24}, 	{141, 24}, 	{153, 24}, 	{168, 24}, 	{183, 24}, 		{200, 24}, 	{212, 24},
  {10, 37}, {27, 37}, 	{38, 37}, 	{50, 37}, 	{62, 37}, 	{74, 37}, 	{85, 37}, 	{97, 37}, 	{109, 37}, 	{121, 37}, 	{133, 37}, 	{144, 37}, 		        {164, 37}, 	{183, 37}, 		{200, 37}, 	{212, 37},
  {13, 49}, {32, 49}, 	{44, 49}, 	{56, 49}, 	{68, 49}, 	{80, 49}, 	{91, 49}, 	{103, 49}, 	{115, 49}, 		        {127, 49}, 	{139, 49}, 	{150, 49}, 	{167, 49}, 	{183, 49}, 		{200, 49}, 	{212, 49},
  {7, 62}, 	{22, 62}, 	{37, 62}, 			                {81, 62}, 			                {124, 62}, 		        {136, 62}, 	{147, 62}, 	{159, 62}, 	{171, 62}, 	{183, 62}, 		{200, 62}, 	{212, 62}
}, {
  // LED Index to Flag
  // North Facing LEDs
  NORTH_MODIFIER,   NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED,    NORTH_LED,      NORTH_LED,      NORTH_MODIFIER,    NORTH_MODIFIER, NORTH_MODIFIER,
  NORTH_MODIFIER,   NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED,    NORTH_LED,      NORTH_LED,      NORTH_MODIFIER,    NORTH_MODIFIER, NORTH_MODIFIER,
  NORTH_CAPSLOCK,   NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED,                    NORTH_LED,      NORTH_MODIFIER,    NORTH_MODIFIER, NORTH_MODIFIER,
  NORTH_MODIFIER,   NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_LED,               NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER,    NORTH_MODIFIER, NORTH_MODIFIER,
  NORTH_MODIFIER,   NORTH_MODIFIER, NORTH_MODIFIER, NORTH_LED, NORTH_LED, NORTH_LED, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER, NORTH_MODIFIER,

  // Window
  LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

  // Underglow 2*9
  LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
  LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

  // South Facing LEDs
  SOUTH_MODIFIER,   SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED,    SOUTH_LED,      SOUTH_LED,      SOUTH_MODIFIER,    SOUTH_MODIFIER, SOUTH_MODIFIER,
  SOUTH_MODIFIER,   SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED,    SOUTH_LED,      SOUTH_LED,      SOUTH_MODIFIER,    SOUTH_MODIFIER, SOUTH_MODIFIER,
  SOUTH_CAPSLOCK,   SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED,                    SOUTH_LED,      SOUTH_MODIFIER,    SOUTH_MODIFIER, SOUTH_MODIFIER,
  SOUTH_MODIFIER,   SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED, SOUTH_LED,               SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER,    SOUTH_MODIFIER, SOUTH_MODIFIER,
  SOUTH_MODIFIER,   SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_LED, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER, SOUTH_MODIFIER
} };

#endif // RGB_MATRIX_ENABLE

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#else
    #define CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#endif

#ifdef RGB_MATRIX_VAL_STEP
    #define CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#else
    #define CAPS_LOCK_VAL_STEP 8
#endif

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        uint8_t b = rgb_matrix_get_val();
        if (b < CAPS_LOCK_VAL_STEP) {
            b = CAPS_LOCK_VAL_STEP;
        } else if (b < (CAPS_LOCK_MAX_BRIGHTNESS - CAPS_LOCK_VAL_STEP)) {
            b += CAPS_LOCK_VAL_STEP;  // one step more than current brightness
        } else {
            b = CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, b, b, b);  // white, with the adjusted brightness
    }
    return true;
}
#endif

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
    }
    return true;
}

// bool issiInit = false;

// static void initIssi(void);

// bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
//     switch(keycode) {
//     #ifdef RGB_MATRIX_ENABLE
//         case KC_A: // toggle rgb matrix
//         print("Toggle RGB\n");
//         rgb_matrix_toggle();
//         return false;
//         case KC_B:
//         rgb_matrix_step();
//         print("RGB step\n");
//         print(status);
//         uprintf( "Received ID: 0x%02X\n", id );
//         // if ( !issiInit ) {
//         //     initIssi();
//         //     issiInit = true;
//         // }
//         return false;
//     #endif
//         default:
//         break;
//     }
//   }
//   return process_record_user(keycode, record);
// }

// static void initIssi(void) {
//     IS31FL3741_init(DRIVER_ADDR_1);

//     IS31FL3741_set_led_control_register(0, true, true, true);
//     IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);
// }

// i2c_status_t ret;


// Custom Driver
// static void init(void) {
//     setPinOutput( A5 );

//     i2c_init();

//     print("right after i2c init printing... hope that works?");

//     uint8_t IS31FL3741_REG_ID = 0xFC;
//     uint16_t delay = 0xFFU;
//     // if ( i2c_readReg( 0x60, IS31FL3741_REG_ID, &id, 1U, delay ) == 0 ) {
//     //     status = "Success\n";
//     // } else {
//     //     status = "ReadReg error\n";
//     // }
//     if ( i2c_transmit( DRIVER_ADDR_1 << 1, &IS31FL3741_REG_ID, 0x00000001U, delay ) == 0 ) {
//         if ( i2c_receive( DRIVER_ADDR_1 << 1, &id, 0x00000001U, delay ) == 0 ) {
//             if ( id == DRIVER_ADDR_1 << 1 ) {
//                 status = "Success\n";
//                 writePinHigh( A5 );
//             }
//         } else {
//             status = "Unable to receive after successful initial transmit\n";
//         }
//     } else {
//         status = "Error during first transmit of reg address\n";
//     }

//     IS31FL3741_init(DRIVER_ADDR_1);

//     // sets scaling registers to 0xFF
//     for ( int i = 0; i < RGB_MATRIX_LED_COUNT; i++ )
//         IS31FL3741_set_led_control_register(i, true, true, true);
//     IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);

//     print("Init ISSI finished\n");
// }

// static void flush(void) {
//     IS31FL3741_update_pwm_buffers(DRIVER_ADDR_1, 0);
//     // print("Flush ISSI\n");
//     wait_ms(10);
// }

// static void set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
//     IS31FL3741_set_color(index, red, green, blue);
//     wait_ms(10);
// }

// static void set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
//     IS31FL3741_set_color_all( red, green, blue );
//     // uprintf("Set all colors on ISSI [0x%02X, 0x%02X, 0x%02X]\n", red, green, blue);
//     wait_ms(10);
// }

// const rgb_matrix_driver_t rgb_matrix_driver = {
//     .init = init,
//     .flush = flush,
//     .set_color = set_color,
//     .set_color_all = set_color_all
// };
