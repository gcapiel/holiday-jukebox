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
char* songFiles[] = {"O_Tannenbaum","Santa_Baby","White_Christmas","O_Tannenbaum","O_Tannenbaum"};
char* songTitles[] = {"O Tannenbaum","Santa Baby","White Christmas","O Tannenbaum","O Tannenbaum"};
int currentSong;

TKLCD_Local lcd = TKLCD_Local();
TKButton button(A0); 

void setup() {
  //setTime(15,0,0,21,9,2013);
  lcd.begin();
  Serial1.begin(9600);
  Serial1.println("msg:Jukebox ready"); 
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
      lcd.print(songTitles[currentSong]);
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
      Serial1.println(songFiles[currentSong]);
      msgOneState = 1;
    }
  }
}




