#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
 DDRD = 0xff; //port D -> izlaz
 DDRB |= 1 << 4; //PB4 -> izlaz
 PORTB &= ~(1 << 4); //PB4 = 0, cime se ukljucuje tranzistor Q0
 while(1)
 {
 PORTD = 0xaa; //ukljucuju se LED na pozicijama 6, 4, 2 i 0
 _delay_ms(1000);//pauza 1s
 PORTD = 0x55; //ukljucuju se LED na pozicijama 7, 5, 3 i 1
 _delay_ms(1000);//pauza 1s
 }
 return 0;
}