#include "macros.hpp"

extern pros::adi::DigitalOut intake_piston;
extern pros::MotorGroup intake_motors;
extern pros::MotorGroup top_motors;

// ---- DRIVER MACROS ----

// ---- AUTON MACROS ----

bool intake_lift(bool state) { return intake_piston.set_value(state); }

void intake_state(IntakeState state) {
  switch (state) {
  case INTAKE_ON: // Run intake motors forward (Intake game pieces and will spit
                  // from top)
    intake_motors.move(127);
    top_motors.move(127);
    break;
  case INTAKE_REVERSE: // Reverse intake motors (Spit out game pieces)
    intake_motors.move(-127);
    top_motors.move(-127);
    break;
  case INTAKE_OFF: // Stop intake motors
    intake_motors.move(0);
    top_motors.move(0);
    break;
  case INTAKE_HOLD: // Run intake motors. Spin top motors in reverse to hold
                    // game pieces
    intake_motors.move(127);
    top_motors.move(-127);
    break;
  default:
    break;
  }
}