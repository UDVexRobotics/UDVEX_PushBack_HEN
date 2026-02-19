#include "lemlib/api.hpp" // IWYU pragma: keep
#include "api.h"
#include "lemlib/chassis/trackingWheel.hpp"

#ifndef _UDVEX_CONFIG_H_
#define _UDVEX_CONFIG_H_

#define ROBOT_HEN 0
#define ROBOT_EGG 1
#define AUTON_ENABLED 1
#define SKILL_ENABLED 0

/**
 * Select Robot ID here
 * ROBOT_HEN: Robot 0 (Left Side)
 * ROBOT_EGG: Robot 1 (Right Side)
 */
#define ROBOT_ID ROBOT_EGG

/** Configuartion for Robot 1 (EGG) */
#if ROBOT_ID == ROBOT_EGG
/** Port Mapping */
#define LEFT_MOTOR_PORTS {9, -10, 13, -17} // Numerical Ports for left motors
#define RIGHT_MOTOR_PORTS {-4, 5, 7, -8}   // Numerical Ports for right motors
#define IMU_PORT 19                        // Port for Inertial Measurement Unit
#define INTAKE_MOTOR_PORTS {11, -12, 14, -15, 16} // Ports for intake motors
#define TOP_MOTOR_PORTS                                                        \
  {-2} // Ports for top motor(s) to be used for holding game pieces
#define VERTICAL_TRACKING_WHEEL_PORT 3   // Port for vertical tracking wheel
#define HORIZONTAL_TRACKING_WHEEL_PORT 6 // Port for horizontal tracking wheel

#define LIFT_PISTON_PORT 'A'   // Alphabetical Port for lift piston
#define INTAKE_PISTON_PORT 'B' // Alphabetical Port for intake piston

/** Controls Mapping */
#define OUTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_A
#define INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define INTAKE_REFILL_BUTTON pros::E_CONTROLLER_DIGITAL_R2
#define LIFT_PISTON_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_PISTON_BUTTON pros::E_CONTROLLER_DIGITAL_L2

/** Configuration for Robot 0 (HEN) */
#elif ROBOT_ID == ROBOT_HEN
/** Port Mapping */
#define LEFT_MOTOR_PORTS {9, -10, 12, -13} // Numerical Ports for left motors
#define RIGHT_MOTOR_PORTS {7, -8, -17, 18} // Numerical Ports for right motors
#define IMU_PORT 1                         // Port for Inertial Measurement Unit
#define INTAKE_MOTOR_PORTS {5, 6, 11, 14, -15} // Ports for intake motors
#define TOP_MOTOR_PORTS                                                        \
  {16} // Ports for top motor(s) to be used for holding game pieces
#define VERTICAL_TRACKING_WHEEL_PORT 2   // Port for vertical tracking wheel
#define HORIZONTAL_TRACKING_WHEEL_PORT 4 // Port for horizontal tracking wheel

#define LIFT_PISTON_PORT 'A'   // Alphabetical Port for lift piston
#define INTAKE_PISTON_PORT 'B' // Alphabetical Port for intake piston

/** Controls */
#define OUTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_A
#define INTAKE_REFILL_BUTTON pros::E_CONTROLLER_DIGITAL_R2
#define LIFT_PISTON_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_PISTON_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#endif

/** Constants */
#define MAX_MOTOR_VOLTAGE 127    // Maximum voltage for motors
#define MIN_MOTOR_VOLTAGE -127   // Minimum voltage for motors
#define INTAKE_MOTOR_VOLTAGE MAX_MOTOR_VOLTAGE // Voltage for intake motors

// Initialize Controllers
inline pros::Controller master(pros::E_CONTROLLER_MASTER);
inline pros::Controller partner(pros::E_CONTROLLER_PARTNER);

// Define motors and motor groups here
inline pros::MotorGroup right_motors(RIGHT_MOTOR_PORTS,
                                     pros::MotorGearset::blue);
inline pros::MotorGroup left_motors(LEFT_MOTOR_PORTS, pros::MotorGearset::blue);
inline pros::MotorGroup intake_motors(INTAKE_MOTOR_PORTS,
                                      pros::MotorGearset::blue);
inline pros::MotorGroup top_motors(TOP_MOTOR_PORTS, pros::MotorGearset::blue);

// IMU Sensor
inline pros::Imu imu_sensor(IMU_PORT);

// ADI Port Devices
inline pros::adi::DigitalOut lift_piston(LIFT_PISTON_PORT);
//pros::ADIDigitalOut lift_piston (LIFT_PISTON_PORT);
inline pros::adi::DigitalOut intake_piston(INTAKE_PISTON_PORT);

#if ROBOT_HEN
// Tracking Wheels
inline pros::Rotation vertical_rotation(VERTICAL_TRACKING_WHEEL_PORT);
inline pros::Rotation horizontal_rotation(HORIZONTAL_TRACKING_WHEEL_PORT);
inline lemlib::TrackingWheel
    vertical_tracking_wheel(&vertical_rotation,       // rotation sensor
                            lemlib::Omniwheel::NEW_2, // orientation
                            -2 // distance from the center of the robot (inches)
    );
inline lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizontal_rotation,     // rotation sensor
    lemlib::Omniwheel::NEW_2, // orientation
    -3                        // distance from the center of the robot (inches)
);
#elif ROBOT_EGG
// Tracking Wheels
inline pros::Rotation vertical_rotation(VERTICAL_TRACKING_WHEEL_PORT);
inline pros::Rotation horizontal_rotation(HORIZONTAL_TRACKING_WHEEL_PORT);
inline lemlib::TrackingWheel vertical_tracking_wheel(
    &vertical_rotation,       // rotation sensor
    lemlib::Omniwheel::NEW_2, // orientation
    -2.5                      // distance from the center of the robot (inches)
);
inline lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizontal_rotation,     // rotation sensor
    lemlib::Omniwheel::NEW_2, // orientation
    -3                        // distance from the center of the robot (inches)
);
#endif

// Define sensors
inline lemlib::OdomSensors
    sensors(&vertical_tracking_wheel,   // Vertical tracking wheel 1
            nullptr,                    // Vertical tracking wheel 2
            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
            nullptr,                    // Horizontal tracking wheel 2
            &imu_sensor                 // Inertial sensor
    );

// lemlib::OdomSensors sensors(
//     nullptr, // Vertical tracking wheel 1
//     nullptr, // Vertical tracking wheel 2
//     nullptr, // Horizontal tracking wheel 1
//     nullptr, // Horizontal tracking wheel 2
//     nullptr  // Inertial sensor
// );

// lateral PID controller
// lemlib::ControllerSettings lateral_controller(10,  // proportional gain (kP)
//                                               0,   // integral gain (kI)
//                                               7,   // derivative gain (kD)
//                                               0,   // anti windup
//                                               0,   // small error range, in
//                                               inches 0, // small error range
//                                               timeout, in milliseconds 0, //
//                                               large error range, in inches 0,
//                                               // large error range timeout,
//                                               in milliseconds 0   // maximum
//                                               acceleration (slew)
// );
inline lemlib::ControllerSettings
    lateral_controller(10,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       7,   // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );

// angular PID controller
inline lemlib::ControllerSettings
    angular_controller(2,   // proportional gain (kP)
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
inline lemlib::Drivetrain
    drivetrain(&left_motors,             // left motor group
               &right_motors,            // right motor group
               9,                        // track width (inches)
               lemlib::Omniwheel::NEW_4, // wheel diameter (inches)
               360,                      // drivetrain RPM
               2                         // horizontal drift
    );

// Create the chassis object
inline lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                               lateral_controller, // lateral PID settings
                               angular_controller, // angular PID settings
                               sensors             // odometry sensors
);

#endif // _UDVEX_CONFIG_H_