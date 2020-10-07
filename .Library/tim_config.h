#ifndef _TIM_CONFIG_
#define _TIM_CONFIG_
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_gpio.h"
#include "Lib_iir_filter.h"

void TIM1_Config(uint16_t prescaler, uint32_t period);
void TIM8_Config(uint16_t prescaler, uint32_t period);

#endif