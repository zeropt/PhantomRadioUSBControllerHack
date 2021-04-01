#include <Joystick.h>

// This is the Code I wrote for the hacked DJI Phantom Radio to turn it into a 
// USB Game controller for flight simulators
// The following link is the library I used for this sketch
// https://github.com/ilcato/ArduinoJoystickLibrary

// created 6 May 2020
// by Riley Mann

//Create the Joystick
Joystick_ Joystick(0x03,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, and Z Axis
  true, true, true,     // Rx, Ry, and Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

#define AXIS_MIN -100
#define AXIS_MAX 100

//Wiring
#define throttle_pin  A0
#define yaw_pin       A1
#define pitch_pin     A2
#define roll_pin      A3
#define sa_pin        A4
#define sb_pin        A5

//Gimbal Ranges
// I used these to tune the controller
// values may vary from radio to radio
// flip max and min to reverse a channel
#define throttle_max  594
#define throttle_min  423
#define yaw_max       589
#define yaw_min       417
#define pitch_max     605
#define pitch_min     433
#define roll_max      419
#define roll_min      591

#define THROW_MIN 0
#define THROW_MAX 100

//switches
#define sa_max 1000
#define sa_min 10
#define sb_max 1000
#define sb_min 10

//Flight Correction
#define correction_delay 120000
#define correction_t 500
#define rand_min 10000
#define rand_max 30000

unsigned long prev_millis = 0;
int current_wait = 0;
boolean correcting = false;
int roll_correction = 0;
int pitch_correction = 0;
int throttle_correction = 0;
int yaw_correction = 0;

void setup() {
  Joystick.setXAxisRange(AXIS_MIN, AXIS_MAX);
  Joystick.setYAxisRange(AXIS_MIN, AXIS_MAX);
  Joystick.setZAxisRange(AXIS_MIN, AXIS_MAX);
  Joystick.setRxAxisRange(AXIS_MIN, AXIS_MAX);

  //switches
  Joystick.setRyAxisRange(AXIS_MIN, AXIS_MAX);
  Joystick.setRzAxisRange(AXIS_MIN, AXIS_MAX);

  // Initialize Joystick Library
  Joystick.begin();
  prev_millis = millis();
  current_wait = correction_delay;
}

void loop() {
  Joystick.setXAxis(constrain(map(analogRead(roll_pin), roll_min, roll_max, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX));
  Joystick.setYAxis(constrain(map(analogRead(pitch_pin), pitch_min, pitch_max, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX));
  Joystick.setZAxis(constrain(map(analogRead(throttle_pin), throttle_min, throttle_max, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX));
  Joystick.setRxAxis(constrain(map(analogRead(yaw_pin), yaw_min, yaw_max, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX));

  int sa_val = analogRead(sa_pin);
  if (sa_val > sa_max) {
    Joystick.setRyAxis(THROW_MAX);
  } else if (sa_val < sa_min) {
    Joystick.setRyAxis(THROW_MIN);
  } else {
    Joystick.setRyAxis((THROW_MIN + THROW_MAX)/2.0);
  }

  int sb_val = analogRead(sb_pin);
  if (sb_val > sb_max) {
    Joystick.setRzAxis(THROW_MAX);
  } else if (sb_val < sb_min) {
    Joystick.setRzAxis(THROW_MIN);
  } else {
    Joystick.setRzAxis((THROW_MIN + THROW_MAX)/2.0);
  }
  if (correcting) {
    correct();
    if ((millis() - prev_millis) > correction_t) {
      correcting = false;
      prev_millis = millis();
    }
  } else {
    if ((millis() - prev_millis) > current_wait) {
      get_correction();
      correcting = true;
      current_wait = random(rand_min, rand_max);
      prev_millis = millis();
    }
  }
}

void get_correction() {
  roll_correction = constrain(map(random(3), 0, 2, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX);
  pitch_correction = constrain(map(random(3), 0, 2, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX);
  throttle_correction = constrain(map(random(3), 0, 2, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX);
  yaw_correction = constrain(map(random(3), 0, 2, THROW_MIN, THROW_MAX), THROW_MIN, THROW_MAX);
}

void correct() {
  Joystick.setXAxis(roll_correction);
  Joystick.setYAxis(pitch_correction);
  Joystick.setZAxis(throttle_correction);
  Joystick.setRxAxis(yaw_correction);
}

//4/1/2021
