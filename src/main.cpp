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
#include "pros/rtos.hpp"
#include <cstdio>

extern lemlib::Chassis chassis;
extern pros::MotorGroup intake_motors;

// Declare the image (defined in another file)
LV_IMAGE_DECLARE(NYT_Sudoku_Logo);

// Declare Static Autom Path
ASSET(test_path_txt);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button()
{
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
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::set_text(2, "UDVEX FTW!");
	pros::lcd::set_text(3, "varsha");
void initialize() {
  // Initialize the LCD
  // pros::lcd::initialize();
  // pros::lcd::set_text(1, "Hello PROS User!");
  // pros::lcd::set_text(2, "UDVEX FTW!");

  // pros::lcd::register_btn1_cb(on_center_button);

  // DISPLAY THE GOAT
  lv_obj_t *img = lv_image_create(lv_screen_active()); // create an image object
  lv_image_set_src(img, &NYT_Sudoku_Logo);             // set the image source
  lv_obj_set_align(
      img, LV_ALIGN_CENTER); // align the image to the center of the screen

  // Calibrate the Sensors
  chassis.calibrate();
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
  
  // Follow Set path
  chassis.follow(test_path_txt, 15, 2000);
  
  // Set Start position to (0, 0, 0)
  chassis.setPose(0, 0, 0);
  // std::cout<<"Heading: "<<chassis.getPose(false).theta<<std::endl;
  // chassis.turnToHeading(180, 4000);
  
  // std::cout<<"Heading: "<<chassis.getPose(false).theta<<std::endl;
  // return;
  
  // Move 48" Forward
  chassis.moveToPoint(0,48,4000);
  pros::delay(3000);
  // Move 48" Backward
  chassis.moveToPoint(0,0,4000,{.forwards=false});
  
  
  return;
  // Move 48" Right
  //chassis.turnToHeading(180, 4000);
  chassis.moveToPoint(48,0,4000);
  
  lemlib::Pose currentPose = chassis.getPose();
  printf("X: %f, Y: %f, Theta: %f\n", currentPose.x, currentPose.y, currentPose.theta);

  chassis.moveToPose(0, 48, 270, 10000);


  // Move 48" Right
  //chassis.moveToPoint(48,0,10000);
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
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1});	// Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({4}); // Creates a motor group with forwards port 5 and reversed ports 4 & 6
void opcontrol() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  while (true) {
    pros::lcd::print(0, "%d %d %d",
                     (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                     (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                     (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >>
                         0); // Prints status of the emulated screen LCDs
                             // Gets the Y axis of the left joystick
    int32_t leftY = master.get_analog(ANALOG_LEFT_Y);

    // Gets the X axis of the right joystick
    int32_t rightX = master.get_analog(ANALOG_LEFT_X);

    // Arcade control scheme
    chassis.arcade(leftY, rightX);

    // Intake control
    int32_t intake_motors_control = master.get_analog(ANALOG_RIGHT_Y);
    intake_motors.move(intake_motors_control);

    pros::delay(20); // Run for 20 ms then update
  }
}