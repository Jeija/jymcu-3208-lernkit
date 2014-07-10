/* Abstraction layer to make usage of the ht1632c easier */

#include <stdlib.h>
#include "ht1632c.h"
#include "util.h"
#include "font5x8.h"

// Framebuffer: Contains all data displayed on the matrix screen
uint8_t fb[32];

void MTX_clear(void)
{
	uint8_t i;
	for (i = 0; i < 32; ++i)
		fb[i] = 0x00;
}

void MTX_update(void)
{
	ht1632c_flip(fb);
}

void MTX_dot(int8_t x, int8_t y, bool positive)
{
	if (x < 0 || y < 0 || x > 31 || y > 7) return;
	if (positive)	sbi(fb[x], y);
	else		cbi(fb[x], y);
}

/* http://de.wikipedia.org/wiki/Bresenham-Algorithmus */
void MTX_line(int8_t x0, int8_t y0, int8_t x1, int8_t y1, bool positive)
{
	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;)
	{
		MTX_dot(x0,y0,positive);
		if (x0==x1 && y0==y1) break;
		e2 = 2*err;
		if (e2 > dy)
		{
			err += dy;    /* e_xy+e_x > 0 */
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;    /* e_xy+e_y < 0 */
			y0 += sy;
		}
	}
}

void MTX_init(void)
{
	ht1632c_init();
	MTX_clear();
	MTX_update();
}

void MTX_bitmap(uint8_t *bitmap, uint8_t destx, uint8_t desty, uint8_t bitmapx, uint8_t bitmapy)
{
	uint8_t x, y;
	for (x = 0; x < bitmapx; x++)
		for (y = 0; y < bitmapy; y++)
			MTX_dot(destx+x,desty+y,gbi(bitmap[x], (bitmapy-y-1)));
}

void MTX_putchar(char c, int8_t x, int8_t y)
{
	uint8_t bitmap[5];
	uint8_t i;
	for (i = 0; i<5; i++)
		bitmap[i] = pgm_read_byte(&(font5x8[(uint8_t)c][i]));
	MTX_bitmap(bitmap, x, y-1, 5, 8);
}

void MTX_putstring(char *string, int8_t x, int8_t y)
{
	uint8_t i = 0;
	for (i = 0; string[i] != 0x00; i++)
		MTX_putchar(string[i], x+6*i, y);
}
