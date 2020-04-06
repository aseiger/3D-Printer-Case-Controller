/*
 * TemperatureSensor.cpp
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 */
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(OneWire *oneWire)
{
	_oneWire = oneWire;
	sensor.setOneWire(_oneWire);
	lastReadTemperature = 0.0;
	newTemperature = false;
	deviceCount = 0;

	lastUpdateTime = 0;
	pollRate = 1000;
}

TemperatureSensor::~TemperatureSensor()
{
	_oneWire->reset();
}

void TemperatureSensor::setPollRate(unsigned int _pollRate)
{
	pollRate = _pollRate;
}

void TemperatureSensor::begin(void)
{
	sensor.begin();
	deviceCount = sensor.getDeviceCount();

	//determine device address
	_oneWire->reset_search();
	_oneWire->search(sensorAddr);
	//set to resolution 12-bit
	sensor.setResolution(sensorAddr, 12);
	sensor.setWaitForConversion(false);
	sensor.requestTemperatures(); // Send the command to get temperatures
	lastUpdateTime = millis();
}

void TemperatureSensor::pollTemperature(void)
{
	if(millis() > (lastUpdateTime + pollRate))
	{
		newTemperature = false;
		lastUpdateTime = millis();
		lastReadTemperature = sensor.getTempC(sensorAddr);
		sensor.requestTemperatures(); // Send the command to get temperatures
		newTemperature = true;
	}
}

bool TemperatureSensor::hasNewTemperature(void)
{
	return newTemperature;
}

double TemperatureSensor::getTemperature_C(void)
{
	newTemperature = false;
	return lastReadTemperature;
}


