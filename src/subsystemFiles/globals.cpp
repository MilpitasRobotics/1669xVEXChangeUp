#include "main.h"

//motors initialization
pros::Motor leftFront(4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightFront(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftBack(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightBack(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor leftintake(6,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightintake(7,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Imu imu_sensor(7);
pros::ADIEncoder leftEncoder('A','B');
pros::ADIEncoder rightEncoder('C','D');

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
