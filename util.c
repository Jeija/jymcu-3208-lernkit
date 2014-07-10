#include "util.h"

void button_init(void)
{
	cbi(BUTTON_DDR, BUTTON1);
	cbi(BUTTON_DDR, BUTTON2);
	cbi(BUTTON_DDR, BUTTON3);

	sbi(BUTTON_PORT, BUTTON1);
	sbi(BUTTON_PORT, BUTTON2);
	sbi(BUTTON_PORT, BUTTON3);
}

bool button_get(enum BUTTON b)
{
	return !gbi(BUTTON_PIN, b);
}
