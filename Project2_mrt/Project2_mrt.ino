#include "ProjectsA1.h"

#define ID_PROJECT ID2
#define PIN_SENSOR 4
#define PIN_SERVO 5

ProjectsA1 mrt(ID_PROJECT, PIN_SENSOR, PIN_SERVO);

void setup(){
  mrt.begin();
}

void loop(){
  mrt.run();
}