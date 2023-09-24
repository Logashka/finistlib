#include "finistSensor.h"

class Base
{
public:
    float d, b;
    LineSensor* left_line;
    LineSensor* right_line;
    Encoder* right_encoder;
    Encoder* left_encoder;
    Base(float wheel_diameter, float distance_between_wheels){
        d = wheel_diameter;
        b = distance_between_wheels;
    }

    void setup_lineSensors(LineSensor &left, LineSensor &right){
        this->right_line = &right;
        this->left_line = &left;
    }

    void setup_encoders(Encoder* left, Encoder* right){
        this->right_encoder = right;
        this->left_encoder = left;
    }
};
