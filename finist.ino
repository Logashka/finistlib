#include "finistAlgoritm.h"

#define RIGHT_MOTOR_E 6
#define RIGHT_MOTOR_H 7
#define LEFT_MOTOR_E 5
#define LEFT_MOTOR_H 4
#define LEFT_LINE_PIN A1
#define RIGHT_LINE_PIN A0
#define SHARP_PIN A2

Encoder *left_encoder;
Encoder *right_encoder;
LineSensor right_line(RIGHT_LINE_PIN);
LineSensor left_line(LEFT_LINE_PIN);
Sharp dist_sensor(SHARP_PIN);
Motor left_motor(LEFT_MOTOR_H, LEFT_MOTOR_E);
Motor right_motor(RIGHT_MOTOR_H, RIGHT_MOTOR_E);
Base robot(8.8, 19);


void setup() {
    left_encoder = new Encoder(4, 5, 2);
    right_encoder = new Encoder(6, 7, 3);
    left_encoder->setup([] { left_encoder->EncoderEvent(); });
    right_encoder->setup([] { right_encoder->EncoderEvent(); });

    right_motor.setup();
    left_motor.setup(true);

    left_line.setup();
    right_line.setup();
    //left_line.auto_calibration(3);
    //right_line.auto_calibration(3);

    dist_sensor.setup();

    robot.setup_lineSensors(left_line, right_line);
    robot.setup_encoders(left_encoder, right_encoder);
    robot.setup_motors(left_motor, right_motor);

    Serial.begin(9600);
}

void loop() {
    Serial.println(String(left_line.get_percent()) + "      " + String(right_line.get_percent()));
    turn_line(robot, "tank_right", 50, true);
    //turn_time(robot,"tank_right", 50, 0.1, false);
    delay(2000);
}
