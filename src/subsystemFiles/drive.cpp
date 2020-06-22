#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;
using namespace okapi::literals;

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

void xDrive() {
  int power = controller.get_analog(ANALOG_LEFT_Y);
  int turn = controller.get_analog(ANALOG_RIGHT_X);
  int strafe = controller.get_analog(ANALOG_LEFT_X);
  leftFront = power - strafe + turn;
  rightFront = power - strafe + turn;
  leftBack = power + strafe - turn;
  rightBack = power + strafe - turn; 
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
  //reset encoders and inertial sensor
  resetEncoders();
  imu_sensor.reset();
  //drive forward
  while(avgEncoderVal() < units) {
    setdrive(voltage+imu_sensor.get_heading(), voltage-imu_sensor.get_heading());
    pros::delay(2);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(-10, -10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
}

void moveBack(double units, int voltage) {
  //reset encoders and inertial sensor
  resetEncoders();
  imu_sensor.reset();
  //drive forward
  while(avgEncoderVal() < units) {
    setdrive(-voltage+imu_sensor.get_heading(), -voltage-imu_sensor.get_heading());
    pros::delay(20);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(10, 10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
  
}

void turn(int degrees, int voltage) {
  //identify direction
  int direction = abs(degrees)/degrees;
  //reset encoders and inertial sensor
  imu_sensor.reset();
  resetEncoders();

  //turn a certain amount of degrees
  setdrive(voltage*direction, -voltage*direction);
  while(fabs(imu_sensor.get_heading()) < abs(degrees*10)-50) {
    pros::delay(20);
  }
  //delay to lose momentum
  pros::delay(100);
  //if overshoot, turn a little back
  if(fabs(imu_sensor.get_heading()*10) > abs(degrees)*10) {
    setdrive(0.5*(-voltage)*direction, 0.5*voltage*direction);
    while(fabs(imu_sensor.get_heading()) > abs(degrees)) {
      pros::delay(20); 
    }
  }
  //if undershoot, turn more until reached desired degrees of rotation
  else if(fabs(imu_sensor.get_heading()) < abs(degrees)) {
    setdrive(0.5*voltage*direction, 0.5*(-voltage)*direction);
    while(fabs(imu_sensor.get_heading()) > abs(degrees)) {
      pros::delay(20); 
    }
  }

  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0,0);

}