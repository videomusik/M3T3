#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Serial.begin(9600);
  MotorA.init();
  MotorB.init();
  Music.init();
  Music.set12bit(true);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  
  analogReadAveraging(32);
}

void loop() {

  usbMIDI.read();
  int valueA = analogRead(A1);
  int valueB = analogRead(A9);
  int centerValue = valueA;
  int torqueA = (512-valueA);
  int torqueB = (512-valueB);
//  Serial.print("valueA = ");
//  Serial.print(valueA);
//  Serial.print(" --- valueB = ");
//  Serial.println(valueB);
//  delay(50);
  MotorA.torque(torqueA*4);
  MotorB.torque(torqueB*4);
  Music.setFrequency(valueA);
  Music.setDetune(float(torqueB)/1024.0);
  
}


///////////////////////////////////////////////////////////////////////
// THE BELOW FUNCTIONS ARE NEEDED FOR THE MUSIC PART TO RESPOND TO MIDI
///////////////////////////////////////////////////////////////////////

void OnNoteOn(byte channel, byte note, byte velocity) {
  Midi.noteOn(channel, note, velocity);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  Midi.noteOff(channel, note, velocity);
}

void OnControlChange(byte channel, byte control, byte value) {
  Midi.controller(channel, control, value);  
}
