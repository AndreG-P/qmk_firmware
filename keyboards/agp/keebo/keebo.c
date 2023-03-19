#include "keebo.h"
#include "print.h"
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3741.h"
// #include "gpio.h"

char *status;
uint8_t id = 0xFF;

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, CS3_SW9,   CS2_SW9,   CS1_SW9},
    {0, CS18_SW9,  CS17_SW9,  CS16_SW9},
    {0, CS15_SW1,  CS14_SW1,  CS13_SW1},
    {0, CS30_SW1,  CS29_SW1,  CS28_SW1}
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0  },
  {  2  }
}, {
  // LED Index to Physical Position
  { 112,  64 },
  { 112,  48 },
  { 112,  16 },
  { 112,   0 }
}, {
  // LED Index to Flag
  4, 4, 4, 4
} };

bool issiInit = false;

// static void initIssi(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGB_MATRIX_ENABLE
        case KC_A: // toggle rgb matrix
        print("Toggle RGB\n");
        rgb_matrix_toggle();
        return false;
        case KC_B:
        rgb_matrix_step();
        print("RGB step\n");
        print(status);
        uprintf( "Received ID: 0x%02X\n", id );
        // if ( !issiInit ) {
        //     initIssi();
        //     issiInit = true;
        // }
        return false;
    #endif
        default:
        break;
    }
  }
  return process_record_user(keycode, record);
}

// static void initIssi(void) {
//     IS31FL3741_init(DRIVER_ADDR_1);

//     IS31FL3741_set_led_control_register(0, true, true, true);
//     IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);
// }

i2c_status_t ret;


// Custom Driver
static void init(void) {
    setPinOutput( A5 );

    i2c_init();

    print("right after i2c init printing... hope that works?");

    uint8_t IS31FL3741_REG_ID = 0xFC;
    uint16_t delay = 0xFFU;
    // if ( i2c_readReg( 0x60, IS31FL3741_REG_ID, &id, 1U, delay ) == 0 ) {
    //     status = "Success\n";
    // } else {
    //     status = "ReadReg error\n";
    // }
    if ( i2c_transmit( DRIVER_ADDR_1 << 1, &IS31FL3741_REG_ID, 0x00000001U, delay ) == 0 ) {
        if ( i2c_receive( DRIVER_ADDR_1 << 1, &id, 0x00000001U, delay ) == 0 ) {
            if ( id == DRIVER_ADDR_1 << 1 ) {
                status = "Success\n";
                writePinHigh( A5 );
            }
        } else {
            status = "Unable to receive after successful initial transmit\n";
        }
    } else {
        status = "Error during first transmit of reg address\n";
    }

    IS31FL3741_init(DRIVER_ADDR_1);

    // sets scaling registers to 0xFF
    for ( int i = 0; i < RGB_MATRIX_LED_COUNT; i++ )
        IS31FL3741_set_led_control_register(i, true, true, true);
    IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);

    print("Init ISSI finished\n");
}

static void flush(void) {
    IS31FL3741_update_pwm_buffers(DRIVER_ADDR_1, 0);
    // print("Flush ISSI\n");
    wait_ms(10);
}

static void set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    IS31FL3741_set_color(index, red, green, blue);
    wait_ms(10);
}

static void set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    IS31FL3741_set_color_all( red, green, blue );
    // uprintf("Set all colors on ISSI [0x%02X, 0x%02X, 0x%02X]\n", red, green, blue);
    wait_ms(10);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = set_color,
    .set_color_all = set_color_all
};
