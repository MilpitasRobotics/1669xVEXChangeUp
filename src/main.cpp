#include "main.h"
#include <iostream>
#include <string.h>

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
	setdrive(0,0);
	pidturn(90, 50);
}

void opcontrol() {
	//opcontrol() function code
	pros::lcd::initialize();
	while (true) {
		//Returns Heading and Rotation values from imu_sensor
		pros::lcd::print(1, "heading value: %f\n", imu_sensor.get_heading());
		pros::lcd::print(2, "rotation value: %f\n", imu_sensor.get_rotation());
		//setting up motor temp display
		std::ostringstream var;
		oss << "LF:" << leftFront.get_temperature() << " RF:" << rightFront.get_temperature() << " LB:" << leftBack.get_temperature() << " RB:" << rightBack.get_temperature();
		std::string combinedtemps = oss.str();
		pros::lcd::print(3, "Temperatures: LF: %f\n", combinedtemps)
		//Runs drive
		xDrive();
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
