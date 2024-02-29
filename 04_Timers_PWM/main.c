#include"tim.h"
#define GPIOAEN     (1U<<0)
#define PIN5        (1U<<5)
#define LED          PIN5
int main(void)
{
	RCC ->AHB1ENR |= GPIOAEN:
	GPIOA-> MODER &= ~0x00000C00;
	GPIOA->MODER |=0x00000400;
	tim2_1hz_init();
	while(1)
	{
		tim_delay();
		GPIOA->ODR ^=LED;
	}
}
