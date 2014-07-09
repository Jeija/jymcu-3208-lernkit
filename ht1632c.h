#include <avr/io.h>
#include <stdbool.h>

#ifndef _HT1632C_H
#define _HT1632C_H

void ht1632c_setpower(bool on);
void ht1632c_setblink(bool on);
void ht1632c_setbrightness(uint8_t value);
void ht1632c_flip(uint8_t *buffer);
void ht1632c_init(void);

#endif
