#ifndef _LIB_IIR_FILTER_H_
#define _LIB_IIR_FILTER_H_

#include "stm32h750xx.h"
#include "stdio.h"
#include "math.h"
#include "stdint.h"

void       initialization();
float      section_filter(float x ,uint8_t sections);
uint16_t   iir_filter(uint16_t in);

#endif
