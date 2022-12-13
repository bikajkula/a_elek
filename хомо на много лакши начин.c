#include <LiquidCrystal.h>
#include <string.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

String captcha, unos;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  randomSeed(analogRead(A3));
}

void loop() {
  lcd.setCursor(0,0);
  captcha = gen_captcha(random(5, 9)); //inclusive/exclusive
  lcd.print(captcha);

  while(Serial.available()<=0);
  delay(100);
  unos = Serial.readString();

  lcd.setCursor(0, 1);
  if(captcha == unos){
    lcd.print("ECCE HOMO!");
  }
  else{
    lcd.print("BOT!");
  }

  while(readButton() != SELECT);
  lcd.clear();
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
 return 0; //NONE
}

String gen_captcha(int len) {
    String alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    String tmp_s;

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum.charAt(random(0, alphanum.length()));
    }

    return tmp_s;
}
