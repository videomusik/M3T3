#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int delayTime = 2000;
int cnt = 0;
long timeNow;
long lastTime = 0;

byte waveFormArray[] = { SINE,
                        SQUARE,
                        PULSE,
                        TRIANGLE,
                        SAW,
                        FUZZ,
                        DIGI1,
                        DIGI2,
                        DIGI3,
                        DIGI4,
                        NOISE,
                        DIGI6,
                        TAN1,
                        TAN2,
                        TAN3,
                        TAN4
                       };

void setup() {
  
  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.setFrequency(220);
  Music.setWaveform(SINE);
}

void loop() {
  
  timeNow = millis();
  if((timeNow-lastTime) > delayTime) {
    cnt = cnt + 1;
    if(cnt>15) cnt = 0;
    Music.setWaveform(waveFormArray[cnt]);
    lastTime = timeNow;
  }   
}
