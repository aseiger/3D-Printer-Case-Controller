/*
 * ValveControl.h
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 */

#ifndef VALVECONTROL_H_
#define VALVECONTROL_H_

class ValveControl
{
private:
	unsigned int minimumPulse;
	unsigned int maximumPulse;
	double setPoint;

	Servo servo;
	int servoPin;

public:
	ValveControl(unsigned int pin);
	void begin(void);
	int SetValvePosition(double position);
	int setMinimumPulse(unsigned int pulse);
	int setMaximumPulse(unsigned int pulse);
};



#endif /* VALVECONTROL_H_ */
