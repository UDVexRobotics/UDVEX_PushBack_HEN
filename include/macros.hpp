#ifndef MACROS_HPP
#define MACROS_HPP

#include "config.hpp"
namespace macros {
enum IntakeState {
  INTAKE_PISTON_UP = false,
  INTAKE_PISTON_DOWN = true,
  INTAKE_HOLD,
  INTAKE_ON,
  OUTTAKE,
  INTAKE_OFF
};

bool intake_lift(bool state);
bool intake_entry(bool state);
void intake_state(IntakeState state);
} // namespace macros
#endif // MACROS_HPP