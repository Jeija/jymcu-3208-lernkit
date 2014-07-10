#include <util/delay.h>
#include "util.h"
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
	button_init();

	// "CAG"-Schriftzug als Bitmap
	MTX_bitmap(bitmap, 7, 0, 19, 8);
	MTX_update();
	_delay_ms(3000);

	// "Hello" fährt von links rein
	int8_t i;
	for (i = -31; i<=1; i++)
	{
		MTX_clear();
		MTX_putstring("Hello", i, 0);
		MTX_update();
		_delay_ms(30);
	}
	_delay_ms(1000);

	// "World" fährt von rechts rein
	for (i = 31; i>=1; i--)
	{
		MTX_clear();
		MTX_putstring("World", i, 0);
		MTX_update();
		_delay_ms(30);
	}
	_delay_ms(1000);

	// Button: Eingabe-Test
	for (i = 0; i<100; i++)
	{
		MTX_clear();
		if (button_get(BUTTON1))
		{
			MTX_line(0, 6, 31, 6, true);
			MTX_line(0, 7, 31, 7, true);
		}

		if (button_get(BUTTON2))
		{
			MTX_line(0, 3, 31, 3, true);
			MTX_line(0, 4, 31, 4, true);
		}

		if (button_get(BUTTON3))
		{
			MTX_line(0, 0, 31, 0, true);
			MTX_line(0, 1, 31, 1, true);
		}
		MTX_update();
		_delay_ms(50);
	}

	// Endloser roter Streifen
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

