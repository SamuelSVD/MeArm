#include <Servo.h>
#include "mearm.h"

#define HIGH_ANGLE 180
#define LOW_ANGLE 0
#define DELAY 40

MeArm * meArm;

int pos;
bool dir = true;

void setup() {
  meArm = new MeArm(9, 6, 5, 3);
  meArm->setOffsets(0, 145, 90, 20);
  Serial.begin(115200);
}

void doMove(int angle)
{
  if (dir) meArm->closeGrip();
  else meArm->openGrip();
  meArm->goTo(7+(float)(pos-90)/20, 4.0+ (180.0-pos) / 50, 80-pos/2);
  delay(DELAY);
}

void loop() {
  dir = false;
  for (pos = LOW_ANGLE; pos < HIGH_ANGLE; pos++) {
    doMove(pos);
  }
  dir = true;
  for (pos = HIGH_ANGLE; pos > LOW_ANGLE; pos--) {
    doMove(pos);
  }
}

