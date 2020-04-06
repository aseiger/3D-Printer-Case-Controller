/*
 * TemperatureSensor.h
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 */

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

class TemperatureSensor
{
private:
	OneWire *_oneWire;
	DallasTemperature sensor;
	DeviceAddress sensorAddr;

	unsigned int deviceCount;

	unsigned long lastUpdateTime;
	unsigned int pollRate;

	double lastReadTemperature;
	bool newTemperature;

public:
	TemperatureSensor(OneWire *oneWire);
	~TemperatureSensor();

	void begin(void);
	void setPollRate(unsigned int pollRate); //set Poll Rate in ms.
	void pollTemperature(void);
	bool hasNewTemperature(void);
	double getTemperature_C(void);
};

#endif /* TEMPERATURESENSOR_H_ */
