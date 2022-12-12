#include <LiquidCrystal.h>
#define NONE 0
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

String karakteri = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int pos = 0;
int slova[16];
bool dozvola = true;
int btn;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.cursor();
  Serial.begin(9600);

}

void loop() {
  btn = readButton();
  lcd.setCursor(pos, 0);
  lcd.print(karakteri.charAt(slova[pos]));

  if(btn == NONE){
    dozvola = true;
  }
  else if(dozvola == true){
    switch(btn){
      case UP:
        ++slova[pos];
        break;
      case DOWN:
        --slova[pos];
        break;
      case LEFT:
        --pos;
        break;
      case RIGHT:
        ++pos;
        break;
      default:
        break;
    }

    dozvola = false;

   //lcd.print(karakteri.charAt(slova[pos]));
  }
  if(btn==SELECT)
  {
    lcd.noCursor();
    while(1)
    {
      lcd.scrollDisplayLeft();
      delay(150);
    }
  }
  delay(100);
}


byte readButton()
{
 int tmp = analogRead(0); //read value of Analog input 0
 //depending on voltage, we can find out which switch was pressed
 if (tmp > 635 && tmp < 645) //SELECT
     return SELECT;
 if (tmp > 405 && tmp < 415) //LEFT
     return LEFT;
 if (tmp > 95 && tmp < 105) //UP
     return UP;
 if (tmp > 252 && tmp < 262) //DOWN
     return DOWN;
 if (tmp < 5) //RIGHT
     return RIGHT;
 return NONE; //NONE
}