#pragma once

#include_next <board.h>

#undef STM32_HSE_BYPASS
#undef STM32_HSECLK
#define STM32_HSECLK 24000000U
