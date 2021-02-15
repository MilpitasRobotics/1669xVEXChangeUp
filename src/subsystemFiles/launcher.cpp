#include "main.h"

void setIndexer(int velocity) {
  indexer = velocity;
}
void launchercontroller() {
  if(controller.get_digital(DIGITAL_R1) && controller.get_digital(DIGITAL_R2)){
    setIndexer(600);
    launcher = 600;
    //pros::delay(10);

  }else if(controller.get_digital(DIGITAL_R2)){
    launcher.move_velocity(-600);
  } else if(controller.get_digital(DIGITAL_R1)) {
    launcher.move_velocity(600);
  }
  else{
    launcher.move_velocity(0);
  }
}

void cycle(int velocity) {
  if(controller.get_digital(DIGITAL_R1) && controller.get_digital(DIGITAL_R2)) {
    launcher.move_velocity(velocity);
    indexer.move_velocity(velocity);
  } else {
    //do nothing
  }
}
