/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  

int joystick_x = A0;    
int joystick_y = A1;
int joystick_z = 2;    

#define melodyPin 3
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};


int Titanic_note[] =  {
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, 
NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, 
NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E4, NOTE_B4, NOTE_E5, 
NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, 
NOTE_F5, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_E4, 
NOTE_D4, NOTE_B3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_B3, NOTE_E4,
NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4
};
int Titanic_duration[] = {
8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,4,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,
8,8,8,8,8,1,
8,8,8,8,4,4,4,8,4,4,8,8,8,8,4,8,8,4,8,4,8,8,4,8,4,1
};

int Pirates_note[] = {
NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,
NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,
NOTE_C5,NOTE_C5,NOTE_C5,

NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,

NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,
NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,
NOTE_E5,NOTE_D5,NOTE_C5
};
int Pirates_duration[] = {
4,8,8,4,4,
4,8,8,4,4,
8,8,4,8,8,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
4,4,2,
4,4,4,4,
8,8,8,8,2,
4,4,4,4,
4,4,2
};


int correct_song=1,searching=1,songg=1;
int x,y,z;
void setup(void)
{
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(joystick_z, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  lcd.display(); 
  x = 500;      // 조이스틱 X축의 아날로그 신호를 x에 저장
  y = 500;      // 조이스틱 Y축의 아날로그 신호를 y에 저
  z = 1;
}
void loop()
{
  while(z==1){
  x = analogRead(joystick_x);      // 조이스틱 X축의 아날로그 신호를 x에 저장
  y = analogRead(joystick_y);      // 조이스틱 Y축의 아날로그 신호를 y에 저
  z = digitalRead(joystick_z);     // 조이스틱 Z축의 디지털 신호를 z에 저장
  Serial.print("X: ");                   
  Serial.print(x);                          //시리얼 모니터에 'X: x값'을 표기
  Serial.print("  Y: ");
  Serial.print(y);                          //시리얼 모니터에 '  Y: y값'을 표기
  Serial.print("  Z: ");
  Serial.println(z);  
  if ((x>600 && y>400) or (x>400 && y>600))searching+=1;
  else if((x<300 && y<600) or (x<600 && y<300))searching-=1;
//  else searching+=1;
  
  if (searching>3)searching=1;
  else if (searching<1)searching=2;
  
  lcd.clear();
  lcd.setCursor(0,1);
  if (searching==1){lcd.print("Mario");Serial.println("Mario");}
  else if (searching==2){lcd.print("Titanic");Serial.println("Titanic");}
  else if (searching==3){lcd.print("three bears");Serial.println("three bears");}
  lcd.setCursor(0,0);
  if (songg==1)lcd.print("Mario");
  else if (songg==2)lcd.print("Titanic");
  else lcd.print("three bears"); 
  delay(500);
  }
  correct_song=searching;
  songg=correct_song;
  sing(correct_song);
  z=1;
}
int song = 0;
void sing(int s) {
  song = s;
  lcd.setCursor(0,0); 
  if(s==1)mario();
  else if(s==2)Play_Titanic();
  else if(s==3)Play_Pirates();
}

void mario(){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Mario Theme"); 
    Serial.println(" 'Mario Theme'");
    for (int thisNote = 0; thisNote < 78; thisNote++) {

      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
    
    Serial.println(" 'Mario Theme'");
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print(" 'Mario Theme'"); 
    for (int thisNote = 0; thisNote < 78; thisNote++) {

      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(melodyPin, 0, noteDuration);

    }
    lcd.clear();
    Serial.println(" 'Underworld Theme'");
    lcd.setCursor(0,0); 
    lcd.print("Underworld Theme"); 
    for (int thisNote = 0; thisNote < 56; thisNote++) {

      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
  }
}

void Play_Titanic()
{
  lcd.clear();
  lcd.print("Titanic");
  for (int thisNote = 0; thisNote < (sizeof(Titanic_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Titanic_duration[thisNote];//convert duration to time delay
    buzz(melodyPin, Pirates_duration[thisNote], noteDuration);
 
    int pauseBetweenNotes = noteDuration * 2.70;
    delay(pauseBetweenNotes);
    buzz(melodyPin,0,noteDuration); //stop music on buzzer pin
    }
}

void Play_Pirates()
{ 
  lcd.clear();
  lcd.print("three bears"); 
  for (int i = 0; i < 49; i++) {
    int Durations = 1000/Pirates_duration[i];    // 음계의 음길이 계산
    buzz(melodyPin, Pirates_note[i], Durations);    
    int pauseBetweenNotes = Durations *1.3 ;
    delay(pauseBetweenNotes);
    buzz(melodyPin,0,Durations);
    }
}

//void Nyan_cat(){
//  //iterate over the notes of the melody:
//  for (int thisNote = 0; thisNote < sizeof(Nyan_cat_melody) / sizeof(Nyan_cat_melody[0]); thisNote++) {
//
//    int noteDuration = 1000/Nyan_cat_noteDurations[thisNote];
//    tone(melodyPin, Nyan_cat_melody[thisNote],noteDuration);
//    
//    int pauseBetweenNotes = noteDuration * 1.30;
//    delay(pauseBetweenNotes);
//    
//    noTone(melodyPin); //stop the tone playing:
//  }
//  digitalWrite(melodyPin,LOW);
//}

void buzz(int targetPin, long frequency, long length) {
  analogWrite(9, frequency/20);
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }  
  digitalWrite(9,LOW);
}
