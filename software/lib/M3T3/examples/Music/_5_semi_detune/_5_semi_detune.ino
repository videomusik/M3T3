#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.setFrequency(110);
  Music.setDetune(0.001); // ranges from 0.00 - 0.02 are usually good
  Music.setWaveform(DIGI2);
  Music.setSemitone1(0);
  Music.setSemitone2(7);
  Music.setSemitone3(-12);
}

void loop() {

}
