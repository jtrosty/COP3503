//www.elegoo.com
//2016.12.08

#include "pitches.h"
 
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_DS8, NOTE_FS6};
int duration = 500;  // 500 miliseconds
int shortDuration = 50;  // 500 miliseconds
// NOTE_DS8

int chirp[] = {NOTE_CS8, NOTE_B7};

 
void setup() {
 
}
 
void loop() {  
  tone(8, chirp[1], shortDuration);
  delay(100);
  tone(8, chirp[0], shortDuration);

  /*
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(8, melody[thisNote], duration);
     
    // Output the voice after several minutes
    delay(1000);
  }
  */
   
  // restart after two seconds 
  delay(2000);
}
