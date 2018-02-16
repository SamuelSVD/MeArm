#include <Servo.h>
#include "mearm.h"

SerialMeArm * meArm;

String message;
bool messageReady = false;

void setup() {
  meArm = new SerialMeArm(3, 5, 6, 11);
  meArm->setOffsets(0, 135, 0, 0);
  Serial.begin(115200);
}

void loop() {
  if (messageReady) {
    meArm->handleMessage(message);
    message = "";
    messageReady = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
      messageReady = true;
    } else {
      message += c;
    }
  }
}

