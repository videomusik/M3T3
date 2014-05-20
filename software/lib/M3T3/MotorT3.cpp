/* 
 Motor.cpp - Motor library
 Copyright (c) 2012 Copenhagen Institute of Interaction Design. 
 All right reserved.
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser Public License for more details.
 
 You should have received a copy of the GNU Lesser Public License
 along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + author: dviid
 + contact: dviid@labs.ciid.dk 
 */

#include "MotorT3.h"
#include <wiring.h>
//#include <stdlib.h>
//#include <avr/interrupt.h>

#define RESOLUTION 65536

#define ENABLE_12 2
#define INPUT_1 3
#define INPUT_2 5
#define ENABLE_34 7
#define INPUT_3 6
#define INPUT_4 4

bool reg_init = false;


MMotor MotorA(MOTORA); // this is motor A
MMotor MotorB(MOTORB); // this is motor B

// IntervalTimer motorTimer;


MMotor::MMotor(MOTOR m)
{
    _m = m;
}

void MMotor::init()
{   
	// For best frequencies see http://www.pjrc.com/teensy/td_pulse.html
	analogWriteFrequency(INPUT_1,23437); // 93750
	analogWriteFrequency(INPUT_2,23437); // 93750
	analogWriteFrequency(INPUT_3,23437); // 93750
	analogWriteFrequency(INPUT_4,23437); // 93750
	analogWriteResolution(9);
	pinMode(ENABLE_12, OUTPUT);
	pinMode(ENABLE_34, OUTPUT);
	_d = FORWARD;
	_t = 0;	
	direction(_d);
	start();
}


void MMotor::torque(int t) 
{	
	if(t < 0) {
		_d = BACKWARD;
	} else {
		_d = FORWARD;
	}
	t = abs(t);
	if(t > 512) t = 512;
    _t = t;
	direction(_d);
}


int MMotor::torque()
{
    return _t;
}


void MMotor::direction(DIRECTION d)
{
    _d = d;
    if(_m == MOTORA && _d == FORWARD) {
		analogWrite(INPUT_1, 0);
		analogWrite(INPUT_2, _t);
	}
    else if(_m == MOTORA && _d == BACKWARD) {
		analogWrite(INPUT_1, _t);
		analogWrite(INPUT_2, 0);
	}
    else if(_m == MOTORB && _d == FORWARD) {
		analogWrite(INPUT_3, 0);
		analogWrite(INPUT_4, _t);
	}
    else if(_m == MOTORB && _d == BACKWARD) {
		analogWrite(INPUT_3, _t);
		analogWrite(INPUT_4, 0);
	}
}


void MMotor::stop()
{
    if(_m == MOTORA) {
		digitalWrite(ENABLE_12, LOW);
	}
    else if(_m == MOTORB) {
		digitalWrite(ENABLE_34, LOW);
	}
}


void MMotor::start()
{
    if(_m == MOTORA) {
		digitalWrite(ENABLE_12, HIGH);
	}
    else if(_m == MOTORB) {
		digitalWrite(ENABLE_34, HIGH);
	}
}


void MMotor::restart()  // DO WE REALLY NEED THIS?????
{
	_d = FORWARD;
	_t = 0;
	direction(_d);
	start();
}

