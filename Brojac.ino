#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char brojac_str[4];
int brojac = 0;
int sd = 0;               //softversko diferenciranje

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int taster = ocitajTaster();

  if(taster != 0 && sd == 0){     //ako je taster pritisnut i sd je 0
    sd = 1;
    delay(50);                    //zbog problema sa kineskim tasterima
    
    if(taster == 3){
      brojac++;
    }//UP
    else if(taster == 4){
      brojac--;
    }//DOWN
    else if(taster == 1){
      brojac = 0;
    }//SELECT = RESET    
  }
  if(taster == 0){      //ako je taster pusten, sd je 0
    sd = 0;
  }

  lcd.setCursor(0,0);
  itoa(brojac, brojac_str, 10);
  lcd.print(brojac);
  delay(100);
  lcd.clear();
}

int ocitajTaster(){
  int a_vr = analogRead(0);
  
  if(a_vr < 50)
    return 5;//RIGHT
  else if(a_vr < 175)   
    return 3;//UP  
  else if(a_vr < 325)
    return 4;//DOWN
  else if(a_vr < 520)
    return 2;//LEFT
  else if(a_vr < 800)
    return 1;//SELECT
  else 
    return 0;//NONE
}
