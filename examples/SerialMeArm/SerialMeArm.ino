#include <Servo.h>
#include "mearm.h"

SerialMeArm * meArm;

String message;
bool messageReady = false;

void setup() {
  meArm = new SerialMeArm(9, 6, 5, 3);
  meArm->setOffsets(0, 145, 90, 20);
  meArm->setAngles(90, 90, 0, 0);
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

