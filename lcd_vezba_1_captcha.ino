#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte choose;
char capcha[8];
byte counter=0;
int pom;
char unos[8];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.begin(9600);
  randomSeed(analogRead(1));
  for(int j=0;j<8;j++){
    choose=random(0,3);
    Serial.print(choose);
    Serial.print("\t");
    if(choose==0){
        capcha[counter]='0'+random(10);
      }
  
     if(choose==1){
        capcha[counter]=random('a','z'+1);
      }
  
     if(choose==2){
        capcha[counter]=random('A','Z'+1);
      }
    Serial.println(capcha[counter]);
    counter++;
  }
  capcha[counter]='\0';
  counter=0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print(capcha);
  while(Serial.available()==0)
  ;
  delay(50);
  int duzina=Serial.available();
  Serial.readBytes(unos,duzina);
  lcd.setCursor(0,1);
  int yn=0;
  for(int c=0;c<duzina;c++){
      if(unos[c]==capcha[c]){
          yn++;
        }
    }
  if (yn==duzina){
      lcd.print("Covjek!");
    }
  else{
      lcd.print("ISS sotono!");
    }
  lcd.setCursor(0,0);
}
