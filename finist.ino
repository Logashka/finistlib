#include "finistSensor.h"
Encoder* left_encoder;
Encoder* right_encoder;


void setup() {
  // put your setup code here, to run once:
  left_encoder = new Encoder (4,5,2);
  right_encoder = new Encoder (6, 7, 3);
  left_encoder->setup([]{left_encoder->EncoderEvent();});
  right_encoder->setup([]{right_encoder->EncoderEvent();});

}

void loop() {
  // put your main code here, to run repeatedly:

}
