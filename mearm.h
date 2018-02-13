#ifndef _SV_MeArm_
#define _SV_MeArm_

#define L1   6 //cm
#define L1_2 36
#define L2   8 //cm
#define L2_2 64

#include <Servo.h>

class MyServo: public Servo
{
  private:
    int highLimit;
    int lowLimit;
  public:
    MyServo();
    void setLimits(int lowAngle, int highAngle);
    void write(int pos);
};

class MeArm
{
  private:
    MyServo * base;
    MyServo * radial;
    MyServo * z;
    MyServo * grip;
    int gripAngle;
  public:
    MeArm(int basePin, int radialPin, int zPin, int gripPin);
    void setAngles(int baseAngle, int radialAngle, int zAngle, int gripAngle);
    void goTo(float r, float z, int theta);
    void closeGrip();
    void openGrip();
};

#endif

