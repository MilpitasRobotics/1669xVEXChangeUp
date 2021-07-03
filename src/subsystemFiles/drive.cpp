#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;
using namespace okapi::literals;

//function to set values to the motors
void setdrive(int left, int right) {
  leftFront = left;
  rightFront = right;
  leftBack = left;
  rightBack = right;
}

double encoderConvert( int inches ) {
  double circumference = 4*pi;
  double total_inches = 360*inches;
  double clicks = total_inches / circumference;
  return (clicks*7)/3;
}

void motorDrive() {
  //arcade control
  int power = controller.get_analog(ANALOG_LEFT_Y);
  int turn = controller.get_analog(ANALOG_RIGHT_X);
  int left = power + turn;
  int right = power - turn;
  setdrive(left, right);
  intakecontroller();
  launchercontroller();
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
  
  //brake (give setdrive() function a small negative value to slowly break)
  setdrive(-10, -10);
  pros::delay(100);
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
  pros::delay(100);
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

void moveForward1(double units, int speed) {
  int direction = fabs(units)/units;
  resetEncoders();
  while (fabs(avgEncoderVal()) < fabs(units))
  {
    setdrive(speed*direction, -speed*direction);
    pros::delay(10);
  }

  setdrive(-10, -10);
  pros::delay(50);
  setdrive(0, 0);
  
}

int drivePIDcontrol(float left, float right, float speedscale){
  float leftFrontpos = -leftFront.get_position();
  float rightFrontpos = rightFront.get_position();
  float targetLeft = leftFrontpos+left;
  float targetRight = rightFrontpos+right;
  float errorLeft = targetLeft-leftFrontpos;
  float errorRight = targetRight-rightFrontpos;
  float voltLeft;
  float voltRight;
  int signLeft;
  int signRight;
  float kp = 0.1;
  while(abs(errorLeft)>5 || abs(errorRight)>5){
    pros::lcd::print(7, "leftFront: %f\n", leftFront.get_position());
    leftFrontpos = -leftFront.get_position();
    rightFrontpos = rightFront.get_position();
    errorLeft = targetLeft-leftFrontpos;
    errorRight = targetRight-rightFrontpos;
    signLeft = (errorLeft/fabs(errorLeft));
    signRight = (errorRight/fabs(errorRight));
    voltLeft = kp*errorLeft*speedscale;
    voltRight = kp*errorRight*speedscale;
    if(errorLeft*kp*speedscale>115){
      voltLeft = signLeft*110;
    }else if(errorLeft*kp*speedscale<10){
      voltLeft = signLeft*10;
    }
    if(errorRight*kp*speedscale>115){
      voltRight = signRight*110;
    }else if(errorRight*kp*speedscale<10){
      voltRight = signRight*10;
    }
    setdrive(voltLeft,voltRight);
    pros::delay(5);
  }
  setdrive(-10,-10);
  pros::delay(100);
  setdrive(0,0);
  return 0;
}

int pidturn(int degrees,float speedscale = 1) {
  float kp = 0.15;
  float target = imu_sensor.get_heading()+degrees;
  float error = target-imu_sensor.get_heading();
  int sign; 
  float voltage;
  while(fabs(error)>3){
    pros::lcd::print(1, "heading value: %f\n", imu_sensor.get_heading());
  	pros::lcd::print(2, "rotation value: %f\n", imu_sensor.get_rotation());
    error = target-imu_sensor.get_heading();
    sign = (error/fabs(error));
    voltage = error*kp*speedscale;
    if(voltage>115){
      voltage = 115;
    }else if(voltage<15){
      voltage = 15;
    }
    setdrive(-voltage,voltage);
    pros::delay(5);
  }
  setdrive(0,0);
  return 0;
}
void gyroPid (double angle) {

  double target;
  
  if(angle <= 0.0) {
    target = 1.5;
  }
  
  else {
    target = 0.7;
  }

  // variable instantiations
  double error = angle - imu_sensor.get_rotation();
  double integral;
  double derivative;
  double prevError;
  double kp = 0.98;
  double ki = 0.001;
  double kd = 5.5;

  while(fabs(error) > target) {
    error = angle - imu_sensor.get_rotation();
    integral  = integral + error;
    if(error == 0 || fabs(error) >= angle) {
      integral = 0;
    }
  
    derivative = error - prevError;
    prevError = error;
    double p = error * kp;
    double i = integral * ki;
    double d = derivative * kd;

    double vel = p + i + d;

    leftFront.move_velocity(-vel);
    rightFront.move_velocity(vel);
    leftBack.move_velocity(vel);
    rightBack.move_velocity(-vel);

    pros::delay(20);
  }
}

void cyclingMacro(int velocity) {
  setintake(velocity);
  indexer.move_velocity(velocity);
  launcher.move_velocity(velocity);
  pros::delay(1000);
  launcher.move_velocity(0);
  indexer.move_velocity(0);
  setintake(0);
}
