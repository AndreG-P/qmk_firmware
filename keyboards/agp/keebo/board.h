
#pragma once

#include_next <board.h>

// Having a 24MHz crystal on the board
// Setting PMML factor in mcuconf.h
#undef STM32_HSECLK
#define STM32_HSECLK 24000000U

#ifndef BOARD_OTG_NOVBUSSENS
    #define BOARD_OTG_NOVBUSSENS
#endif

#undef STM32_HSE_BYPASS
