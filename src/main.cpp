#include <Arduino.h>

int braillePins[] = {D1, D2, D3, D4, D5, D6};

void testPins() {
	// For testing connections
	for(int i=0;i<6;i++) {
		digitalWrite(braillePins[i], HIGH);
		delay(1000);
	}

	for(int i=0;i<6;i++) {
		digitalWrite(braillePins[i], LOW);
		delay(1000);
	}
}

void displayLetter(int letterValue[6]) {
	for(int i=0;i<6;i++) {
		digitalWrite(braillePins[i], letterValue[i]);
		delay(1000);
	}
}

void displayString(String newsString) {

	int alphabets[][6] = {
		{ 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0 },
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		// {,,,,,},
		{ 1, 0, 1, 0, 1, 1}
	};

	for(int i=0;i<newsString.length();i++) {
		if(islower(newsString[i])) {
			displayLetter(alphabets[(int)newsString[i]-97]);
		}
	}
}

void setupPins() {
	for(int i=0;i<6;i++) {
		pinMode(braillePins[i], OUTPUT);
	}
}

void setup() {
	Serial.begin(115200);
	setupPins();
}

void loop() {
	displayString(Serial.readString());
}
