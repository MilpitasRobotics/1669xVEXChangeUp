#include "main.h"
#include <iostream>
#include <string.h>
using namespace okapi;
int auton = 0;
void initialize() {
	pros::delay(200);
	//initialize() function code
	pros::lcd::initialize();
}
void competition_initialize(){
	pros::delay(200);
	//initialize() function code
	pros::lcd::initialize();
	const char* autonNames[] = {
		"2 Goal Left",//this one is regular
		"1 Goal Left",
		"2 Goal Right",
		"1 Goal Right",
		"turn testing",//this one prints joe
	};
	while(true){
		pros::lcd::print(1, "current auton: %s\n", autonNames[auton]);
		pros::lcd::print(3, "press switch to go next\n");
		pros::lcd::print(4, "%d\n", auton);
		if(lswitch.get_new_press()){
			auton += 1;
			if(auton==sizeof(autonNames))
				auton = 0;
		}
		pros::delay(5);
	}
}
void disabled() {
	//disabled() function code
}
//autonomous function code
void autonomous() {
	autonhandler(auton);
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
		//cycle(600);
	}
}
