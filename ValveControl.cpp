/*
 * ValveControl.cpp
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 */

#include <Arduino.h>
#include <Servo.h>
#include "ValveControl.h"

ValveControl::ValveControl(unsigned int pin)
{
	servoPin = pin;
	minimumPulse = 1000;
	maximumPulse = 2000;
	setPoint = 0.0;
}

void ValveControl::begin(void)
{
	servo.attach(servoPin);
}

int ValveControl::SetValvePosition(double position)
{
	if((position < 0) || (position > 1.0))
	{
		return -1;
	}
	setPoint = position;
	double range = maximumPulse - minimumPulse;
	double output = (position * range) + static_cast<double>(minimumPulse);
	int pulseVal = static_cast<int>(output);
	servo.writeMicroseconds(pulseVal);
}

int ValveControl::setMaximumPulse(unsigned int pulse)
{
	if(pulse <= minimumPulse)
	{
		return -1;
	}

	minimumPulse = pulse;
	//update the position of the servo to reflect the new maximum pulse
	SetValvePosition(setPoint);
	return 0;
}

int ValveControl::setMinimumPulse(unsigned int pulse)
{
	if(pulse >= maximumPulse)
	{
		return -1;
	}

	maximumPulse = pulse;
	//update the position of the servo to reflect the new minimum pulse
	SetValvePosition(setPoint);
	return 0;
}



