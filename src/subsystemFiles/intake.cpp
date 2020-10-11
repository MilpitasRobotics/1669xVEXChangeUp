#include "main.h"

/**
 * L1 is pressed for intaking. L1 and X is pressed for outtaking
 * X is the shift key
*/

void intakecontroller(){
  if(controller.get_digital(DIGITAL_L1)){
    rightintake.move_velocity(200);
    leftintake.move_velocity(200);
  }else if(controller.get_digital(DIGITAL_L1) && controller.get_digital(DIGITAL_X)){
    leftintake.move_velocity(-200);
    rightintake.move_velocity(-200);
  }else{
    leftintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftintake.move_velocity(0);
    rightintake.move_velocity(0);
  }
}
