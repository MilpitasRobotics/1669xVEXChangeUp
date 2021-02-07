#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;
using namespace okapi::literals;
void setintake(int vel) {
  leftintake = -vel;
  rightintake = vel;
}

void intakecontroller(){
  if(controller.get_digital(DIGITAL_L1)){
    setintake(600);
    indexer.move_velocity(600);
  }else if(controller.get_digital(DIGITAL_L2)){
    setintake(-600);
    indexer.move_velocity(-600);
  }else{
    setintake(0);
    indexer.move_velocity(0);
  }
}
