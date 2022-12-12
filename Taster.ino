#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char taster_str[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int taster = ocitajTaster();
  //Serial.print(taster);
  lcd.setCursor(0,0);
  itoa(taster, taster_str, 10);
  lcd.print(taster_str);                  //taster + 48
  delay(500);
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
