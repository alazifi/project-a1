#include "ProjectsA1.h"

#define ID_PROJECT ID3
#define PIN_SENSOR 5
#define PIN_ALARM 4
#define DURATION 5000
#define TRESHOLD_VIBRATION 5.0
#define TOKEN_TELEGRAM "5844171478:AAEanxQ38aS4lv0vJjwljwazGtWfnl-OD5o"
#define ID_TELEGRAM 5966432787

ProjectsA1 sqes(ID_PROJECT, PIN_SENSOR, PIN_ALARM, DURATION, TRESHOLD_VIBRATION, TOKEN_TELEGRAM, ID_TELEGRAM);

void setup(){
  sqes.begin();
}

void loop(){
  sqes.run();
}