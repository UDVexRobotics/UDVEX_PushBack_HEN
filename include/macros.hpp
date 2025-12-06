#ifndef MACROS_HPP
#define MACROS_HPP

#include "config.hpp"

enum IntakeState {
  INTAKE_PISTON_UP = false,
  INTAKE_PISTON_DOWN = true,
  INTAKE_HOLD,
  INTAKE_ON,
  INTAKE_REVERSE,
  INTAKE_OFF
};

bool intake_lift(bool state);
void intake_state(IntakeState state);

#endif // MACROS_HPP