#include <avr/io.h>
#include <avr/interrupt.h>
const unsigned char cifre[] = {	
	0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14  
}; //decimalne cifre 0..9
unsigned char DISP_BAFER[4] = {
  0xff, 0xff, 0xff,cifre[0]
}; //bafer displeja
volatile unsigned long ms = 0;
volatile unsigned char disp = 3;
ISR(TIMER0_COMPA_vect)
{
 //prekid tajmera 0 usled dostizanja vrednosti registra OCR0A
 if (++disp > 3)
 disp = 0;
 PORTB = ~(1 << (3-disp)); //ukljucenje tranzistora
 PORTD = DISP_BAFER[disp]; //ispis na trenutno aktivan displej
 ms++; //sistemsko vreme
}
int main()
{
 unsigned long t0;
  char i;
  int mi=0;
 unsigned int counter=0;
 unsigned char pom;
 unsigned int pomi;

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
 t0 = ms;
 while ((ms - t0) < 1000); //pauza 1s
	pomi=counter;
   for (i = 3; i >= 0; i--){
 	pom=pomi%10;
     DISP_BAFER[i] = cifre[pom];
     pomi/=10;
     if(pom!=0){
        	mi=i;
        }
   }
   for(i=0;i<mi;i++)
   DISP_BAFER[i]=0xff;
      mi=0;
      counter++;
 }
 return 0;
}