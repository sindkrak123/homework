#include <LiquidCrystal.h>
#include <SPI.h>
#include "Tetris.h"
#define SS_PIN 10


int speakerPin = 8;
int length = 15;
int ledPin = 9;

char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; 
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin,OUTPUT);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("   Score: 0");
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Loading ...");
  Dp_Init();
  Te_Init();
  Serial.println(random(9, 15) * (10 + pow(3,1) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,2) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,3) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,4) * 10));
}



byte xC = 0;
byte yC = 0;
long frameCount = 0;

void loop() {
  // put your main code here, to run repeatedly:
  for(int a = 0 ; a < 1000 ; a++){
    frameCount++;
    Te_Draw();
    Te_Update(frameCount);
    delay(1);
  }
  digitalWrite(ledPin, HIGH);
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2); 
  } 
  digitalWrite(ledPin,LOW);
}
