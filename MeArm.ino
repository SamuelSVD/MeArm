#include <Servo.h>
#include "MeArm.h"

#define HIGH_ANGLE 180
#define LOW_ANGLE 0
#define DELAY 40
//Servo servo;
MeArm * meArm;
int pos;
bool dir = true;
int baseAngle;
int radialAngle;
int zAngle;
int gripAngle;

void setup() {
//  servo.attach(3);// put your setup code here, to run once:
  meArm = new MeArm(3, 5, 6, 11);
  Serial.begin(115200);
}

void loop() {
  if (pos >= HIGH_ANGLE)dir = false;
  if (pos <= LOW_ANGLE) dir = true;
  Serial.print(pos);
  Serial.print(' ');
  Serial.print(9+((float)pos-90)/20);
  Serial.print(' ');

  if (!dir) meArm->closeGrip();
  else meArm->openGrip();
//  meArm->setAngles(90, 90, 45, 0);
  meArm->goTo(7+(float)(pos-90)/20, 4.0+ (180.0-pos) / 50, 80-pos/2);
  delay(DELAY);
  pos += dir? 1: -1;
}
