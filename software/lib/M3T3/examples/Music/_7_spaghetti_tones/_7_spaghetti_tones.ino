#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

// variables for this sketch
float gain = 1.0;
float c = 220; // center frequency
float f1 = 1;
float f2 = 1;
float f3 = 1;
float m1 = 1.0011;
float m2 = 1.0012;
float m3 = 1.0013;


void setup() {

  Music.init();
  Music.set12bit(true);
  Music.setWaveform(SINE);
  Music.setFrequency(c);
  Music.setDetune(0.002);  
  
}

void loop() {
  
    Music.setFrequency1(c*f1);
    Music.setFrequency2(c*f2);
    Music.setFrequency3(c*f3);
    
    f1 *= m1;
    f2 *= m2;
    f3 *= m3;
    
    if(f1 > 4.0) m1 = 0.999745;
    if(f2 > 4.0) m2 = 0.999852;
    if(f3 > 4.0) m3 = 0.999975;
    
    if(f1 < 0.25) m1 = 1.000754;
    if(f2 < 0.25) m2 = 1.000573;
    if(f3 < 0.25) m3 = 1.000386;
      
    if(millis() > 10000) {
      Music.setGain(gain);
      gain *= 0.99999;
    }
}

