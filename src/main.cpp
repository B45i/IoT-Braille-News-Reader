#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

/*
the-times-of-india
google-news-in
techcrunch
the-hindu
the-new-york-times
bbc-news
cnn
fox-news
nbc-news
*/

int braillePins[] = {D1, D2, D3, D4, D5, D6};

char APIKey[34] = "374125c2dfa441c9ae156b7378f2f6e9";

char channels[][25] = {
	"the-times-of-india",
	"the-hindu",
	"google-news-in",
	"techcrunch",
	"the-new-york-times",
	"bbc-news",
	"cnn",
	"fox-news",
	"nbc-news",
	"reuters"
};

void displayLetter(int letterValue[6]) {
	while (!digitalRead(D0)) {
		delay(1);
	}
		for(int i=0;i<6;i++) {
				digitalWrite(braillePins[i], letterValue[i]);
		}

		int potValue = analogRead(A0);
		int delayValue = map(potValue, 0, 1023, 2500, 250);
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

	pinMode(D0, INPUT);
}

// void setupWiFi(){
// 	Serial.println("\nConnecting...");
// 	WiFi.begin("MITS", "mits@12345");
// 	while(WiFi.status() != WL_CONNECTED){
// 		Serial.print(".");
// 		delay(500);
// 	}
// 	Serial.println("\nConnected : ");
// 	Serial.println(WiFi.localIP());
// }

void setup() {
	Serial.begin(115200);
	setupPins();
	//setupWiFi();

	WiFiManager wifiManager;
	wifiManager.autoConnect("Braille-News-Reader");
	Serial.println("Connected ");
}

void loop() {
	// displayString(Serial.readString());

	if (WiFi.status() == WL_CONNECTED) {

		const size_t bufferSize = JSON_ARRAY_SIZE(10) + JSON_OBJECT_SIZE(4) + 10*JSON_OBJECT_SIZE(6) + 7610;
		DynamicJsonBuffer jsonBuffer(bufferSize);

		String newsJSON;

		HTTPClient http;
		String newsURL = "http://newsapi.org/v1/articles?source=the-hindu&sortBy=latest&apiKey="+String(APIKey);

		Serial.print("Sending Request to: ");
		Serial.println(newsURL);

		http.begin(newsURL);
		int httpCode = http.GET();

		if (httpCode > 0) {
			newsJSON = http.getString();
			JsonObject& root = jsonBuffer.parseObject(newsJSON);
			JsonArray& articles = root["articles"];

			for(int i=0;i<10;i++) {
				displayString(articles[i]["title"]);
				displayString(articles[i]["description"]);
			}
		}
		else {
			Serial.println("Unable to connect to newsapi.org");
		}
		http.end();
	}
	else {
		Serial.println("WiFI Disconnected !");
	}
}
