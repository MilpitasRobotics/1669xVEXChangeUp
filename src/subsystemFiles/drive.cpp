#include "main.h"
using namespace okapi;

//function to set values to the motors
void setdrive(int left, int right) {
  leftFront = left;
  rightFront = -right;
  leftBack = -left;
  rightBack = right;
}

void motorDrive() {
  //arcade control
  int power = controller.get_analog(ANALOG_LEFT_Y);
  int turn = controller.get_analog(ANALOG_RIGHT_X);
  int left = power + turn;
  int right = power - turn;
  setdrive(left, right);
}

//Auton functions
auto chassis = ChassisControllerFactory::create(leftFront, rightFront, leftBack, rightBack);
void moveForward() {
  leftFront.move_absolute(1000, 200);
  leftBack.move_absolute(-1000, 200);
  rightFront.move_absolute(-1000, 200);
  rightBack.move_absolute(1000, 200);
}

void moveBack() {
  leftFront.move_absolute(-1000, 200);
  leftBack.move_absolute(1000, 200);
  rightFront.move_absolute(1000, 200);
  rightBack.move_absolute(-1000, 200);
}