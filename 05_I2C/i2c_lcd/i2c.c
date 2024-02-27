
#include "i2c.h"
#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; //enable gpiob clock
RCC->APB1ENR|=RCC_APB1ENR_I2C1EN; //enable i2c1 clock
GPIOB->MODER|=0xA0000; //set pb8and9 to alternative function
GPIOB->AFR[1]|=0x44;
GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; //set pb8 and pb9 as open drain

I2C1->CR1=0x8000;
I2C1->CR1&=~0x8000;
I2C1->CR2|=0x10;
I2C1->CCR=80; //standard 100KHz
I2C1->TRISE=17;
I2C1->CR1|=0x1;
	
}

