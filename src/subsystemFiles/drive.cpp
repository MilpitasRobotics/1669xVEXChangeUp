#include "main.h"

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

double avgEncoderVal() {
  return (fabs(leftFront.get_position()) + fabs(leftBack.get_position())
    + fabs(rightFront.get_position()) + fabs(rightBack.get_position())) / 4;
}

//Auton functions

void resetEncoders() {
  leftFront.tare_position();
  leftBack.tare_position();
  rightFront.tare_position();
  rightBack.tare_position();
}

void moveForward(double units, int voltage) {
  //reset encoders
  resetEncoders();
  //drive forward
  while(avgEncoderVal() < units) {
    setdrive(voltage, voltage);
    pros::delay(2);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(-10, -10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
}

void moveBack(double units, int voltage) {
  //reset encoders
  resetEncoders();
  //drive forward
  while(avgEncoderVal() < units) {
    setdrive(-voltage, -voltage);
    pros::delay(2);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(10, 10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
}