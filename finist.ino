#include "finistAlgoritm.h"

#define RIGHT_MOTOR_E 6
#define RIGHT_MOTOR_H 7
#define LEFT_MOTOR_E 5
#define LEFT_MOTOR_H 4
#define LEFT_LINE_PIN A1
#define RIGHT_LINE_PIN A0

Encoder* left_encoder;
Encoder* right_encoder;
LineSensor right_line(RIGHT_LINE_PIN);
LineSensor left_line(LEFT_LINE_PIN);
Motor left_motor(LEFT_MOTOR_H, LEFT_MOTOR_E);
Motor right_motor(RIGHT_MOTOR_H, RIGHT_MOTOR_E);
Base robot(8.8,19);


void setup() {
  left_encoder = new Encoder (4,5,2);
  right_encoder = new Encoder (6, 7, 3);
  left_encoder->setup([]{left_encoder->EncoderEvent();});
  right_encoder->setup([]{right_encoder->EncoderEvent();});
  right_motor.setup();
  left_motor.setup(true);
  left_line.setup();
  right_line.setup();


  robot.setup_lineSensors(left_line, right_line);
  robot.setup_encoders(left_encoder, right_encoder);
  robot.setup_motors(left_motor, right_motor);


  Serial.begin(9600);
}

void loop() {
  robot.right_motor->start_percent(100);
  robot.left_motor->start_percent(100);
  delay(100);
}
