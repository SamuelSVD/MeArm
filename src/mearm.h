#ifndef _SV_MeArm_
#define _SV_MeArm_

#define L1   6 //cm
#define L2   8 //cm

#include <Servo.h>

class MeServo: public Servo
{
  private:
    int angleLimit;
    int offset;
    bool direction;
  public:
    MeServo();
    void setLimit(int angleLimit);
    void setOffset(int offset);
    void setDirection(bool direction);
    void write(int pos);
};

class MeArm
{
  private:
    MeServo * base;
    MeServo * radial;
    MeServo * z;
    MeServo * grip;
    int gripAngle;
  public:
    MeArm(int basePin, int radialPin, int zPin, int gripPin);
    void setAngles(int baseAngle, int radialAngle, int zAngle, int gripAngle);
    void setDirections(bool baseDirection, bool radialDirection, bool zDirection, bool gripDirection);
    void setOffsets(int baseOffset, int radialOffset, int zOffset, int gripOffset);
    void goTo(float r, float z, int theta);
    void closeGrip();
    void openGrip();
};

#endif

