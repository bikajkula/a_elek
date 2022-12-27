#include <avr/io.h>
#include <avr/interrupt.h>
const unsigned char cifre[] = {	
	0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14  
}; //decimalne cifre 0..9
unsigned char DISP_BAFER[4]={0xff,0xff,0xff,cifre[0]};
const unsigned char minus=0xfe;//znak minus
unsigned char ukljuceno = 1;
volatile unsigned long ms = 0;
volatile unsigned char disp = 3;
volatile int number=0;
ISR(TIMER0_COMPA_vect)
{
 //prekid tajmera 0 usled dostizanja vrednosti registra OCR0A
  if (++disp > 3)
 		disp = 0;
  PORTB = ~(1 << (3-disp)); //ukljucenje tranzistora
  PORTD = DISP_BAFER[disp]; //ispis na trenutno aktivan displej
  ms++; //sistemsko vreme
}
ISR(PCINT1_vect)
{
 //prekid usled promene stanja pina PCINT10 ili pina PCINT8
 switch ((~PINC) & 0x0a)//maska 1010
 {
 case 0x02: //pritisnut taster dole
   	ukljuceno = 1;
   	number--;
 break;
 case 0x08: //pritisnut taster gore
 	ukljuceno = 0;
   	number++;
 break;
 }
}
int main()
{
  int pom1,pom2,mi=0,zero=0;
  char i;
  unsigned long t0;
 //inicijalizacija portova:
 DDRB = 0x0f; //PB3-PB0 -> izlazi
 DDRC = 0x00; //port C -> ulaz
 DDRD = 0xff; //port D -> izlaz
 //PORTB = ~0x01; //ukljucenje displeja D4

 PCICR = (1 << PCIE1); //dozvola prekida usled promene stanja
 PCMSK1 = 0x0a; //pina PCINT10, ili pina PCINT8 ovde se podesavaju tasteri

 //inicijalizacija tajmera 0:
 TCCR0A = 0x02; //tajmer 0: CTC mod
 TCCR0B = 0x03; //tajmer 0: fclk = fosc/64
 OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
 TIMSK0 = 0x02; //dozvola prekida tajmera 0
 //usled dostizanja vrednosti registra OCR0A

 sei(); //I = 1 (dozvola prekida)

  while(1){ 
  	t0 = ms;
 	while ((ms - t0) < 100); //pauza 500ms
    pom1=number;
    if(pom1<0){
      pom1*=(-1);
      for (i = 3; i >0 ; i--){
        pom2=pom1%10;
        DISP_BAFER[i]=cifre[pom2];
        pom1/=10;
        if(pom2!=0){
        	mi=i;
          	zero=i-1;
        }
      }
      DISP_BAFER[mi-1]=minus;
      mi=0;
      for(i=0;i<zero;i++){
        	DISP_BAFER[i]=0xff;
        }
    }else if(pom1!=0){
      for (i = 3; i >=0 ; i--){
        pom2=pom1%10;
        DISP_BAFER[i]=cifre[pom2];
        pom1/=10;
        if(pom2!=0){
          	zero=i;
        }
        
      }
      for(i=0;i<zero;i++){
        	DISP_BAFER[i]=0xff;
        }
    }else{
    	DISP_BAFER[3]=cifre[0];
      	DISP_BAFER[2]=0xff;
      	DISP_BAFER[1]=0xff;
      	DISP_BAFER[0]=0xff;
    }
    	
  }
    //i ceka prekide
 return 0;
}
