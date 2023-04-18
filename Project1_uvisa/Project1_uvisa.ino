#include "ProjectsA1.h"

#define ID_PROJECT ID1
#define PIN_SENSOR A0
#define PIN_ALARM 14
#define DURATION 5000
#define TRESHOLD_UV 3.00

ProjectsA1 uvisa(ID_PROJECT, PIN_SENSOR, PIN_ALARM, DURATION, TRESHOLD_UV);

void setup(){
  uvisa.begin();
}

void loop(){
  uvisa.run();
}