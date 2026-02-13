#include "macros.hpp"
#include "config.hpp"
#include "pros/adi.h"
#include <cstdint>

namespace {
// Constants
constexpr std::int32_t kMaxMotorVoltage =
    INTAKE_MOTOR_VOLTAGE; // Maximum voltage for motors
constexpr std::int32_t kHalfMotorVoltage = kMaxMotorVoltage / 2; // Half voltage

} // anonymous namespace

namespace macros {

// ---- DRIVER MACROS ----

// ---- AUTON MACROS ----
/**
 * @brief Sets the state of the lift piston.
 *
 * @param state True to extend the piston, false to retract.
 *
 * @return True if the operation was successful.
 */
bool intake_lift(bool state) {
  return lift_piston.set_value(state) != PROS_ERR;
}

/**
 * @brief Sets the state of the intake piston.
 *
 * @param state True to close, false to open entry of intake.
 *
 * @return True if the operation was successful.
 */
bool intake_entry(bool state) {
  return intake_piston.set_value(state) != PROS_ERR;
}

/**
 * @brief Sets the state of the intake motors.
 *
 * @param state The desired intake state.
 */
void intake_state(IntakeState state) {
  switch (state) {
  case INTAKE_ON: // Run intake motors forward (Intake game pieces and will spit
                  // from top)
    intake_motors.move(kMaxMotorVoltage);
    top_motors.move(kMaxMotorVoltage);
    break;
  case OUTTAKE: // Reverse intake motors (Spit out game pieces)
    intake_motors.move(-kHalfMotorVoltage);
    top_motors.move(-kHalfMotorVoltage);
    break;
  case INTAKE_OFF: // Stop intake motors
    intake_motors.move(0);
    top_motors.move(0);
    break;
  case INTAKE_HOLD: // Run intake motors. Spin top motors in reverse to hold
                    // game pieces
    intake_motors.move(kMaxMotorVoltage);
    top_motors.move(-kMaxMotorVoltage);
    break;
  default:
    break;
  }
}
} // namespace macros