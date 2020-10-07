#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_


#include "stdio.h"
#include "stm32h7xx.h"

#define ADC_CR_BITS_PROPERTY_RS  (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART | ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN) 

void ADC1_Config();

#endif
