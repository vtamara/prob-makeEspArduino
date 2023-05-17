// Example that fails in adJ/OpenBSD 7.2 with makeEspArduino 6.8.1 
// (also fails with 6.6.5 that is the version of the port of
// makeEspArduino for OpenBSD 7.2 and 7.3)

// The following four lines are based on
// https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
#include "Arduino.h"
#if defined(__AVR__)
#include <SoftwareSerial.h>
#endif

// Simple example

void setup() {
	Serial.println("1");
	Serial.begin(115200);
	Serial.println("2");
}

void loop() {
}
