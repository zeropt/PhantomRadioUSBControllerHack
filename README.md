# PhantomRadioUSBControllerHack
Here is the code I used to turn an old phantom controller I had lying around into a USB compatible controller for FPV flight simulators. This can work on any controller although most can connect to a computer already.

The Library I used to turn the microcontroller into a USB Joystick can be found [here](https://github.com/ilcato/ArduinoJoystickLibrary)

Modify the Wiring and Gimbal Range values in the arduino sketch to configure and tune your controller.

![Final Controller](documentation/20200506_150437.jpg)

### Wiring Diagram
![Wiring Diagram](documentation/WiringDiagram.jpg)

### Modified Throttle
![Mode 2](documentation/20200506_120558.jpg)
I took the spring out of the left joystick y-axis to turn the controller into a mode 2 controller. I found some metal flashing that I cut and mounted to give the throttle some resistance.
