#include "stm32f4xx.h"
#define RS 0x20 /* PB5 mask for reg select */ #define RW 0x40 /* PB6
mask for read/write */ #define EN 0x80 /* PB7 mask for enable */
void
void
void
void
delayMs(int n);
LCD_command(unsigned char command); void LCD_data(char data);
LCD_init(void);
PORTS_init(void);
int main(void) {
/* initialize LCD controller */ LCD_init();
LCD_data('l'); LCD_data('o'); delayMs(1000);
while(1) {
/* Write "hello" on LCD */ LCD_data('h');
LCD_data('e');
LCD_data('l');
/* clear LCD display */ LCD_command(1);
delayMs(500);
}
}
/* initialize port pins then initialize LCD controller */ void
LCD_init(void) {
PORTS_init();
delayMs(30); /* initialization sequence */ LCD_command(0x30);
delayMs(10);
LCD_command(0x30);
delayMs(1);
LCD_command(0x30);
LCD_command(0x38);
LCD_command(0x06);
LCD_command(0x01);
LCD_command(0x0F);
/*
/*
/*
/*
set 8-bit data, 2-line, 5x7 font */
move cursor right after each char */
clear screen, move cursor to home */
turn on display, cursor blinking */}
void PORTS_init(void) {
RCC->AHB1ENR |= 0x06; /* enable GPIOB/C clock */
/* PB5 for LCD R/S */
/* PB6 for LCD R/W */
/* PB7 for LCD EN */
GPIOB->MODER &= ~0x0000FC00; /* clear pin mode */ GPIOB->MODER |=
0x00005400; /* set pin output mode */ GPIOB->BSRR = 0x00C00000; /*
turn off EN and R/W */
/* PC0-PC7 for LCD D0-D7, respectively. */
GPIOC->MODER &= ~0x0000FFFF; /* clear pin mode */ GPIOC->MODER |=
0x00005555; /* set pin output mode */
}
void LCD_command(unsigned char command) {
GPIOB->BSRR = (RS | RW) << 16; /* RS = 0, R/W = 0 */ GPIOC->ODR =
command; /* put command on data bus */ GPIOB->BSRR = EN; /* pulse E
high */ delayMs(0);
GPIOB->BSRR = EN << 16; /* clear E */
if (command < 4)
delayMs(2); /* command 1 and 2 needs up to 1.64ms */
else
delayMs(1); /* all others 40 us */
}
GPIOC->ODR = data; /* put data on data bus */ GPIOB->BSRR = EN; /*
pulse E high */ delayMs(0);
GPIOB->BSRR = EN << 16; /* clear E */
void LCD_data(char data) {
GPIOB->BSRR = RS; /* RS = 1 */ GPIOB->BSRR = RW << 16; /* R/W = 0 */
delayMs(1); }
/* delay n milliseconds (16 MHz CPU clock) */ void delayMs(int n) {
int i;
for (; n > 0; n--)
for (i = 0; i < 3195; i++) ;
}
