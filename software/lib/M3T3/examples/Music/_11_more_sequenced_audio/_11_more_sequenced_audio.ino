#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

// sequence ID
int s1, s2;
// sequence step index
int indx1 = 0;
int indx2 = 0;
const int nbr_notes1 = 16;
const int nbr_steps2 = 8;
const int notes1[] = {12, 24, 7, 12, 36, 12, 24, 15, 0, 12, 48, 36, 19, 24, 3, 36};
const int midiCC[] =     {8,  8, 11, 21, 21, 11, 21, 31, 8};
const int midiValue[] =  {0, 80, 68, 68, 68, 72, 72, 72, 0};

void setup() {

// We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();

// Loading a preset from EEPROM
  Music.getPreset(21);
  
// These guys just have to be here...
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
  
// this is the sequencer code
  Sequencer.init(120);
  Sequencer.setInternalClock(true);  

  //Sequencer.newSequence(SUBDIV, CALLBACK);
  // create new sequence and ID (s1)
  s1 = Sequencer.newSequence(NOTE_16, &s1cb);
  s2 = Sequencer.newSequence(NOTE_32, &s2cb);
  Sequencer.setInternal(s1, true);
  Sequencer.setExternal(s1, false);
  Sequencer.setInternal(s2, true);
  Sequencer.setExternal(s2, false);

  // start sequence 1 and 2
  Sequencer.startSequence(s1);
  Sequencer.startSequence(s2);
  
}

void loop() {
  
// Checking for incoming MIDI to use dashboard
  usbMIDI.read();
  Sequencer.update();
}

// callback function for the step sequencer

void s1cb() {
  Music.noteOn(notes1[indx1++] + 24, 127);
  if(indx1 >= nbr_notes1) indx1 = 0;
}

void s2cb() {
  Midi.controller(MIDI_CHANNEL - 1, midiCC[indx2], midiValue[indx2]);
  indx2++;
  if(indx2 >= nbr_steps2) indx2 = 0;
}
