#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#include "TemperatureSensor.h"
#include "ValveControl.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Servo Pin
#define SERVO_PIN 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
TemperatureSensor temperatureSensor(&oneWire);

//set up the valve control servo
ValveControl butterflyValve(SERVO_PIN);

double valvePosition = 0.25;

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	Serial.println("Starting...");
	temperatureSensor.begin();
	temperatureSensor.setPollRate(2500);//500ms update rate

	butterflyValve.begin();
	butterflyValve.SetValvePosition(0.5);
}

void loop() {
	temperatureSensor.pollTemperature();
	if(temperatureSensor.hasNewTemperature())
	{
		Serial.println(temperatureSensor.getTemperature_C());

		//update valve positon, because we can?
		if(valvePosition < 0.5)
			valvePosition = 0.75;
		else
			valvePosition = 0.25;

		butterflyValve.SetValvePosition(valvePosition);

	}
}
