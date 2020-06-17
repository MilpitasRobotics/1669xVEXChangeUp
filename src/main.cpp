#include "main.h"


void initialize() {
	//initialize() function code
	pros::lcd::initialize();
	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	imu_sensor.reset();
}

void disabled() {
	//disabled() function code
}

//autonomous function code
void autonomous() {
	//moveForward(1000.0, 100);
	//moveBack(1000.0, 100);
	turn(90, 50);
	
}

void opcontrol() {
	//opcontrol() function code
	while (true) {
		motorDrive();
		pros::delay(2);
	}
}

void competition_initialize() {
	//competition_initialize() function code
	//consists of auton and driver control functions 
	//meant to be kept in order of the game (auton period then driver period)
	autonomous();
	opcontrol();
	while(1) {
		pros::delay(1);
	}
}