#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#include <PacketSerial.h>
#include "Communications.h"

#include "TemperatureSensor.h"
#include "ValveControl.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Servo Pin
#define SERVO_PIN 9

//Comms instance
PacketSerial pktSerial; //EXTERN

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
TemperatureSensor temperatureSensor(&oneWire); //EXTERN

//set up the valve control servo
ValveControl butterflyValve(SERVO_PIN); //EXTERN

double valvePosition = 0.25;

void setup() {

	//defaults to COBS encoding, 256-byte buffer.
	Serial.begin(115200);
	pktSerial.begin(&Serial);
	pktSerial.setPacketHandler(&CommunicationsHandler::onPacketReceived);

	pinMode(13, OUTPUT);
	temperatureSensor.begin();
	temperatureSensor.setPollRate(750);//750ms update rate

	butterflyValve.begin();
	butterflyValve.SetValvePosition(0.5);
}

void loop() {
	pktSerial.update();
	temperatureSensor.pollTemperature();
//	if(temperatureSensor.hasNewTemperature())
//	{
//		temperatureSensor.getTemperature_C();
//		//update valve positon, because we can?
//		if(valvePosition < 0.5)
//			valvePosition = 0.75;
//		else
//			valvePosition = 0.25;
//
//		butterflyValve.SetValvePosition(valvePosition);
//
//	}
}
