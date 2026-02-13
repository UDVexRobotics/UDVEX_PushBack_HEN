#include "main.h"
#include "NYT_Sudoku_Logo.h"
#include "config.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/image/lv_image.h"
#include "macros.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <cstdint>
#include <cstdio>

// extern lemlib::Chassis chassis;
// extern pros::MotorGroup intake_motors;
// extern pros::MotorGroup top_motors;

#define SUDOKU_DISPLAY 0

#if SUDOKU_DISPLAY
// Declare the image (defined in another file)
LV_IMAGE_DECLARE(NYT_Sudoku_Logo);
#endif

// Declare Static Autom Path
// ASSET(TestAUTO_txt);
// ASSET(autom_txt);
// ASSET(automloader_txt);
// ASSET(automlowergoal_txt);
// ASSET(automlowergoaldump_txt);
// ASSET(AutomAction4_txt);
// ASSET(AutomAction5_txt);
#if ROBOT_ID == ROBOT_HEN
#if SKILL_ENABLED
ASSET(AutomAction1_L_txt);
ASSET(AutomAction2_L_txt);
ASSET(AutomAction3_L_txt);
ASSET(AutomAction4_L_txt);
ASSET(AutomAction5_L_txt);
ASSET(AutomAction6_L_txt);
#else
ASSET(MatchAction1_L_txt);
ASSET(MatchAction2_L_txt);
ASSET(MatchAction3_L_txt);
#endif
#else
ASSET(AutomAction1_R_txt);
ASSET(AutomAction2_R_txt);
ASSET(AutomAction3_R_txt);
ASSET(AutomAction4_R_txt);
ASSET(AutomAction5_R_txt);
ASSET(AutomAction6_R_txt);
#endif

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button()
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * @bug causes program to freeze
 * Intention is to print debugging stats to the controller. Need to explore task
 * feasability more later
 */
void controllerTask(void *param) {
  while (true) {
    // Your controller code here
    lemlib::Pose currentPose = chassis.getPose();
    pros::lcd::print(1, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                     currentPose.theta);

    master.clear_line(0);
    master.print(0, 0, "X: %f", currentPose.x);
    master.clear_line(1);
    master.print(1, 0, "Y: %f", currentPose.y);
    master.clear_line(2);
    master.print(2, 0, "T: %f", currentPose.theta);
    pros::delay(250); // Run every 250 ms
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::set_text(2, "UDVEX FTW!");
void initialize() {
  // Initialize the LCD
  pros::lcd::initialize();

  pros::lcd::register_btn1_cb(on_center_button);

  // Initialize the IMU
  imu_sensor.reset();

  // Calibrate the Sensors
  chassis.calibrate();

  // pros::Task controllerTaskHandle(controllerTask);

#if SUDOKU_DISPLAY
  // DISPLAY THE GOAT
  lv_obj_t *img = lv_image_create(lv_screen_active()); // create an image object
  lv_image_set_src(img, &NYT_Sudoku_Logo);             // set the image source
  lv_obj_set_align(
      img, LV_ALIGN_CENTER); // align the image to the center of the screen
#endif
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
#if AUTON_ENABLED

/** Robot 0 (HEN) Auton: Starts on the Left Side */
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#if ROBOT_ID == ROBOT_HEN
  // Set Starting Position
  chassis.setPose(-60.239, 19.683, 90);

#if SKILL_ENABLED
  // Go to ball loader
  chassis.follow(AutomAction1_L_txt, 15, 4000, true, false);

  // Grab the bal--, take the loaa--, just get the objectives out
  macros::intake_entry(true);
  macros::intake_state(macros::INTAKE_HOLD);
  pros::delay(2000); // Ensure they're secured
  macros::intake_entry(false);
  macros::intake_state(macros::INTAKE_OFF);

  // Back up, turn around, then head to center-upper goal
  chassis.follow(AutomAction2_L_txt, 15, 4000, false, false);
  chassis.turnToHeading(135, 3000, {}, false);

  /**
   * @bug The robot ends up fairly misaligned here with the goal.
   * Temporary fix is to manually adjust the robot before hand
   */
  // chassis.moveToPose(chassis.getPose().x - 9, chassis.getPose().y + 9, 135,
  //                    1000, {.forwards = false}, false);
  // chassis.turnToHeading(180, 1000, {}, false);
  // chassis.moveToPose(chassis.getPose().x, chassis.getPose().y - 5, 180, 1000,
  //                    {}, false);
  // chassis.turnToHeading(135, 1000, {}, false);
  // chassis.setPose(-24.85, 24.075, 135);

  // Approach the center-upper goal
  chassis.follow(AutomAction3_L_txt, 15, 2000, true, false);

  // Deposit the balls into the center-upper goal
  macros::intake_state(macros::OUTTAKE);
  pros::delay(250); // try to loosen some potentially jammed balls

  // Deposit fully
  macros::intake_state(macros::INTAKE_ON);
  pros::delay(2000); // Ensure they're all out
  macros::intake_state(macros::INTAKE_OFF);

// Back up, position to the line of pac-man balls
// chassis.follow(AutomAction4_L_txt, 15, 2000, false, false);
// chassis.turnToHeading(90, 3000, {}, false);
// chassis.follow(AutomAction5_L_txt, 15, 3000, true, false);
// chassis.turnToHeading(0, 2000, {}, false);

  // Wacka-wacka-wacka-wacka-wacka (Pick up the balls)
  // macros::intake_state(macros::INTAKE_HOLD);
  // chassis.follow(AutomAction6_L_txt, 15, 4000, true, false);
  // pros::delay(2000); // Ensure they're secured
  // macros::intake_state(macros::INTAKE_OFF);
  // Back up and turn around

#else // MATCH_ENABLED AUTONOMOUS

  // Go to ball loader
  chassis.follow(MatchAction1_L_txt, 5, 4000, true, false);

  // Grab the bal--, take the loaa--, just get the objectives out
  macros::intake_entry(true);
  macros::intake_state(macros::INTAKE_HOLD);
  pros::delay(2000); // Ensure they're secured
  macros::intake_entry(false);
  macros::intake_state(macros::INTAKE_OFF);

  // Back up, and turn around
  chassis.follow(MatchAction2_L_txt, 5, 4000, false, false);
  chassis.turnToHeading(45, 3000, {}, false);

  // Try to spit out the opposing balls
  macros::intake_state(macros::OUTTAKE);
  pros::delay(2000); // Ensure they're all out
  macros::intake_state(macros::INTAKE_OFF);

  // Finish turning towards the upper goal
  chassis.turnToHeading(90, 3000, {}, false);

  // Lift intake and approach upper goal
  macros::intake_lift(true);
  chassis.follow(MatchAction3_L_txt, 5, 4000, true, false);

  // Deposit the balls into the upper goal
  macros::intake_state(macros::OUTTAKE);

  // Deposit fully
  macros::intake_state(macros::INTAKE_ON);
  pros::delay(3000); // Ensure they're all out
  macros::intake_state(macros::INTAKE_OFF);

#endif

/** Robot 1 (EGG) Auton: Starts on the Right Side */
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#else
  // Set Starting Position
  chassis.setPose(-60.239, -18.909, 90);

  // Go to ball loader
  chassis.follow(AutomAction1_R_txt, 5, 5000, true, false);

  // Grab the bal--, take the loaa--, just get the objectives out
  macros::intake_entry(true);
  macros::intake_state(macros::INTAKE_HOLD);
  pros::delay(2000); // Ensure they're secured
  macros::intake_entry(false);
  macros::intake_state(macros::INTAKE_OFF);

#if AUTON_ENABLED
#if SKILL_ENABLED
  // Back up, turn around, then head to center-upper goal
  chassis.follow(AutomAction2_R_txt, 5, 5000, false, false);
  chassis.turnToHeading(45, 3000, {}, false);

  // Approach the center-upper goal
  chassis.follow(AutomAction3_R_txt, 5, 4000, true, false);

  // Deposit the balls into the center-lower goal
  macros::intake_state(macros::OUTTAKE);
  pros::delay(2000); // Ensure they're all out
  macros::intake_state(macros::INTAKE_OFF);

  // chassis.follow(AutomAction4_R_txt, 15, 4000, false, false);
  // chassis.turnToHeading(90, 3000, {}, false);
  // chassis.follow(AutomAction5_R_txt, 15, 5000, true, false);
  // chassis.turnToHeading(180, 3000, {}, false);
  // chassis.follow(AutomAction6_R_txt, 15, 4000, true, false);
#else
#endif
#endif
#endif
#endif

#if 0
  // Set Start position to (0, 0, 0)
  chassis.setPose(0, 0, 0);
  const int timeout_time = 3500;

  chassis.moveToPose(-36, 24, -90, timeout_time, {.forwards = true}, false);
  lemlib::Pose currentPose = chassis.getPose();
  pros::lcd::print(1, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                   currentPose.theta);
  chassis.turnToHeading(-180, timeout_time, {}, false);
  chassis.moveToPose(-36, 0, -180, timeout_time, {.forwards = true}, false);
  currentPose = chassis.getPose();
  pros::lcd::print(2, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                   currentPose.theta);
  chassis.moveToPose(-36, 24, -180, timeout_time, {.forwards = false}, false);
  currentPose = chassis.getPose();
  pros::lcd::print(3, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                   currentPose.theta);
  chassis.turnToHeading(0, timeout_time, {}, false);
  currentPose = chassis.getPose();
  pros::lcd::print(4, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                   currentPose.theta);
  // chassis.moveToPose(-24, 0, -180, timeout_time,
  //                    {.forwards = true, .lead = 0.3});

  // Follow Set path
  // chassis.follow(TestAUTO_txt, 15, 2000);

  chassis.cancelAllMotions();
#endif
#if 0
  // std::cout<<"Heading: "<<chassis.getPose(false).theta<<std::endl;
  // chassis.turnToHeading(180, 4000);
  
  // std::cout<<"Heading: "<<chassis.getPose(false).theta<<std::endl;
  // return;
  
  // Move 48" Forward
  chassis.moveToPoint(0,48,4000);
  pros::delay(3000);
  // Move 48" Backward
  chassis.moveToPoint(0,0,4000,{.forwards=false});
  
  

  // Move 48" Right
  //chassis.turnToHeading(180, 4000);
  chassis.moveToPoint(48,0,4000);
  
  chassis.moveToPose(0, 0, 270, 10000);


  // Move 48" Right
  //chassis.moveToPoint(48,0,10000);
#endif
  return;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1});	// Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({4}); // Creates a motor group with forwards port 5 and reversed ports 4 & 6
void opcontrol() {

  bool lift_state = false;
  bool intake_state = false;

  // Track previous button states for edge detection
  bool last_lift_button = false;
  bool last_intake_button = false;

  int clk = 0;
  while (true) {

    // Gets the Y axis of the left joystick
    int32_t leftY = master.get_analog(ANALOG_LEFT_Y);

    // Gets the X axis of the right joystick
    int32_t rightX = master.get_analog(ANALOG_RIGHT_X);

    lemlib::Pose currentPose = chassis.getPose();
    pros::lcd::print(4, "X: %f, Y: %f, Theta: %f", currentPose.x, currentPose.y,
                     currentPose.theta);

    // Arcade control scheme
    chassis.arcade(leftY, rightX);

    // Intake control
    int32_t buttonOutake = master.get_digital(OUTAKE_BUTTON);
    int32_t buttonIntake = master.get_digital(INTAKE_BUTTON);
    int32_t buttonIntakeHold = master.get_digital(INTAKE_REFILL_BUTTON);
    if (buttonOutake) {
      macros::intake_state(macros::IntakeState::OUTTAKE);
    } else if (buttonIntake) {
      macros::intake_state(macros::IntakeState::INTAKE_ON);
    } else if (buttonIntakeHold) {
      macros::intake_state(macros::IntakeState::INTAKE_HOLD);
    } else {
      macros::intake_state(macros::IntakeState::INTAKE_OFF);
    }

    bool lift_button = master.get_digital(LIFT_PISTON_BUTTON);

    // Rising edge: button just got pressed
    if (lift_button && !last_lift_button) {
      lift_state = !lift_state; // toggle
      lift_piston.set_value(lift_state);
    }
    last_lift_button = lift_button;

    // ---- INTAKE PISTON TOGGLE (use A) ----
    bool intake_button = master.get_digital(INTAKE_PISTON_BUTTON);

    if (intake_button && !last_intake_button) {
      intake_state = !intake_state; // toggle
      // intake_piston.set_value(intake_state);
      macros::intake_entry(intake_state);
    }
    last_intake_button = intake_button;

    pros::delay(20); // Run for 20 ms then update
  }
}