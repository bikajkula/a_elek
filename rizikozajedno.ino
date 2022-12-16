#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5
#define NONE 0
int brKockica1,brKockica2;
String karakteri="123";
bool dozvola=true;
int btn;

int kockica;
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
}

void loop() {
  btn=NONE;
  int unos=0;
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("Napad");
  lcd.setCursor(9,0);
  lcd.print(">");


  lcd.setCursor(0,1);
  lcd.print("Odbrana");
  lcd.setCursor(9,1);
  lcd.print(">");
  //broj kockica
  lcd.setCursor(8,0);
  lcd.print(karakteri[unos]);
  while(btn!=SELECT)
  {
    btn=readButton();
    if(btn==NONE)
    {
      dozvola=true;
    }
    else if(dozvola==true){
      if(btn==UP && unos<2) 
      {
          ++unos;
      }
      else if(btn==DOWN && unos>0)
      {
        --unos;
      }
      dozvola=false;
    }
    lcd.setCursor(8,0);
    lcd.print(karakteri[unos]);
    delay(200);
  }
  //baca kockicu
  
  int napad[unos+1];
  for(int i=0;i<unos+1;i++)
  {
    btn=NONE;
    kockica=1;
    lcd.setCursor(11+2*i,0);
    while(btn!=SELECT)
    {
      btn=readButton();
      lcd.setCursor(11+2*i,0);
      kockica=kockica%6+1;
      lcd.print(kockica);
      delay(200);
    }
    napad[i]=kockica;
    delay(200);
  }
//drugi unosi kockci
btn=NONE;
for(int i=unos; i>=0; i--){
    for(int j=unos; j>=1; j--){
      if(napad[j] > napad[j-1]){
        int tmp = napad[j];
        napad[j] = napad[j-1];
        napad[j-1] = tmp;
      }
    }
  }
delay(100);
unos=0;
lcd.setCursor(8,1);
  lcd.print(karakteri[unos]);
  while(btn!=SELECT)
  {
    btn=readButton();
    if(btn==NONE)
    {
      dozvola=true;
    }
    else if(dozvola==true){
      if(btn==UP && unos<2) 
      {
          ++unos;
      }
      else if(btn==DOWN && unos>0)
      {
        --unos;
      }

      dozvola=false;
    }
    lcd.setCursor(8,1);
    lcd.print(karakteri[unos]);
    delay(200);
  }
//drugi baca kockciu
  
  //baca kockicu
  
  int odbrana[unos+1];
  for(int i=0;i<unos+1;i++)
  {
    btn=NONE;
    kockica=1;
    lcd.setCursor(11+2*i,1);
    while(btn!=SELECT)
    {
      btn=readButton();
      lcd.setCursor(11+2*i,1);
      kockica=kockica%6+1;
      lcd.print(kockica);
      delay(100);
    }
    odbrana[i]=kockica;
    delay(100);
  }
  btn=NONE;
  for(int i=unos; i>=0; i--){
    for(int j=unos; j>=1; j--){
      if(odbrana[j] > odbrana[j-1]){
        int tmp = odbrana[j];
        odbrana[j] = odbrana[j-1];
        odbrana[j-1] = tmp;
      }
    }
  }
  delay(1000);
  //**SELECT**
  while(btn!=SELECT)
  {
      btn=readButton();
  }
  btn=NONE;
  delay(300);
  lcd.clear();
  //rez bacanja napad
  int lenNapad=sizeof(napad)/sizeof(int);
  int lenOdbrana=sizeof(odbrana)/sizeof(int);

  for(int i=0;i<lenNapad;i++)
  {
    lcd.setCursor(2*i,0);
    lcd.print(napad[i]);
  }
  lcd.setCursor(6,0);
  lcd.print("->");

  //rez bacanja odbrana

  for(int i=0;i<lenOdbrana;i++)
  {
    lcd.setCursor(2*i,1);
    lcd.print(odbrana[i]);
  }
  lcd.setCursor(6,1);
  lcd.print("->");

  //racunanje rez
  int gubiNapad=0,gubiOdbrana=0;
  int manjilen=lenOdbrana;
  if(lenNapad<lenOdbrana)
  {
    manjilen=lenNapad;
  }
  for(int i=0;i<manjilen;i++)
  {
    if(napad[i]<=odbrana[i])
    {
      ++gubiNapad;
    }
    else
      ++gubiOdbrana;
  }
  lcd.setCursor(9,0);
  lcd.print("Gubi ");
  lcd.print(gubiNapad);
  lcd.setCursor(9,1);
  lcd.print("Gubi ");
  lcd.print(gubiOdbrana);



  while(btn!=SELECT)
  {
      btn=readButton();
      
  }
  lcd.clear();

}
//racunanje rezultata

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