#include <Arduino.h>
#include <ESP8266WiFi.h>


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
	}

	int potValue = analogRead(A0);
	int delayValue = map(potValue, 0, 1023, 500, 2500);
	delay(delayValue);

	for(int x=0;x<6;x++) {
		digitalWrite(braillePins[x], 0);
	}
	delay(delayValue/4);
}

void displayString(String newsString) {

	int alphabets[][6] = {
		{ 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0 },
		{ 1, 0, 0, 1, 1, 0 },
		{ 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 0, 0 },
		{ 1, 1, 0, 1, 1, 0 },
		{ 1, 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 0 },
		{ 1, 0, 1, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 1, 0, 1, 0, 1, 0 },
		{ 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 0 },
		{ 0, 1, 1, 1, 1, 0 },
		{ 1, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 1 },
		{ 0, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 1 } // a-z
	};

	int charPeriod[]		= { 0, 1, 0, 0, 1, 1 }; // "."
	int charComam[]			= { 0, 1, 0, 0, 0, 0 }; // ","
	int charExcl[]			= { 0, 1, 1, 0, 1, 0 }; // "!"
	int charSemiColon[]		= { 0, 1, 1, 0, 0, 0 }; // ";"
	int charColon[]			= { 1, 0, 0, 0, 1, 1 }; // ":"
	int charAt[]			= { 0, 0, 0, 1, 0, 0 }; // "@"
	int charAmp[]			= { 1, 1, 1, 1, 0, 1 }; // "&"
	int charPlus[]			= { 0, 0, 1, 1, 0, 1 }; // "+"
	int charMinus[]			= { 0, 0, 1, 0, 0, 1 }; // "-"
	int charEquals[]		= { 1, 1, 1, 1, 1, 1 }; //"="

	int upperCaseSymbol[] 	= { 0, 0, 0, 0, 0, 1 };
	int numberSymbol[]		= { 0, 0, 1, 1, 1, 1 };
	int spaceSymbol[]		= { 1, 1, 1, 1, 1, 1 };

	for(int i=0;i<newsString.length();i++) {
		Serial.println(newsString[i]);

		if(islower(newsString[i])) {
			displayLetter(alphabets[(int)newsString[i]-97]);
		}
		else if(isupper(newsString[i])) {
			displayLetter(upperCaseSymbol);
			displayLetter(alphabets[(int)newsString[i]-65]);
		}
		else if(isdigit(newsString[i])) {
			displayLetter(numberSymbol);
			displayLetter(alphabets[(int)newsString[i]-48]);
		}
	}
}

void setupPins() {
	for(int i=0;i<6;i++) {
		pinMode(braillePins[i], OUTPUT);
	}
}

void setupWiFi(){
	Serial.println("\nConnecting...");
	WiFi.begin("MITS", "mits@12345");
	while(WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.println("\nConnected : ");
	Serial.println(WiFi.localIP());

  }


void setup() {
	Serial.begin(115200);
	setupPins();
	setupWiFi();
}

void loop() {
	displayString(Serial.readString());
}
