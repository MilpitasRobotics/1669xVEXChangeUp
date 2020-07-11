#include "main.h"

//calling the setdrive function created in drive.cpp
void setdrive(int left, int right);

//calling the motorDrive function created in drive.cpp
void motorDrive();

void xDrive();

//calling auton functions created in drive.cpp
void moveForward(double units, int voltage);
void moveBack(double units, int voltage);
void resetEncoders();
int pidturn(int degrees,float speedscale=1);
int drivePIDcontrol(int left, int right, float speedscale=1);
