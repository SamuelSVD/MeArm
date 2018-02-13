#include <Servo.h>
#include "MeArm.h"
#include <Arduino.h>

MyServo::MyServo()
{
  highLimit = 180;
  lowLimit = 0;
}

void MyServo::setLimits(int lowAngle, int highAngle)
{
  lowLimit = lowAngle;
  highLimit = highAngle;
}

void MyServo::write(int pos)
{
  Serial.print(pos);
  Serial.print(' ');
  if (pos > highLimit) pos = highLimit;
  if (pos < lowLimit)  pos = lowLimit;
  this->Servo::write(pos);
}

MeArm::MeArm(int basePin, int radialPin, int zPin, int gripPin)
{
  base = new MyServo;
  radial = new MyServo;
  z = new MyServo;
  grip = new MyServo;
  base->attach(basePin);
  radial->attach(radialPin);
  radial->setLimits(20, 180);
  z->attach(zPin);
//  z.setLimits(90, 120);
  grip->attach(gripPin);
  grip->setLimits(45, 180);
}

void MeArm::setAngles(int baseAngle, int radialAngle, int zAngle, int gripAngle)
{
  base->write(baseAngle);
  radial->write(135 - radialAngle);
  z->write(95 - zAngle);
  grip->write(gripAngle);
  Serial.println();
}

void MeArm::goTo(float r, float z, int theta)
{
  Serial.print(r);
  Serial.print(' ');
  Serial.print(z);
  Serial.print(' ');
  Serial.print(theta);
  Serial.print(':');
  float p = sqrt(r*r+z*z);
  float beta = acos((L1*L1 + L2*L2 - p*p) /(2 * L1 * L2));
  float alpha = atan2(z, r);
  float psi = acos((p*p + L1*L1 - L2*L2)/(2 * L1 * p));
  float theta1 = alpha + psi;
  float theta2 = PI-theta1-beta;
  setAngles(theta, (int)degrees(theta1), (int)degrees(theta2), gripAngle);
}

void MeArm::closeGrip()
{
  gripAngle = 180;
  grip->write(gripAngle);
}

void MeArm::openGrip()
{
  gripAngle = 45;
  grip->write(gripAngle);
}

