#include "dac_config.h"

void DAC1_Config()
{
     RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
     RCC->APB1LENR |= RCC_APB1LENR_DAC12EN;
     
     GPIOA->MODER |= 0x03<<8;
     GPIOA->OSPEEDR |= 0x03<<8;
     GPIOA->PUPDR &= ~(0x03<<8); 
     
     DAC1->CR &= ~0x01;       //disable DAC befor setting DAC

     //set up SHSR2
     //set up SHHR
     //set up SHRR
     //set up CCR
     //set up MCR
     //set up CR
       DAC1->CCR &= ~(((uint32_t)(DAC_CCR_OTRIM1)) );
 
      /* Configure for the selected DAC channel: mode, buffer output & on chip peripheral connect */
      /* Write to DAC MCR */
       DAC1->MCR &= ~(((uint32_t)(0x00000007)));

      /* Clear TENx, TSELx, WAVEx and MAMPx bits */
       DAC1->CR &= ~(((uint32_t)(DAC_CR_MAMP1 | DAC_CR_WAVE1 | DAC_CR_TSEL1 | DAC_CR_TEN1)) );
      
       DAC1->CR |= 0x01;       //disable DAC befor setting DAC
       
       SET_BIT(DAC1->SWTRIGR, DAC_SWTRIGR_SWTRIG1);
}