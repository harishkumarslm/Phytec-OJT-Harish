#include "stm32f4xx.h" void delayMs(int n);
void LCD_command(unsigned char command); void
LCD_command_noPoll(unsigned char command); void LCD_data(char data);
void LCD_init(void);
void LCD_ready(void);
void PORTS_init(void);
#define RS 0x20 /* PB5 mask for reg select */ #define RW 0x40 /* PB6
mask for read/write */ #define EN 0x80 /* PB7 mask for enable */
int main(void) {
/* initialize LCD controller */ LCD_init();
while(1) {
/* Write "Hello" on LCD */ LCD_data('H');
LCD_data('e');
LCD_data('l');LCD_data('l');
LCD_data('o');
delayMs(500);
/* clear LCD display */ LCD_command(1);
delayMs(500);
}
}
/* Initialize port pins then initialize LCD controller */ void
LCD_init(void) {
PORTS_init();
delayMs(30); /* initialization sequence */
LCD_command_noPoll(0x30); /* LCD does not respond to status poll yet
*/ delayMs(10);
LCD_command_noPoll(0x30);
delayMs(1);
LCD_command_noPoll(0x30); /* busy flag cannot be polled before this
*/
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
turn on display, cursor blinking */
}
void PORTS_init(void) {
RCC->AHB1ENR |= 0x06; /* enable GPIOB/C clock */
/* PB5 for LCD R/S */
/* PB6 for LCD R/W */
/* PB7 for LCD EN */
GPIOB->MODER &= ~0x0000FC00; /* clear pin mode */ GPIOB->MODER |=
0x00005400; /* set pin output mode */ GPIOB->BSRR = 0x00C00000; /*
turn off EN and R/W */ /* This function waits until LCD controller
is ready to
/* PC0-PC7 for LCD D0-D7, respectively. */
GPIOC->MODER &= ~0x0000FFFF; /* clear pin mode */ GPIOC->MODER |=
0x00005555; /* set pin output mode */
}
* accept a new command/data before returns.
* It polls the busy bit of the status register of LCD controller. *
In order to read the status register, the data port of the *
microcontroller has to change to an input port before reading * the
LCD. The data port of the microcontroller is return to * output port
before the end of this function.
*/void LCD_ready(void) {
char status;
/* change to read configuration to poll the status register */
GPIOC->MODER &= ~0x0000FFFF; /* clear pin mode */ GPIOB->BSRR = RS
<< 16; /* RS = 0 for status register */ GPIOB->BSRR = RW; /* R/W = 1
for read */
do { /* stay in the loop until it is not busy */ GPIOB->BSRR = EN;
/* pulse E high */ delayMs(0);
status = GPIOC->IDR; /* read status register */ GPIOB->BSRR = EN <<
16; /* clear E */
delayMs(0);
} while (status & 0x80); /* check busy bit */
/* return to default write configuration */
GPIOB->BSRR = RW << 16; /* R/W = 0, LCD input */ GPIOC->MODER |=
0x00005555; /* Port C as output */
}
void LCD_command(unsigned char command) {
LCD_ready(); /* wait for LCD controller ready */ GPIOB->BSRR = (RS |
RW) << 16; /* RS = 0, R/W = 0 */ GPIOC->ODR = command; /* put
command on data bus */ GPIOB->BSRR = EN; /* pulse E high */
delayMs(0);
GPIOB->BSRR = EN << 16; /* clear E */
}
/* This function is used at the beginning of the initialization *
when the busy bit of the status register is not readable. */
void LCD_command_noPoll(unsigned char command) {
GPIOB->BSRR = (RS | RW) << 16; /* RS = 0, R/W = 0 */ GPIOC->ODR =
command; /* put command on data bus */ GPIOB->BSRR = EN; /* pulse E
high */ delayMs(0);
GPIOB->BSRR = EN << 16; /* clear E */
}
void LCD_data(char data) {
LCD_ready(); /* wait for LCD controller ready */ GPIOB->BSRR = RS;
/* RS = 1 */
GPIOB->BSRR = RW << 16; /* R/W = 0 */
GPIOC->ODR = data; /* put data on data bus */ GPIOB->BSRR = EN; /*
pulse E high */ delayMs(0);
GPIOB->BSRR = EN << 16; /* clear E */
}/* delay n milliseconds (16 MHz CPU clock) */ void delayMs(int n) {
int i;
for (; n > 0; n--)
for (i = 0; i < 3195; i++) ;
