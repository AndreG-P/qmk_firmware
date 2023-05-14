#include "print.h"

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

#   ifdef RGB_MATRIX_KEYREACTIVE_AGP_ENABLED
        RGB_MATRIX_EFFECT(SOLID_SPLASH_PINWHEEL_BASE)
#   endif

#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV CUSTOM_SPLASH_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - (dist << 1);
    if (effect > 255) effect = 255;
    hsv.h += effect;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

static HSV CUSTOM_PINWHEEL_math(HSV hsv, int16_t dx, int16_t dy, uint16_t time) {
    hsv.v = scale8(hsv.v - time - atan2_8(dy, dx) * 4, qadd8(hsv.v, hsv.v));
    return hsv;
}

static bool calculate_Layered_Splash(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 2);
    uint8_t count = g_last_hit_tracker.count;
    uint8_t originalHue = rgb_matrix_config.hsv.h;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;

        int16_t dx  = g_led_config.point[i].x - k_rgb_matrix_center.x;
        int16_t dy  = g_led_config.point[i].y - k_rgb_matrix_center.y;
        hsv = CUSTOM_PINWHEEL_math(hsv, dx, dy, time);
        hsv.h = originalHue;

        // hsv.v = 0;
        for (uint8_t j = 0; j < count; j++) {
            int16_t  hit_dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  hit_dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(hit_dx * hit_dx + hit_dy * hit_dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = CUSTOM_SPLASH_math(hsv, hit_dx, hit_dy, dist, tick);
        }

        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

static bool SOLID_SPLASH_PINWHEEL_BASE(effect_params_t* params) {
    // print("Active pinwheel\n");
    return calculate_Layered_Splash(params);
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
