#include <LiquidCrystal.h>
LiquidCrystal lcd{8,9,4,5,6,7};
//char taster_str[4];
char brojac_str[4];
int brojac = 0;
int sd = 0;
int pos_x = 0;
int pos_y = 0;

byte cikica[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B01110,
  B10001,
};

byte srce[8] = {
  B00000 ,
  B01010 ,
  B11111 ,
  B11111 ,
  B01110 ,
  B00100 ,
  B00000 ,
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);

  lcd.createChar(0, cikica);
  lcd.createChar(1, srce);
}

void loop() {
  int taster = ocitajTaster();

  if(taster != 0 && sd == 0){
    sd = 1;
    delay(50);
    if(taster == 3) // Up
    {
      if(pos_y > 0)
        pos_y--;
    }
    else if(taster == 4)  // Down
    {
      if(pos_y < 1)
        pos_y++;
    }
    else if(taster == 2)  // Left
    {
      if(pos_x > 0)
        pos_x--;
    }
    else if(taster == 5)  // Right
    {
      if(pos_x < 15)
        pos_x++;
    }
    else if(taster == 1)
    {
      pos_x = 0;
      pos_y = 0;  
    }
  }
  if(taster == 0)
    sd = 0;
 
  lcd.setCursor(pos_x,pos_y);

  lcd.write(byte(0));
  lcd.write(byte(1));
  delay(100);
  lcd.clear(); 
}

int ocitajTaster()
{
  int a_vr = analogRead(0);
  if(a_vr < 50)
    return 5; // Right  
  else if(a_vr < 175)
    return 3; // Up
  else if(a_vr < 325)
    return 4; // Down
  else if(a_vr < 520)
    return 2; // Left
  else if(a_vr < 800)
    return 1; // Select
  else
    return 0; // None
}
