#ifndef ProjectsA1_H
#define ProjectsA1_H
#include <Arduino.h>

static const uint8_t ID1{1};
static const uint8_t ID2{2};
static const uint8_t ID3{3};
static const uint8_t ID4{4};

class ProjectsA1{
	public :
		ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output);
		ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, int duration, float treshold);
		ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, int duration, float treshold, String token_tele, int id_tele);
		ProjectsA1(uint8_t id, uint8_t pin_input, uint8_t pin_output, uint8_t pin_alarm, float treshold_temp, float treshold_hum);
		~ProjectsA1();
		void runServo();
		void openGarage();
		void closeGarage();
		void begin();
		void run();
		void writeBlynk();
		void runBlynk();
		void triggerServo(bool condition);
		void triggerAlarm(bool condition);
		void sendTelegram(bool condition);
		long pulseVibration();
		float vibration();
		int averageAnalogRead(int pinToRead);
		float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
		void valueDisplay();
		float UVvalue();
		void displayOLED(uint8_t textSize, uint16_t x, uint16_t y, uint16_t textColor, String caption);
	private:
		uint8_t _id, _pin_input, _pin_output, _pin_alarm;
		int _duration, _id_tele;
		float _treshold, _treshold_temp, _treshold_hum;
		String _token_tele;
};

#endif