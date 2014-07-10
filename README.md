JY-MCU 3208 LED Matrix
======================

Dieses Kit bietet die möglichkeit, die LED Matrix mit wenigen Befehlen einfach anzusteuern.
Diese Befehle sind:

## LED Matrix ##
* `MTX_init()`
	Die LED Matrix initialisieren. Muss zu Anfang aufgerufen werden!
* `MTX_update()`
	Die Änderungen auf die LED Matrix anwenden. Muss aufgerufen werden, wenn eine Änderung zu sehen sein soll.
* `MTX_clear()`
	Die LED Matrix leeren.


* `MTX_dot(x, y, positive)`
	Die LED bei den Koordinaten (x, y) einschalten (wenn positive == true) bzw. ausschalten (wenn positive == false).
* `MTX_line(startx, starty, destx, desty, positive)`
	Eine Linie zwischen den angegebenen Punkten auf der Matrix anzeigen (aus eingeschalteten LEDs wenn positive == true, ansonsten eine dunkle Linie).
* `MTX_bitmap(bitmap, destx, desty, bitmapx, bitmapy)`
	Ein bitmap (= Bild) auf der Matrix anzeigen. Siehe auch main.c für ein Beispiel.
* `MTX_putchar(c, x, y)`
	Den Buchstaben in der Variable c an der Stelle (x, y) anzeigen. Fontgröße: 5x8 Pixel.
* `MTX_putstring(string, x, y)`
	Einen string an der Stelle (x, y) anzeigen.


## HT1632C Controller IC ##
Weiterhin können noch verwendet werden:
* `ht1632c_setblink(bool on)`
	Alle 0,5 Sekunden alle LEDs blinken (on = true aktivieren; on = false deaktivieren)
* `ht1632c_setbrightness(uint8_t value)`
	Helligkeit des Displays setzen (maximal 15)

## Buttons ##
* `button_init()`
	Eingabe über die Buttons aktivieren. Muss unbedingt vor `button_get()` aufgerufen werden.
* `button_get()`
	Status der Buttons abfragen. Die Buttons sind von oben nach unten mit BUTTON1, BUTTON2, BUTTON3 durchnummeriert. Beispiel: `if (button_get(BUTTON1)) {...}`.

#### Siehe main.c für Beispiele ####
Diese Bibliothek ist NICHT für den regulären Einsatz, sondern nur zum Erlernen der Programmierung einer LED Matrix geeignet.
Eine flexiblere Bibliothek findet sich z.B. [hier](https://github.com/vogelchr/avr-jy-mcu-3208).
