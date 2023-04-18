#include "ProjectsA1.h"

#define ID_PROJECT ID4
#define PIN_SENSOR 4
#define PIN_SERVO 5
#define PIN_ALARM 14
#define TRESHOLD_TEMPERATURE 30.0
#define TRESHOLD_HUMIDITY 88.0

ProjectsA1 go(ID_PROJECT, PIN_SENSOR, PIN_SERVO, PIN_ALARM, TRESHOLD_TEMPERATURE, TRESHOLD_HUMIDITY);

void setup(){
  Serial.begin(9600);
  go.begin();
}

void loop(){
  go.run();
}