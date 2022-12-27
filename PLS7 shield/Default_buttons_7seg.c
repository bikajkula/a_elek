// Simple test code that writes "----" on 7-seg displays
// By holding one of the buttons, a letter will appear on 7-seg
// Cathodes of 4x 7-seg and LEDS are connected to digital pins PORTD
// Anodes are shorted and connected to Vcc by PNP transistors
// Transistors are controlled with PORTB
// Set bit (PB4-PB0) of PORTB to zero to enable adequate display
// Set bits of PORTD to write something to display (7-seg, LED)
#include <avr/io.h>
#include <util/delay.h>

const unsigned char symbols[] = { 0x0c, 0xa4, 0x27, 0xc4 };
void writeTo7Seg (unsigned char letter, unsigned char position)
{
 	PORTB = ~(0x01 << (4-position)); //enable one of 7-seg
 	PORTD = letter; // writhe character to that display
 	_delay_ms(2); //pause 2ms
}

int main(void)
{
  unsigned char buttons;
  DDRD = 0xff; //port D -> output
  DDRC = 0x00; //port C -> input
  DDRB = 0x0f; //PB3 - PB0 output
  while (1)
  {
    buttons = PINC & 0x0f; //read buttons
    if (!(buttons & 0x01)) //check button "left"
    	writeTo7Seg (symbols[0], 1);
    else
    	writeTo7Seg (0xfe, 1);

    if (!(buttons & 0x02)) //check button "down"
    	writeTo7Seg (symbols[1], 2);
    else
    	writeTo7Seg (0xfe, 2);

    if (!(buttons & 0x04)) //check button "right"
    	writeTo7Seg (symbols[2], 3);
    else
    	writeTo7Seg (0xfe, 3);

    if (!(buttons & 0x08)) //check button "left"
    	writeTo7Seg (symbols[3], 4);
    else
    	writeTo7Seg (0xfe, 4);
  }
return 0;
}