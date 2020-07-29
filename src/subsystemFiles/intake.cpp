#include "main.h"
void intakecontroller(){
  if(controller.get_digital(DIGITAL_L1)){
    leftintake.move_velocity(200);
    rightintake.move_velocity(200);
    indexer.move_velocity(200);
  }else if(controller.get_digital(DIGITAL_L2)){
    leftintake.move_velocity(-200);
    rightintake.move_velocity(-200);
    indexer.move_velocity(-200);
  }else{
    leftintake.move_velocity(0);
    rightintake.move_velocity(0);
    indexer.move_velocity(0);
  }
}
