/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Brendan                                                   */
/*    Created:      29/10/2024, 16:01:35                                      */
/*    Description:  code                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

competition Competition;


// Initalize things

controller Controller = controller(primary);

brain Brain;

motor Motor1 = motor(1, ratio6_1, false);
motor Motor2 = motor(2, ratio6_1, false);
motor Motor3 = motor(3, ratio6_1, false);

motor_group Left = motor_group(Motor1, Motor2, Motor3);

motor Motor11 = motor(11, ratio6_1, true);
motor Motor12 = motor(12, ratio6_1, true);
motor Motor13 = motor(13, ratio6_1, true);

motor_group Right = motor_group(Motor11, Motor12, Motor13);

// inertial Inertial = inertial(15);


void autonomous(void) {
  Brain.Screen.print("Autonomous");

  Left.setStopping(hold);
  Right.setStopping(hold);

  // auton code to be added

  // Left.spin(forward);
  // Right.spin(forward);
}


double motorSpeed = 0.6;

void toggleMotorSpeed(void) {
  if (motorSpeed == 0.6) {
    Brain.Screen.print("80\% Speed");
    motorSpeed = 0.8;
  } else {
    Brain.Screen.print("60\% Speed");
    motorSpeed = 0.6;
  }
}

void usercontrol(void) {
  Brain.Screen.print("User Control");
  Brain.Screen.print("60\% Speed");

  Left.setStopping(coast);
  Right.setStopping(coast);

  Controller.ButtonR2.pressed(toggleMotorSpeed);

  while (1) {
    double leftright = Controller.Axis3.position() * motorSpeed;
    double updown = Controller.Axis1.position() * motorSpeed;

    Left.spin(forward);
    Right.spin(forward);


    // if (fabs(updown) > 0) {
    //   Left.setVelocity(updown, percent);
    //   Right.setVelocity(updown, percent);
    // } else {
    //   Left.setVelocity(leftright, percent);
    //   Right.setVelocity(leftright, percent);
    // }


    if (fabs(updown) > 0) {
      if (leftright > 0) {
        Left.setVelocity(updown, percent);
        Right.setVelocity(updown - 2*leftright, percent);
      } else {
        Left.setVelocity(updown - 2*leftright, percent);
        Right.setVelocity(updown, percent);
      }
    } else {
      Left.setVelocity(leftright, percent);
      Right.setVelocity(-leftright, percent);
    }


    wait(20, msec);
  }
}


int main() {
  Competition.autonomous(autonomous);
  
  // Competition.drivercontrol(usercontrol);
  usercontrol();

  return 0;
}
