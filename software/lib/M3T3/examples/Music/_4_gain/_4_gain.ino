#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int delayTime = 100;
int cnt = 0;
float baseFrequency = 110;
long timeNow;
long lastTime = 0;

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.setFrequency(220);
  Music.setDetune(0.005); // ranges from 0.00 - 0.02 are usually good
  Music.setWaveform(PULSE);
  Music.setFrequency1(baseFrequency*1);
  Music.setFrequency2(baseFrequency*1.3333);
  Music.setFrequency3(baseFrequency*1.5);
  
}

void loop() {

  timeNow = millis();
  if((timeNow-lastTime) > delayTime) {
    cnt = cnt + 1;
    if(cnt>16) cnt = 0;
    float counter = float(cnt);
    Music.setGain1(1.0/cnt);
    Music.setGain2(1.0/cnt);
    Music.setGain3(1.0/cnt);
    lastTime = timeNow;
  }   
}
