#include "main.h"

//calling the setdrive function created in drive.cpp
void setdrive(int left, int right);

//calling the motorDrive function created in drive.cpp
void motorDrive();

//calling auton functions created in drive.cpp
void moveForward(double units, int voltage);
void moveBack(double units, int voltage);
void resetEncoders();
void turn(double degrees, int voltage);