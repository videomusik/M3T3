//"Pulse" - small duration positive then negative force 
// parameters: F1, T1, D1, F2, T2, D2

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup(){
  MotorA.init();
  Music.init();
  Music.set12bit(true);
  
  Music.setWaveform(SINE);
  Music.enableEnvelope1();
  Music.setEnv1Attack(10);
  Music.setEnv1Decay(10);
  Music.setEnv1Release(10);
}

void loop(){
    MotorA.start();
    MotorA.torque(200);
    Music.noteOn(map(analogRead(A1),0,1023,30,60));
    delay (20);
    Music.noteOff();
    MotorA.torque(0);
    delay (150);
    MotorA.torque(-200);
    Music.noteOn(map(analogRead(A1),0,1023,35,65));
    delay (40);
    Music.noteOff();
    MotorA.torque(0);
    MotorA.stop();
    delay (750);
}
