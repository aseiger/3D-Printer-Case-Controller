/*
 * Communications.cpp
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 */
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include "TemperatureSensor.h"
#include "ValveControl.h"

#include <PacketSerial.h>
#include "Communications.h"

extern PacketSerial pktSerial;
extern TemperatureSensor temperatureSensor;
extern ValveControl butterflyValve;

void CommunicationsHandler::onPacketReceived(const uint8_t* buffer, size_t size)
{
	//pktSerial.send(buffer, size);
	switch(buffer[0])
	{
		case CommunicationsHandler::HEARTBEAT:
		{
			uint8_t writeBuffer[] = {1, 0x0D, 0x0E, 0x0A, 0x0D};
			pktSerial.send(writeBuffer, sizeof(writeBuffer));
		}
		break;
		case CommunicationsHandler::STATUS_REQUEST:
		{
			float currentTemp = temperatureSensor.getTemperature_C();
			pktSerial.send(reinterpret_cast<uint8_t *>(&currentTemp), sizeof(currentTemp));
		}
		break;
		case CommunicationsHandler::SET_VALVE_POSITION:
		{
			float valvePositionSetting;
			memcpy(&valvePositionSetting, &buffer[1], sizeof(valvePositionSetting));
			butterflyValve.SetValvePosition(static_cast<double>(valvePositionSetting));
			pktSerial.send(buffer, size);
		}
	}
}



