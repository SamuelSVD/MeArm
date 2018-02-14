#include <Servo.h>
#include "MeArm.h"
#include <Arduino.h>

MeServo::MeServo()
{
  angleLimit = 180;
  offset = 0;
  direction = true;
}

void MeServo::setLimit(int angleLimit)
{
  this->angleLimit = angleLimit;
}

void MeServo::write(int pos)
{
  if (pos > angleLimit) pos = angleLimit;
  if (direction) pos = offset + pos;
  else           pos = offset - pos;
  if (pos > 180) pos = 180;
  else if (pos < 0) pos = 0;
  this->Servo::write(pos);
}

void MeServo::setOffset(int offset)
{
  this->offset = offset;
}

void MeServo::setDirection(bool direction)
{
  this->direction = direction;
}

MeArm::MeArm(int basePin, int radialPin, int zPin, int gripPin)
{
  base   = new MeServo;
  radial = new MeServo;
  z      = new MeServo;
  grip   = new MeServo;
  base->attach(basePin);
  radial->attach(radialPin);
  radial->setLimit(130);
  radial->setDirection(false);
  z->attach(zPin);
  z->setDirection(false);
  z->setLimit(130);
  grip->attach(gripPin);
  grip->setLimit(145);
}

void MeArm::setAngles(int baseAngle, int radialAngle, int zAngle, int gripAngle)
{
  base  ->write(baseAngle);
  radial->write(radialAngle);
  z     ->write(zAngle);
  grip  ->write(gripAngle);
}

void MeArm::setDirections(bool baseDirection, bool radialDirection, bool zDirection, bool gripDirection) 
{
  base  ->setDirection(baseDirection);
  radial->setDirection(radialDirection);
  z     ->setDirection(zDirection);
  grip  ->setDirection(gripDirection);
}

void MeArm::setOffsets(int baseOffset, int radialOffset, int zOffset, int gripOffset)
{
  base  ->setOffset(baseOffset);
  radial->setOffset(radialOffset);
  z     ->setOffset(zOffset);
  grip  ->setOffset(gripOffset);
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

