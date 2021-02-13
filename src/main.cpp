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
	const int autoCount = 2;
const char* autoNames[autoCount] = {
	"test",
	"2 goal"
};

	pros::lcd::set_text(0, "Select an Auton");
	pros::lcd::print(2, "%s", autoNames[auton]);

	while(1){
		if(choose.get_new_press()) {
			auton++;
		if(auton == autoCount)
			auton = 0;

		pros::lcd::print(2, "%s", autoNames[auton]);
		pros::lcd::print(3, "%d", auton);
	}

	pros::delay(50);
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
	}
}
