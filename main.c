#include <util/delay.h>
#include "matrix.h"

uint8_t bitmap[] =
{
	0b11000011,
	0b10000001,
	0b00000000,
	0b01111110,
	0b01000010,
	0b01000010,
	0b00000000,
	0b01111110,
	0b00010010,
	0b00010010,
	0b01111110,
	0b00000000,
	0b01111110,
	0b01000010,
	0b01010010,
	0b01110010,
	0b00000000,
	0b10000001,
	0b11000011
};

int main(void)
{
	MTX_init();

	MTX_bitmap(bitmap, 7, 0, 19, 8);
	MTX_update();
	_delay_ms(5000);

	MTX_clear();
	MTX_putstring("Hello", 0, 0);
	MTX_update();
	_delay_ms(5000);

	uint8_t i;
	bool positive = true;
	while(1)
	{
		for (i = 0; i <= 31; i++)
		{
			MTX_line(i, 0, i, 7, positive);
			_delay_ms(10);
			MTX_update();
		}
		positive = !positive;
	}

	while(1);
	return 0;
}

