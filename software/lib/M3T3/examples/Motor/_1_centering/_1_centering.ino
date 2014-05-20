// The Music object is automatically instantiated when the header file is
// included. Make calls to the Music objects with "Music.function(args)".
// You still need to call Music.init() in the setup() function below.
#define MIDI
#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Serial.begin(115200);
  MotorA.init();
  MotorB.init();
  Music.init();
  Music.enableEnvelope1();
  Music.enableEnvelope2();
//  Midi.init();
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  
  analogReadAveraging(32);
}

void loop() {

  usbMIDI.read();
  int valueA = analogRead(A1);
  int valueB = analogRead(A9);
  int torqueA = (512-valueA)*4;
  int torqueB = (512-valueB)*4;
//  Serial.print("valueA = ");
//  Serial.print(valueA);
//  Serial.print(" --- valueB = ");
//  Serial.println(valueB);
//  delay(50);
  MotorA.torque(torqueA);
  MotorB.torque(torqueB);
  
}
