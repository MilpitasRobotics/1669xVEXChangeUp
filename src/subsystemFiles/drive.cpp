#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;
using namespace okapi::literals;

//function to set values to the motors
void setdrive(int left, int right) {
  leftFront = -left;
  rightFront = right;
  leftBack = left;
  rightBack = -right;
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
  leftFront = power + strafe + turn;
  rightFront = strafe - power + turn;
  leftBack = power - strafe + turn;
  rightBack = turn - power - strafe;
}

//Returns average encoder values from the 4 drive motors
double avgEncoderVal() {
  return (fabs(leftFront.get_position()) + fabs(leftBack.get_position())
    + fabs(rightFront.get_position()) + fabs(rightBack.get_position())) / 4;
}

//Auton functions

//self explanitory
void resetEncoders() {
  leftFront.tare_position();
  leftBack.tare_position();
  rightFront.tare_position();
  rightBack.tare_position();
}

void moveForward(double units, int voltage) {
  //captures initial heading
  double tempheading = imu_sensor.get_heading();
  //drive forward until it has has the desired value
  while(avgEncoderVal() < units) {
    //powering motors and using initial heading values to stay moving in a straight line
    setdrive(voltage+tempheading, voltage-tempheading);
    pros::delay(2);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(-10, -10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
}

void moveBack(double units, int voltage) {
  //captures inital heading
  double tempheading = imu_sensor.get_heading();
  //drive backward until it has past the desired value
  while(avgEncoderVal() > units) {
    //powering motors and using initial heading values to stay moving in a straight line
    setdrive(-voltage+tempheading, -voltage-tempheading);
    pros::delay(20);
  }
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(10, 10);
  pros::delay(50);
  //set drive to 0 so that once the delay is over, it doesn't move
  setdrive(0, 0);
}
//old turn code based off an online tutorial on gyro turning
/*
void turn(int degrees, int voltage) {
  //identify direction
  int direction = abs(degrees)/degrees;
  //reset encoders and inertial sensor
  imu_sensor.reset();
  resetEncoders();

  //turn a certain amount of degrees
  setdrive(voltage*direction, -voltage*direction);
  while(fabs(imu_sensor.get_heading()) < abs(degrees)-50) {
    pros::delay(20);
  }
  //delay to lose momentum
  pros::delay(100);
  //if overshoot, turn a little back
  if(fabs(imu_sensor.get_heading()) > abs(degrees)) {
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
*/

int drivePIDcontrol(int left, int right, float speedscale = 1){
  float targetLeft = leftEncoder.get_value()+left;
  float targetRight = rightEncoder.get_value()+right;
  float errorLeft = targetLeft-leftEncoder.get_value();
  float errorRight = targetRight-rightEncoder.get_value();
  float voltLeft;
  float voltRight;
  int signLeft;
  int signRight;
  float kp = 0.25;
  while(errorLeft>1 || errorRight>1){
    errorLeft = targetLeft-leftEncoder.get_value();
    errorRight = targetRight-rightEncoder.get_value();
    signLeft = (errorLeft/fabs(errorLeft));
    signRight = (errorRight/fabs(errorRight));
    voltLeft = kp*errorLeft*speedscale;
    voltRight = kp*errorRight*speedscale;
    if(errorLeft*kp*speedscale>115){
      voltLeft = signLeft*110;
    }
    if(errorRight*kp*speedscale>115){
      voltRight = signRight*110;
    }
    setdrive(voltLeft,voltRight);
  }
  setdrive(0,0);
  return 0;
}

int pidturn(int degrees,float speedscale = 1) {
  float kp = 0.25;
  float target = imu_sensor.get_heading()+degrees;
  float error = target-imu_sensor.get_heading();
  int sign;
  float voltage;
  while(error>1){
    error = target-imu_sensor.get_heading();
    sign = (error/fabs(error));
    voltage = error*kp*speedscale;
    if(voltage>115){
      voltage = 115;
    }
    setdrive(-voltage,voltage);
    pros::delay(5);
  }
  setdrive(0,0);
  return 0;
}
