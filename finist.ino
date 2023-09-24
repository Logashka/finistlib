#include "finistSensor.h"
#include "finistMotor.h"

class Base {
private:
    LineSensor *left_line;
    LineSensor *right_line;
    Encoder *right_encoder;
    Encoder *left_encoder;
    Motor *right_motor;
    Motor *left_motor;
public:
    float d, b;


    Base(float wheel_diameter, float distance_between_wheels) {
        d = wheel_diameter;
        b = distance_between_wheels;
    }


    void setup_lineSensors(LineSensor &left, LineSensor &right) {
        this->right_line = &right;
        this->left_line = &left;
    }


    void setup_encoders(Encoder *left, Encoder *right) {
        this->right_encoder = right;
        this->left_encoder = left;
    }


    void setup_motors(Motor &left, Motor &right){
        this->right_motor = &right;
        this->left_motor = &left;
    }
};
