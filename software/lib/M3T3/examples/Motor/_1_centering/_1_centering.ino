#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

void setup() {

  Serial.begin(9600);
  MotorA.init();
  MotorB.init();
  analogReadAveraging(32);
}

void loop() {

  usbMIDI.read();
  int valueA = analogRead(A1);
  int valueB = analogRead(A9);
  int torqueA = (512-valueA);
  int torqueB = (512-valueB);
//  Serial.print("valueA = ");
//  Serial.print(valueA);
//  Serial.print(" --- valueB = ");
//  Serial.println(valueB);
//  delay(50);
  MotorA.torque(torqueA*4);
  MotorB.torque(torqueB*4);
}
