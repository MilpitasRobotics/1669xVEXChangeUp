#include "main.h"

//calling the setdrive function created in drive.cpp
void setdrive(double left, double right);

//calling the motorDrive function created in drive.cpp
void motorDrive();

void xDrive();
void intake(int left, int right);
double encoderConvert(int inches);
void outtake(int units, int speed);
void gyroPid (double angle);
//calling auton functions created in drive.cpp
void moveForward(double units, int voltage);
void moveBack(double units, int voltage);
void resetEncoders();
int pidturn(int degrees,float speedscale);
int drivePIDcontrol(float left, float right, float speedscale);
void intakecontroller();
void moveForward1(double units, int speed);
void cyclingMacro(int velocity);