#include "main.h"
void launchercontroller() {
  if(controller.get_digital(DIGITAL_R1)){
    launcher.move_velocity(600);
  }else if(controller.get_digital(DIGITAL_R2)){
    launcher.move_velocity(-600);
  }else{
    launcher.move_velocity(0);
  }
}
