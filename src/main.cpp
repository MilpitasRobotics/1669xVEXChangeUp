#include "main.h"
#include <iostream>
#include <string.h>

void initialize() {
	//initialize() function code
	pros::lcd::initialize();
	leftFront.set_encoder_units(MOTOR_ENCODER_COUNTS);
	leftBack.set_encoder_units(MOTOR_ENCODER_COUNTS);
	rightFront.set_encoder_units(MOTOR_ENCODER_COUNTS);
	rightBack.set_encoder_units(MOTOR_ENCODER_COUNTS);
	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	imu_sensor.reset();
	pros::lcd::initialize();
	setdrive(0,0);
	resetEncoders();
	pros::delay(2100);
}

void disabled() {
	//disabled() function code
}

//autonomous function code
void autonomous() {
	//moveForward(1000.0, 100);
	//moveBack(1000.0, 100);
	pros::lcd::print(1, "heading value: %f\n", imu_sensor.get_heading());
	pros::lcd::print(2, "rotation value: %f\n", imu_sensor.get_rotation());
	pros::lcd::print(3, "atrget: %f\n", leftFront.get_position()+encoderConvert(30));
	pros::lcd::print(4, "t:%f\n", imu_sensor.get_heading()+90);
	pros::lcd::print(7, "leftFront: %f\n", leftFront.get_position());
	setintake(-600);
	//pros::delay(500);
	setintake(0);
	moveForward1(encoderConvert(30), 100);
	//drivePIDcontrol(encoderConvert(23), encoderConvert(23), 0.4);
	//pros::delay(20);
	// pidturn(90, 0.6);
	pros::lcd::print(5, "done\n");
	// drivePIDcontrol(500,500,1);
	// pidturn(90,1);
	// drivePIDcontrol(500,500,1);
	// pidturn(90,1);
	// drivePIDcontrol(500,500,1);
	// pidturn(90,1);
	// drivePIDcontrol(500,500,1);
	// pidturn(90,1);
}

void opcontrol() {
	//opcontrol() function code
	pros::lcd::initialize();
	while (true) {
		//Returns Heading and Rotation values from imu_sensor
		pros::lcd::print(1, "heading value: %f\n", imu_sensor.get_heading());
		pros::lcd::print(2, "rotation value: %f\n", imu_sensor.get_rotation());
		pros::lcd::print(3, "leftFront: %f\n", leftFront.get_position());
		//setting up motor temp display
		//std::string combinedtemps = std::string("LF:") + std::to_string(leftFront.get_temperature()) + std::string(" RF:") + std::to_string(rightFront.get_temperature()) + std::string(" LB:") + std::to_string(leftBack.get_temperature()) + std::string(" RB:") + std::to_string(rightBack.get_temperature());
		//pros::lcd::print(3, "Temperatures: LF: %f\n", combinedtemps);
		//Runs drive
		motorDrive();
		launchercontroller();
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
