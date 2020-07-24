#include "main.h"
void intakecontroller(){
  if(controller.get_digital(DIGITAL_L1)){
    leftintake.move_velocity(200);
  }else if(controller.get_digital(DIGITAL_L2)){
    leftintake.move_velocity(-200);
  }else{
    leftintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
  if(controller.get_digital(DIGITAL_R1)){
    rightintake.move_velocity(200);
  }else if(controller.get_digital(DIGITAL_R2)){
    rightintake.move_velocity(-200);
  }else{
    rightintake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}
