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

char* songFiles[] = {
"01_Ive_Got_My_Love_To_Keep_Me_Warm.mp3",
"02_Misletoe_And_Holly.mp3",
"03_Christmas_Time_All_Over_The_World.mp3",
"04_The_First_Noel.mp3",
"06_I_Believe.m4a",
"07_Silver_Bells.m4a",
"08_The_Christmas_Song.m4a",
"09_Hark_The_Herald_Angels_Sing.m4a",
"10_Rudolph_The_Red-Nosed_Reindeer.m4a",
"11_The_Christmas_Waltz.m4a",
"12_Let_It_Snow_Let_It_Snow_Let_It_Snow.m4a",
"13_Have_Yourself_A_Merry_Little_Christmas.m4a",
"14_Peace_On_Earth_Silent_Night.m4a",
"15_Jingle_Bells.m4a",
"18_Winter_Wonderland.mp3",
"20_A_Marshmallow_World.mp3",
"Baby_Its_Cold_Outside.mp3",
"Joy_to_the_World.mp3",
"O_Tannenbaum.mp3",
"Santa_Baby.mp3",
"White_Christmas.mp3"};

char* songTitles[] = {
"I've Got My Love|To Keep Me Warm", 
"Misletoe|And Holly",
"Christmas Time|All Over The World",
"The First Noel",
"I Believe",
"Silver Bells",
"The Christmas Song",
"Hark! The Herald|Angels Sing",
"Rudolph,|Red-Nosed Reindeer",
"The|Christmas Waltz",
"Let It Snow!",
"A Merry|Little Christmas",
"Peace On Earth|Silent Night",
"Jingle Bells",
"Winter Wonderland",
"A Marshmallow|World",
"Baby It's|Cold Outside",
"Joy to the World",
"O Tannenbaum",
"Santa Baby",
"White Christmas"
};

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
      currentSong = random(0,21);
      Serial1.println(songFiles[currentSong]);
      msgOneState = 1;
    }
  }
}
