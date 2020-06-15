#include "main.h"


void initialize() {
	//initialize() function code
	pros::lcd::initialize();
	//print velocity of motors of the drivetrain to Brain
  	pros::lcd::set_text(1, __STRING(_LONG_DOUBLE(leftFront.get_actual_velocity())));
  	pros::lcd::set_text(2, __STRING(_LONG_DOUBLE(leftBack.get_actual_velocity())));
  	pros::lcd::set_text(3, __STRING(_LONG_DOUBLE(rightFront.get_actual_velocity())));
  	pros::lcd::set_text(4, __STRING(_LONG_DOUBLE(rightBack.get_actual_velocity())));

}

void disabled() {
	//disabled() function code
}

//autonomous function code
void autonomous() {
	moveForward();
	moveBack();
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
