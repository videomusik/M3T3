//FM synthes of a sort
//hang on!  it's unstable and wants to limit cycle

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

byte cnt;
float xf, vf; //
float k = 10.0; // increase FM frequency
float b = 0.4; // increase
float Tf = .001 ; //integration time

void setup(){
  Serial.begin(9600);
  Music.init();
  Music.set12bit(true);
  Music.setWaveform(0);
  Music.setGain(1.0f);
  MotorA.init();
  analogReadAveraging(32);
}

void loop(){
  xf += vf * Tf;
  vf += (k * (analogRead(A1) - xf) - b*vf) * Tf;
  Music.setFrequency(100+vf);
  Music.setGain(.01*abs(vf));
  MotorA.torque(-500+xf);
  //if(cnt++==0)Serial.println(.001*abs(vf));
}
