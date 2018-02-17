#include "MeArm.h"
#include <Servo.h>
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
  radial->setOffset(180);
  radial->setLimit(130);
  radial->setDirection(false);
  z->attach(zPin);
  z->setOffset(180);
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

SerialMeArm::SerialMeArm(int basePin, int radialPin, int zPin, int gripPin) : MeArm(basePin, radialPin, zPin, gripPin){}

//Expecting a message in the format of:
//MAAABB.BCC.CD
int SerialMeArm::handleMessage(String message)
{
  if (message.length() != 13) return BAD_MESSAGE_LENGTH;
  if (message.charAt(0) != 'M') return BAD_MESSAGE_ID;
  int baseAngle = strtol(message.substring(1,4).c_str(), NULL, 10);
  float radial  = strtol(message.substring(4, 6).c_str(), NULL, 10) + strtol(message.substring(7,8).c_str(), NULL, 10)/10.0;
  float z       = strtol(message.substring(8, 10).c_str(), NULL, 10) + strtol(message.substring(11,12).c_str(), NULL, 10)/10.0;
  bool grip = (message.charAt(12) == '1');
  goTo(radial, z, baseAngle);
  if (grip) closeGrip();
  else      openGrip();
  return GOOD_MESSAGE;
}
