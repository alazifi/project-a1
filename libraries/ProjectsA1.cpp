#include "ProjectsA1.h"
#include "DHTesp.h"
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BlynkEdgent.h"
#include "CTBot.h"
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MIN_PULSE 500
#define MAX_PULSE 2500
#define OLED_RESET -1

DHTesp dht;
CTBot myBot;
Servo myservo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int position = 0;
int cond = 0;
int maxServo = 80;
char message[160];

unsigned long previousMillis = 0;
unsigned long interval = 200; //delay Blynk

ProjectsA1::ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output){
	_id = id;
	_pin_input = pin_input;
	_pin_output = pin_output;
}

ProjectsA1::ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, int duration, float treshold){
	_id = id;
	_pin_input = pin_input;
	_pin_output = pin_output;
	_duration = duration;
	_treshold = treshold;
}

ProjectsA1::ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, int duration, float treshold, String token_tele, int id_tele){
	_id = id;
	_pin_input = pin_input;
	_pin_output = pin_output;
	_duration = duration;
	_treshold = treshold;
	_token_tele = token_tele;
	_id_tele = id_tele;
}

ProjectsA1::ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, uint8_t pin_alarm, float treshold_temp, float treshold_hum){
	_id = id;
	_pin_input = pin_input;
	_pin_output = pin_output;
	_pin_alarm = pin_alarm;
	_treshold_temp = treshold_temp;
	_treshold_hum = treshold_hum;
}

ProjectsA1::~ProjectsA1(){}

void ProjectsA1::runServo(){
	switch(_id){
		case ID2:
			myservo.write(position);
			delay(20);
			break;
		case ID4:
			myservo.write(position);
			delay(20);
			if(position < 180 && position >= 1){
				digitalWrite(_pin_alarm, HIGH);
			}else{
				digitalWrite(_pin_alarm, LOW);
			}
			break;
	}
}

void ProjectsA1::openGarage(){
	if(position == 0){
		for (position = 0; position <= maxServo; position += 1){
		runServo();
		}
	}else{
		position = maxServo;
	}
}

void ProjectsA1::closeGarage(){
	if(position == maxServo){
		for (position = maxServo; position >= 0; position -= 1){
		runServo();
		}
	}else{
		position = 0;
	}
}

void ProjectsA1::begin() {
	switch(_id){
		case ID1:
			pinMode(_pin_input, INPUT);
			pinMode(_pin_output, OUTPUT);
			if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
				Serial.println(F("SSD1306 allocation failed"));
			for(;;);}
			break;
		case ID2:
			pinMode(_pin_input, INPUT);
			myservo.attach(_pin_output, MIN_PULSE, MAX_PULSE);
			myservo.write(maxServo);
			break;
		case ID3:
			pinMode(_pin_input, INPUT);
			pinMode(_pin_output, OUTPUT);
			delay(100);
			BlynkEdgent.begin();
			break;
		case ID4:
			pinMode(_pin_alarm, OUTPUT);
			dht.setup(_pin_input, DHTesp::DHT11);
			myservo.attach(_pin_output, MIN_PULSE, MAX_PULSE);
			myservo.write(0);
			break;
	}
}

void ProjectsA1::run(){
	switch(_id){
		case ID1:
			valueDisplay();
			triggerAlarm(UVvalue() >= _treshold);
			break;
		case ID2:
			triggerServo(digitalRead(_pin_input) == HIGH);
			break;
		case ID3:
			runBlynk();
			sendTelegram(vibration() >= _treshold && vibration() <= 10);
			triggerAlarm(vibration() >= _treshold);
			break;
		case ID4:
			triggerServo(dht.getHumidity() >= _treshold_hum || dht.getTemperature() <= _treshold_temp);
			break;
	}
}

void ProjectsA1::writeBlynk(){
	Blynk.virtualWrite(V0, vibration());
}

void ProjectsA1::runBlynk(){
	BlynkEdgent.run();
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= interval){
		previousMillis = currentMillis;
		writeBlynk();
  }
}

void ProjectsA1::triggerServo(bool condition){
	if(condition){
		cond = 1;
	}else{
		cond = 2;
	}

	switch(cond){
		case 1:
			openGarage();
			break;
		case 2:
			closeGarage();
			break;
	}
	delay(1000);	
}

void ProjectsA1::triggerAlarm(bool condition){	
	if(condition){
		sendTelegram(condition && vibration() <= 10);
		for(int i = 0; i <= _duration; i+=1){
			digitalWrite(_pin_output, HIGH);
			delay(1);
		}
	}else{
		digitalWrite(_pin_output, LOW);
	}
	delay(200);	
}

void ProjectsA1::sendTelegram(bool condition){
	if(condition){
		myBot.setTelegramToken(_token_tele);
		sprintf(message,"Earthquake Magnitude: %.1f SR", vibration());
		myBot.sendMessage(_id_tele, message);
	}
}

long ProjectsA1::pulseVibration(){
	delay(10);
	long pulseVibration = pulseIn(_pin_input, HIGH);
	return pulseVibration;
}

float ProjectsA1::vibration(){
	float vibration =(10.0/1200)*pulseVibration();
	return vibration;
}

int ProjectsA1::averageAnalogRead(int pinToRead){
	byte numberOfReadings = 8;
	unsigned int runningValue = 0; 
		for(int x = 0 ; x < numberOfReadings ; x++)
			runningValue += analogRead(pinToRead);
			runningValue /= numberOfReadings;
	return(runningValue);  
}

float ProjectsA1::mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ProjectsA1::displayOLED(uint8_t textSize, uint16_t x, uint16_t y, uint16_t textColor, String caption){
	display.setTextSize(textSize);
	display.setCursor(x, y);
	display.setTextColor(textColor);
	display.println(caption);
}

void ProjectsA1::valueDisplay(){
	display.clearDisplay();
	displayOLED(2, 28,  0, WHITE, "UV Int");
	displayOLED(4, 15, 20, WHITE, String(UVvalue()));
	displayOLED(1, 43, 55, WHITE, "mW/cm^2");
	display.display();
}

float ProjectsA1::UVvalue(){
	int uvLevel = averageAnalogRead(_pin_input);
	float outputVoltage = 3.3 * uvLevel/1024;
	float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);
	return uvIntensity;
}