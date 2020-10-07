#include "adc_config.h"

void ADC1_Config()
{ 
  __IO uint32_t wait_loop_index = 0UL; 

   RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
   RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
   
   RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
   RCC->APB4ENR |= RCC_APB4ENR_VREFEN;
   RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;

   
   GPIOB-> MODER   |= 0x03<<2;                // ADC1_channel 5     
   GPIOB-> OSPEEDR |= 0x03<<2;
   GPIOB-> PUPDR   &= ~(0x03<<2);
  
   GPIOC-> MODER   |= 0x03<<8;                 // ADC2_channel 4
   GPIOC-> OSPEEDR |= 0x03<<8;
   GPIOC-> PUPDR   &= ~(0x03<<8);
   
   CLEAR_BIT(ADC1->CR, (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART | ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN));    
   CLEAR_BIT(ADC1->CR, ADC_CR_DEEPPWD );
   MODIFY_REG(ADC1->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADVREGEN);
   wait_loop_index = SystemCoreClock / (100000UL * 2UL);
   while (wait_loop_index != 0UL)
   {
      wait_loop_index--;
   }
   MODIFY_REG(ADC1->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADEN); // set ADEN = 1

   ADC1->CFGR  |= 0x000004E8;
   ADC1->SMPR1 |= 0x00028000;
   ADC1->PCSEL |= 0x00000020;
   ADC1->SQR1  |= 0x00000140;
   
   ADC1->IER   |= 0x00000014;                // config interrupt ADC 
   ADC12_COMMON->CCR   |= ADC_CCR_VREFEN; 


   // procedure to enable the ADC - STM32H7 manual
   ADC1->CR    |= 0x0100;                       // boost mode control used when ADC clock > 20 Mhz
   ADC1->ISR   |= ADC_ISR_ADRDY;               // clear ADRDY bit in the ADC_ISR register
 //  MODIFY_REG(ADC1->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADEN); // set ADEN = 1
   while(ADC1->ISR &&0x01 != 0);
   ADC1->ISR   |= ADC_ISR_ADRDY;             // clear ADRDY bit in the ADC_ISR register

   ADC1->IER   |= 0x00000001;                // config interrupt ADC 

   MODIFY_REG(ADC1->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADSTART);// start ADC conversion of regular channels   
   NVIC->ISER[ADC_IRQn >> 5UL] = (uint32_t)(1UL << (ADC_IRQn& 0x1FUL));

}

int adc_vl;
void ADC_IRQHandler(void)
{
   adc_vl = ADC1->DR;
  
   ADC1->ISR &= ~(ADC_ISR_EOC|ADC_ISR_EOS); // clear interrupt flag
}