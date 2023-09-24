#include "finistBase.h"

//тут дефайны

Encoder* left_encoder;
Encoder* right_encoder;
LineSensor right_line(A0);
LineSensor left_line(A1);
Base robot(25,25);

void setup() {
  // put your setup code here, to run once:
  left_encoder = new Encoder (4,5,2);
  right_encoder = new Encoder (6, 7, 3);
  left_encoder->setup([]{left_encoder->EncoderEvent();});
  right_encoder->setup([]{right_encoder->EncoderEvent();});
  robot.setup_lineSensors(left_line, right_line);
  robot.setup_encoders(left_encoder, right_encoder);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
