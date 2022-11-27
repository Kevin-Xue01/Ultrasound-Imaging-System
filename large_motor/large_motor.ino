#include <AccelStepper.h>
#define FULLSTEP 4
// User variables
int x_motor_travel_percentage = 90; // percentage of x axis travel 
int x_motor_pixel_percentage = 1; // percentage of x_motor_total steps for 1 pixel
int y_motor_travel_percentage = 90; // percentage of x axis travel 
int y_motor_pixel_percentage = 1; // percentage of y_motor_total steps for 1 pixel
// System variables

// x motor
int x_motor_pulse_pin = 8;
int x_motor_dir_pin = 9;

int x_motor_steps_per_revolution = 200; // check the switches on the controller

int x_motor_max_speed = 2000; // this we need to figure out, steps / second

int x_motor_max_revolutions = 17; // found by manually rotating x axis lead screw

int x_motor_total_steps = (int)(((float)x_motor_travel_percentage / 100) * 
  (float)x_motor_steps_per_revolution * (float)x_motor_max_revolutions);
int x_motor_steps_per_pixel = (int)((float) x_motor_pixel_percentage / 100 * (float)x_motor_total_steps);
int x_motor_total_pixels = (int)((1 / (float) x_motor_steps_per_pixel) * (float) x_motor_total_steps);
int x_motor_total_steps = x_motor_steps_per_pixel * x_motor_total_pixels;

// y motor
int y_motor_IN_1_pin = 4;
int y_motor_IN_2_pin = 5;
int y_motor_IN_3_pin = 6;
int y_motor_IN_4_pin = 7;

int y_motor_steps_per_revolution = 2038; // datasheet

int y_motor_max_speed = 15; // rpm

int y_motor_max_revolutions = 23; // found by manually rotating y axis lead screw

int y_motor_total_steps = (int)(((float)y_motor_travel_percentage / 100) * 
  (float)y_motor_steps_per_revolution * (float)y_motor_max_revolutions);
int y_motor_steps_per_pixel = (int)((float) y_motor_pixel_percentage / 100 * (float)y_motor_total_steps);
int y_motor_total_pixels = (int)((1 / (float) y_motor_steps_per_pixel) * (float) y_motor_total_steps);
int y_motor_total_steps = y_motor_steps_per_pixel * y_motor_total_pixels;

// Motor objects
AccelStepper x_motor(1, x_motor_pulse_pin, x_motor_dir_pin);
AccelStepper y_motor(FULLSTEP, y_motor_IN_1_pin, y_motor_IN_3_pin, y_motor_IN_2_pin, y_motor_IN_4_pin);

void step(bool ax, bool dir) {
  if (dir) {
    if (ax) {
      y_motor.moveTo(y_motor.currentPosition() - y_motor_steps_per_pixel);
      y_motor.setSpeed(y_motor_max_speed);
      while (abs(y_motor.distanceToGo()) != 0){
        y_motor.runSpeedToPosition();
      }
    } else {
      x_motor.moveTo(x_motor.currentPosition() - x_motor_steps_per_pixel);
      x_motor.setSpeed(x_motor_max_speed);
      while (abs(y_motor.distanceToGo()) != 0){
        x_motor.runSpeedToPosition();
      }
    }
  } else {
    if (ax) {
      y_motor.moveTo(y_motor.currentPosition() + y_motor_steps_per_pixel);
      y_motor.setSpeed(y_motor_max_speed);
      while (abs(y_motor.distanceToGo()) != 0){
        y_motor.runSpeedToPosition();
      }
    } else {
      x_motor.moveTo(x_motor.currentPosition() + x_motor_steps_per_pixel);
      x_motor.setSpeed(x_motor_max_speed);
      while (abs(y_motor.distanceToGo()) != 0){
        x_motor.runSpeedToPosition();
      }
    }
  }
}

// Trajectory 1, X-Main
void trajectory1() {
  for (int j = 0; j < y_max; j++) {
     for (int i = 0; i < x_motor_total_pixels; i++) {
      if (j % 2 == 1) {
        step(0, j % 2 == 1);
        printCoord(x_max - i - 1, j);
      } else {
        printCoord(i, j);
        step(0, j % 2 == 1);
      }
     }
     step(1, 0);
   }
}

void setup() {
  Serial.begin(9600); 
  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000);
  
  x_motor.setMaxSpeed(x_motor_max_speed);
  x_motor.setSpeed(x_motor_max_speed);
  x_motor.setCurrentPosition(0);

  y_motor.setMaxSpeed(y_motor_max_speed);
  y_motor.setSpeed(y_motor_max_speed);
  y_motor.setCurrentPosition(0);
}




void loop() {
//  digitalWrite(dir_pin, LOW); // HIGH is toward motor, LOW is away
}
