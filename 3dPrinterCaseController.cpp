#include <Arduino.h>

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(115200);
}

void loop() {
	for(int i = 0; i < 4; i++)
	{
		delay(50);
		digitalWrite(13, HIGH);
		delay(50);
		digitalWrite(13, LOW);
	}
	delay(1500);
	digitalWrite(13, LOW);
	Serial.println("BLINKY");
}
