#include "tim_config.h"


//uint16_t arr[350]={2047 , 1610 , 1007 , 435 , 80 , 58 , 371 , 911 , 1494 , 1921 , 2048 , 1835 , 1354 , 773 , 291 , 78 , 211 , 654 , 1266 , 1848 , 2216 , 2257 , 1968 , 1461 , 920 , 544 , 474 , 751 , 1296 , 1944 , 2492 , 2775 , 2714 , 2349 , 1822 , 1331 , 1060 , 1121 , 1512 , 2120 , 2760 , 3234 , 3400 , 3222 , 2777 , 2233 , 1792 , 1619 , 1788 , 2259 , 2886 , 3472 , 3833 , 3858 , 3551 , 3027 , 2472 , 2083 , 1998 , 2254 , 2770 , 3376 , 3871 , 4091 , 3963 , 3530 , 2938 , 2386 , 2057 , 2057 , 2383 , 2918 , 3474 , 3855 , 3924 , 3647 , 3107 , 2474 , 1950 , 1698 , 1789 , 2177 , 2716 , 3207 , 3468 , 3392 , 2989 , 2375 , 1740 , 1280 , 1130 , 1322 , 1773 , 2309 , 2732 , 2878 , 2679 , 2184 , 1541 , 949 , 590 , 568 , 873 , 1386 , 1917 , 2273 , 2318 , 2023 , 1476 , 848 , 341 , 115 , 239 , 660 , 1230 , 1750 , 2038 , 1994 , 1628 , 1063 , 487 , 97 , 24 , 296 , 823 , 1434 , 1925 , 2139 , 2010 , 1590 , 1032 , 533 , 273 , 354 , 759 , 1367 , 1987 , 2424 , 2546 , 2330 , 1864 , 1325 , 911 , 782 , 999 , 1508 , 2157 , 2745 , 3093 , 3103 , 2791 , 2281 , 1765 , 1436 , 1424 , 1750 , 2322 , 2965 , 3478 , 3704 , 3581 , 3168 , 2616 , 2126 , 1877 , 1963 , 2368 , 2963 , 3557 , 3957 , 4035 , 3771 , 3258 , 2674 , 2219 , 2048 , 2219 , 2674 , 3258 , 3771 , 4035 , 3957 , 3557 , 2963 , 2368 , 1963 , 1877 , 2126 , 2616 , 3168 , 3581 , 3704 , 3478 , 2965 , 2322 , 1750 , 1424 , 1436 , 1765 , 2281 , 2791 , 3103 , 3093 , 2745 , 2157 , 1508 , 999 , 782 , 911 , 1325 , 1864 , 2330 , 2546 , 2424 , 1987 , 1367 , 759 , 354 , 273 , 533 , 1032 , 1590 , 2010 , 2139 , 1925 , 1434 , 823 , 296 , 24 , 97 , 487 , 1063 , 1628 , 1994 , 2038 , 1750 , 1230 , 660 , 239 , 115 , 341 , 848 , 1476 , 2023 , 2318 , 2273 , 1917 , 1386 , 873 , 568 , 590 , 949 , 1541 , 2184 , 2679 , 2878 , 2732 , 2309 , 1773 , 1322 , 1130 , 1280 , 1740 , 2375 , 2989 , 3392 , 3468 , 3207 , 2716 , 2177 , 1789 , 1698 , 1950 , 2474 , 3107 , 3647 , 3924 , 3855 , 3474 , 2918 , 2383 , 2057 , 2057 , 2386 , 2938 , 3530 , 3963 , 4091 , 3871 , 3376 , 2770 , 2254 , 1998 , 2083 , 2472 , 3027 , 3551 , 3858 , 3833 , 3472 , 2886 , 2259 , 1788 , 1619 , 1792 , 2233 , 2777 , 3222 , 3400 , 3234 , 2760 , 2120 , 1512 , 1121 , 1060 , 1331 , 1822 , 2349 , 2714 , 2775 , 2492 , 1944 , 1296 , 751 , 474 , 544 , 920 , 1461 , 1968 , 2257 , 2216 , 1848 , 1266 , 654 , 211 , 78 , 291 , 773 , 1354 , 1835 , 2048 , 1921 , 1494 , 911 , 371 , 58 , 80 , 435 , 1007 , 1610 };


/***************************** TIM1 Configure ********************************/

void TIM1_Config(uint16_t prescaler, uint32_t period)
{
    /* TIM1 use APB2 clock is 240 MHz */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
      
    uint32_t tmpcr1 = TIM1->CR1;  

    // Select the Counter Mode 
    tmpcr1 &= (uint16_t)(~(TIM_CR1_DIR | TIM_CR1_CMS));
    // Set the clock division
    tmpcr1 &=  (uint16_t)(~TIM_CR1_CKD);
    // Set Auto-reload preload enable 
    tmpcr1 |= TIM_CR1_ARPE; 
    // Set Counter enable 
    tmpcr1 |= 1; 

    TIM1-> PSC = prescaler - 1; 
    TIM1-> ARR = period - 1; 
    TIM1-> EGR |= 0x01; 
  
    // Reset the MMS Bits 
    TIM1->CR2 &= (uint16_t)~TIM_CR2_MMS;
    // Select the TRGO source 
    TIM1->CR2 |= 0x02<<4;
    
    /* Configure is used for interupt update */
    
    // enable interupt 
    TIM1-> DIER |= 0x01;
    // set interupt
    NVIC->ISER[TIM1_UP_IRQn >> 5UL] = 0x01 << (TIM1_UP_IRQn & 0x1FUL);
    
    // Clear interupt TIM_SR
    TIM1->SR &= ~0x01;
   
    // Set TIMx control register 1 
    TIM1->CR1 = tmpcr1;
}
uint16_t  y[350] , cnt = 0, k, adc1_vl;
         /********************* INTERUPT TIM1 ********************/
void TIM1_UP_IRQHandler(void)      // sub = 2
{
    if ((TIM1->SR & 0x01) != RESET && (TIM1->DIER & 0x01) != RESET )
    {
 
       adc1_vl = ADC1->DR;
        /* your code */
        TIM1->SR &= ~0x01;
    }
}
/****************************************************************************/



/***************************** TIM8 Configure ********************************/
void TIM8_Config(uint16_t prescaler, uint32_t period)
{
    /* TIM1 use APB2 clock is 240 MHz */
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
      
    uint32_t tmpcr1 = TIM8->CR1;  

    // Select the Counter Mode 
    tmpcr1 &= (uint16_t)(~(TIM_CR1_DIR | TIM_CR1_CMS));
    // Set the clock division
    tmpcr1 &=  (uint16_t)(~TIM_CR1_CKD);
    // Set Auto-reload preload enable 
    tmpcr1 |= TIM_CR1_ARPE; 
    // Set Counter enable 
    tmpcr1 |= 1; 

    TIM8-> PSC = prescaler - 1; 
    TIM8-> ARR = period - 1; 
    TIM8-> EGR |= 0x01; 
  
    // Reset the MMS Bits 
    TIM8->CR2 &= (uint16_t)~TIM_CR2_MMS;
    // Select the TRGO source 
    TIM8->CR2 |= 0x02<<4;
    
    /* Configure is used for interupt update */
  
    // enable interupt 
    TIM8-> DIER |= 0x01;
    // set interupt
    NVIC->ISER[TIM8_UP_TIM13_IRQn >> 5UL] = 0x01 << (TIM8_UP_TIM13_IRQn & 0x1FUL);
 
    // Clear interupt TIM_SR
    TIM8->SR &= ~0x01;
    
    // Set TIMx control register 1 
    TIM8->CR1 = tmpcr1;
}
         /********************* INTERUPT TIM8 ********************/
void TIM8_UP_TIM13_IRQHandler(void)      // sub = 2
{
    if ((TIM8->SR & 0x01) != RESET && (TIM8->DIER & 0x01) != RESET )
    {
      
         /* your code */
        TIM8->SR &= ~0x01;
    }
}
/****************************************************************************/