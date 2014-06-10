#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
//  Music.enableEnvelope1();
//  Music.enableEnvelope2();

  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);

}

void loop() {
  
  usbMIDI.read();
  updateSequence();
  
}

boolean noteIsOn = false;
int n = 0;
int dir = 1;
int rootNote = 36;
int note[] = {0,0,0,0,0,0,0,0,0};
//int note[] = {0,12,3,19,15,9,5,24,7};

long time = 0;
long lastTime = 0;
long timeDelay = 60;

void updateSequence() {
  // This short routine loops note over and over again
  time = millis();
  if(time - lastTime > timeDelay) {
    if(!noteIsOn) {
      Music.noteOn(rootNote+note[n]);
      noteIsOn = true;
      n = n + dir;
      if(n > 7)
      {
        dir = -1;
      }
      else if(n < 1)
      {
        dir = 1;
      }
    } else {
      Music.noteOff();
      noteIsOn = false;
    }
    lastTime = time;
  }
}
