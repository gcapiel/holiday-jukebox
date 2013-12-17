#include <Time.h>
#include <TinkerKit.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <matrix_lcd_commands.h>
#include <TKLCD.h>

//char outputChar = 'A';
unsigned long lastPress = 0;
const unsigned long timeOutDisplay = 25000;
const unsigned long timeOutButton = 2500;
int msgOneState = 1;
char* songs[] = {"song1","song2","song3","song4","song5"};
int currentSong;

TKLCD_Local lcd = TKLCD_Local();
TKButton button(A0); 

void setup() {
  //setTime(15,0,0,21,9,2013);
  lcd.begin();
  Serial1.begin(9600);
  Serial1.println("Jukebox ready"); 
}

void loop() {
  
  unsigned long millisLastPress = millis() - lastPress;

  if (lastPress > 0 && (millisLastPress < timeOutDisplay)) {
      
    if (msgOneState == 1) {
      msgOneState++;
      lcd.clear();
      lcd.display();
      lcd.setBrightness(255);
      lcd.setCursor(0,0);
      lcd.print(songs[currentSong]);
      lcd.setCursor(0,1);
      lcd.print("");
    }
  } else {
    lcd.noDisplay();
    lcd.setBrightness(0);
  }
  if (button.pressed() == HIGH) {
    if ((millisLastPress) > timeOutButton || lastPress == 0) {
      lastPress = millis();
      currentSong = random(0,5);
      Serial1.println(songs[currentSong]);
      msgOneState = 1;
    }
  }
}




