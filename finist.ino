#include "finistSensor.h"

void setup() {
  // put your setup code here, to run once:
  LineSensor left_sensor(A0);
  Serial.begin(9600);
  Serial.println(left_sensor.s_port);
}

void loop() {
  // put your main code here, to run repeatedly:

}
