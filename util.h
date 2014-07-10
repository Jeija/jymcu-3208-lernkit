#include <avr/io.h>
#include <stdbool.h>

#ifndef _UTIL_H
#define _UTIL_H

// Modify single bits in registers / bytes
#define sbi(ADDR, BIT) ((ADDR |=  (1<<BIT)))
#define cbi(ADDR, BIT) ((ADDR &= ~(1<<BIT)))
#define gbi(ADDR, BIT) ((ADDR &   (1<<BIT)))
#define tbi(ADDR, BIT) ((ADDR ^=  (1<<BIT)))

// Sleep 1 cycle
#define nop() asm volatile ("nop")

#define BUTTON_DDR	DDRD
#define BUTTON_PORT	PORTD
#define BUTTON_PIN	PIND

enum BUTTON
{
	BUTTON1 = PD7,
	BUTTON2 = PD6,
	BUTTON3 = PD5
};

void button_init(void);
bool button_get(enum BUTTON b);

#endif
