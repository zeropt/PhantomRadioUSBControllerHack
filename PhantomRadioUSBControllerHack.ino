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

//switches
#define sa_max 1000
#define sa_min 10
#define sb_max 1000
#define sb_min 10

void setup() {
  Joystick.setXAxisRange(-100, 100);
  Joystick.setYAxisRange(-100, 100);
  Joystick.setZAxisRange(-100, 100);
  Joystick.setRxAxisRange(-100, 100);

  //switches
  Joystick.setRyAxisRange(-100, 100);
  Joystick.setRzAxisRange(-100, 100);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  Joystick.setXAxis(constrain(map(analogRead(roll_pin), roll_min, roll_max, -100, 100), -100, 100));
  Joystick.setYAxis(constrain(map(analogRead(pitch_pin), pitch_min, pitch_max, -100, 100), -100, 100));
  Joystick.setZAxis(constrain(map(analogRead(throttle_pin), throttle_min, throttle_max, -100, 100), -100, 100));
  Joystick.setRxAxis(constrain(map(analogRead(yaw_pin), yaw_min, yaw_max, -100, 100), -100, 100));

  int sa_val = analogRead(sa_pin);
  if (sa_val > sa_max) {
    Joystick.setRyAxis(100);
  } else if (sa_val < sa_min) {
    Joystick.setRyAxis(-100);
  } else {
    Joystick.setRyAxis(0);
  }

  int sb_val = analogRead(sb_pin);
  if (sb_val > sb_max) {
    Joystick.setRzAxis(100);
  } else if (sb_val < sb_min) {
    Joystick.setRzAxis(-100);
  } else {
    Joystick.setRzAxis(0);
  }
}
