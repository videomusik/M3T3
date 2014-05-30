#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int delayTime = 400;
int cnt = 0;
float baseFrequency = 110;
long timeNow;
long lastTime = 0;

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.setFrequency(220);
  Music.setDetune(0.001); // ranges from 0.00 - 0.02 are usually good
  Music.setWaveform(TRIANGLE);

}

void loop() {
  
  timeNow = millis();
  if((timeNow-lastTime) > delayTime) {
    cnt = cnt + 1;
    if(cnt>3) cnt = 0;
    Music.setFrequency1(baseFrequency*1*cnt);
    Music.setFrequency2(baseFrequency*1.3333*cnt);
    Music.setFrequency3(baseFrequency*1.5*cnt);
    lastTime = timeNow;
  }   
}
