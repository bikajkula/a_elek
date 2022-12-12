#include <LiquidCrystal.h>
// zadavanje pinova koji se koriste za komunikaciju s displejom
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);          //uvek isto

void setup() {
 // zadavanje broja vrsta i kolona
 // nakon inicijalizacije kursor je na poziciji (0,0)
 lcd.begin(16, 2);
 
 // ispis poruke
 lcd.print("Srecna nova");
 
 // postavljanje kursora (X = 0..15, Y = 0..1)
 lcd.setCursor(0, 1);
 lcd.print("Godina :)");
}

void loop() {
 //ispis smajlija koji namiguje
 lcd.setCursor(7, 1);
 lcd.print(';');
 delay(1000);           //1 sek
 
 lcd.setCursor(7, 1);
 lcd.print(':');
 delay(1000);
}
