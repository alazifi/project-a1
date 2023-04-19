#include "ProjectsA1.h"

#define ID_PROJECT ID3
#define PIN_SENSOR 5
#define PIN_ALARM 4
#define DURATION 5000
#define TRESHOLD_VIBRATION 5.0
#define TOKEN_TELEGRAM "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define ID_TELEGRAM 1111111111

ProjectsA1 sqes(ID_PROJECT, PIN_SENSOR, PIN_ALARM, DURATION, TRESHOLD_VIBRATION, TOKEN_TELEGRAM, ID_TELEGRAM);

void setup(){
  sqes.begin();
}

void loop(){
  sqes.run();
}