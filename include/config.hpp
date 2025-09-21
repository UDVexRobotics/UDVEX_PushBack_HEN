#include "lemlib/api.hpp" // IWYU pragma: keep
#include "api.h"

#ifndef _UDVEX_CONFIG_H_
#define _UDVEX_CONFIG_H_

// Define motors and motor groups here
pros::MotorGroup right_motors({19}, pros::MotorGearset::blue);
pros::MotorGroup left_motors({-18}, pros::MotorGearset::blue);
pros::MotorGroup intake_motors({1, 2, -10, 11, -12}, pros::MotorGearset::blue);

// Define sensors
lemlib::OdomSensors sensors(
    nullptr, // Vertical tracking wheel 1
    nullptr, // Vertical tracking wheel 2
    nullptr, // Horizontal tracking wheel 1
    nullptr, // Horizontal tracking wheel 2
    nullptr  // Inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10,  // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              3,   // derivative gain (kD)
                                              3,   // anti windup
                                              1,   // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3,   // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20   // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2,   // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              10,  // derivative gain (kD)
                                              3,   // anti windup
                                              1,   // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3,   // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0    // maximum acceleration (slew)
);

// Create the drivetrain object
lemlib::Drivetrain drivetrain(&left_motors,             // left motor group
                              &right_motors,            // right motor group
                              9,                        // track width (inches)
                              lemlib::Omniwheel::NEW_4, // wheel diameter (inches)
                              360,                      // drivetrain RPM
                              2                         // horizontal drift
);

// Create the chassis object
lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors             // odometry sensors
);

#endif // _UDVEX_CONFIG_H_