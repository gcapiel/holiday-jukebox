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
char* songFiles[] = {"O_Tannenbaum","Santa_Baby","White_Christmas","Baby_Its_Cold_Outside","Joy_to_the_World"};
char* songTitles[] = {"O Tannenbaum","Santa Baby","White Christmas","Baby, It's|Cold Outside","Joy to the World"};
int currentSong;

TKLCD_Local lcd = TKLCD_Local();
TKButton button(A0); 

void setup() {
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
      String currentSongTitle = songTitles[currentSong];
      if (currentSongTitle.indexOf('|') > 0) {
        lcd.setCursor(0,0);
        lcd.print(currentSongTitle.substring(0,currentSongTitle.indexOf('|')));
        lcd.setCursor(0,1);
        lcd.print(currentSongTitle.substring(currentSongTitle.indexOf('|')+1));
      }
      else {
        lcd.setCursor(0,0);
        lcd.print(songTitles[currentSong]);
      }
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




