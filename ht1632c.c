#include "ht1632c.h"
#include "util.h"

#include <util/delay.h> // TODO

#define HT1632C_PORT	PORTB
#define HT1632C_DDR	DDRB
#define HT1632C_NCS	PB3
#define HT1632C_WR	PB4
#define HT1632C_DATA	PB5

// ############################
// ## Hardware communication ##
// ############################
#define ht1632c_begin()	(cbi(HT1632C_PORT, HT1632C_NCS))
#define ht1632c_end()	(sbi(HT1632C_PORT, HT1632C_NCS))

inline void ht1632c_putbit(bool bit)
{
	cbi(HT1632C_PORT, HT1632C_WR);

	if (bit) sbi(HT1632C_PORT, HT1632C_DATA);
	else cbi(HT1632C_PORT, HT1632C_DATA);

	nop();
	nop();
	sbi(HT1632C_PORT, HT1632C_WR);
}

void ht1632c_put(uint8_t data, int8_t len)
{
	int8_t i;
	for (i = len-1; i >= 0; i--)
		ht1632c_putbit(gbi(data, i));
}

void ht1632c_cmd(uint8_t cmd)
{
	ht1632c_begin();
	ht1632c_put(0b100, 3);
	ht1632c_put(cmd, 8);
	ht1632c_put(0, 1);
	ht1632c_end();
}


// ##############
// ## Commands ##
// ##############
void ht1632c_setpower(bool on)
{
	if (on) ht1632c_cmd(0x01);
	else	ht1632c_cmd(0x00);
}

void ht1632c_setblink(bool on)
{
	if (on) ht1632c_cmd(0x09);
	else	ht1632c_cmd(0x08);
}

void ht1632c_setbrightness(uint8_t value)
{
	if (value < 0x0f) ht1632c_cmd(0xa0 | value);
}

// ################
// ## Pixel data ##
// ################
void ht1632c_flip(uint8_t *buffer)
{
	// Start writing display values from the beginning on
	ht1632c_begin();
	ht1632c_put(0b101, 3);
	ht1632c_put(0, 7);

	int8_t seg, row, col;
	for (seg = 0; seg < 4; seg++)
		for (row = 7; row >= 0; row--)
			for (col = 0; col < 8; col++)
				ht1632c_putbit(gbi(buffer[seg*8+col], row));

	ht1632c_end();
}

// ###########################
// ## Initial configuration ##
// ###########################
void ht1632c_init(void)
{
	HT1632C_PORT |= _BV(HT1632C_NCS) | _BV(HT1632C_WR) | _BV(HT1632C_DATA);
	HT1632C_DDR  |= _BV(HT1632C_NCS) | _BV(HT1632C_WR) | _BV(HT1632C_DATA);

	// Basic configuration: Power on, master mode, internal clock
	ht1632c_setpower(true);
	ht1632c_cmd(0x14);
	ht1632c_cmd(0x18);
	ht1632c_cmd(0x20);
	ht1632c_setbrightness(5);

	// Turn on
	ht1632c_cmd(0x03);
}
