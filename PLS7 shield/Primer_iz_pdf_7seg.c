#include <avr/io.h>
#include <util/delay.h>
const unsigned char simboli[] = {
 0x0c, 0xa4, 0x27, 0xc4
}; //look-up tabela sa simbolima za ispis na displej (A,b,C,d)
int main(void)
{
 unsigned char displej;
 DDRD = 0xff; //port D -> izlaz
 DDRB = 0x0f; //PB3 - PB0 -> izlazi
 while(1)
 {
 for (displej = 1; displej <= 4; displej++)
 {
 PORTB = ~(0x01 << (4-displej)); //ukljucuje se tranzistor
 //na odgovarajucoj poziciji
 PORTD = simboli[displej-1]; //ispis simbola iz tabele
 _delay_ms(2); //pauza 2ms
 }
 }
 return 0;
}
