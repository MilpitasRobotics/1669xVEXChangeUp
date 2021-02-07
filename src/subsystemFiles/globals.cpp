#include "main.h"

//motors initialization
pros::Motor leftFront(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightFront(2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftBack(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightBack(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor leftintake(6,pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightintake(11,pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor indexer(10,pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor launcher(9,pros::E_MOTOR_GEARSET_06,false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Imu imu_sensor(13);
pros::ADIEncoder leftEncoder('A','B');
pros::ADIEncoder rightEncoder('C','D');

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
