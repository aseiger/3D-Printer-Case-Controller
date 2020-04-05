#include <Arduino.h>
#include "OneWire\OneWire.h"
#include "Arduino-Temperature-Control-Library/DallasTemperature.h"
#include "TemperatureSensor.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
TemperatureSensor temperatureSensor(&oneWire);

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	Serial.println("Starting...");
	temperatureSensor.begin();
	temperatureSensor.setPollRate(5000);//500ms update rate
}

void loop() {
	temperatureSensor.pollTemperature();
	if(temperatureSensor.hasNewTemperature())
	{
		Serial.println(temperatureSensor.getTemperature_C());
	}
}
