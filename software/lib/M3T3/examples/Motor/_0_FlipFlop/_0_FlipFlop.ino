#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {
  MotorA.init();
}

void loop() {
  MotorA.torque(500);
  delay(100);
  MotorA.torque(0);  
  delay(2000);
  MotorA.torque(-500);
  delay(100);
  MotorA.torque(0);  
  delay(2000);
}
