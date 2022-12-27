#include <avr/io.h>
#include <avr/interrupt.h>
const unsigned char simboli[] = {
 0x0c, 0xa4, 0x27, 0xc4
}; //look-up tabela sa simbolima
unsigned char DISP_BAFER[4] = {
 0xfe, 0xfe, 0xfe, 0xfe
}; //bafer displeja
volatile unsigned long millis = 0;
volatile unsigned char disp = 3;
ISR(TIMER0_COMPA_vect)
{
 //prekid tajmera 0 usled dostizanja vrednosti registra OCR0A
 if (++disp > 3)
 disp = 0;
 PORTB = ~(1 << (3-disp)); //ukljucenje tranzistora
 PORTD = DISP_BAFER[disp]; //ispis na trenutno aktivan displej
 millis++; //sistemsko vreme
}
int main()
{
 unsigned long t0;
 unsigned char i;

 //inicijalizacija portova:
 DDRB = 0x0f; //PB3-PB0 -> izlazi
 DDRD = 0xff; //port D -> izlaz

 //inicijalizacija tajmera 0:
 TCCR0A = 0x02; //tajmer 0: CTC mod
 TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
 OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
 TIMSK0 = 0x02; //dozvola prekida tajmera 0
 //usled dostizanja vrednosti registra OCR0A
 sei(); //I = 1 (dozvola prekida)

 while(1)
 {
 t0 = millis;
 while ((millis - t0) < 500); //pauza 500ms
 for (i = 0; i < 4; i++)
 DISP_BAFER[i] = simboli[i];
 t0 = millis;
 while ((millis - t0) < 500); //pauza 500ms
 for (i = 0; i < 4; i++)
 DISP_BAFER[i] = 0xfe;
 }
 return 0;
}