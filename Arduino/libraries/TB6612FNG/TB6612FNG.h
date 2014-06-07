/*
 * TB6612FNG.h
 *
 * A library to interface with the motor driver TB6612FNG using the Arduino Uno.
 *
 * Author: James Jensen
 *
 * 30-jun-2013 - initial revision
 * updated
 *
 */

#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include "Arduino.h"

#define CMD_FORWARD 40
#define CMD_REVERSE 41
#define CMD_STOP 42

#define MOTOR_A 100 // arbitrary const to id motors
#define MOTOR_B 101

/*
 * Commands to control motors.  Call setupMotors() prior to calling other commands.
 * The simplest way to command motors is to just use the function setMotorCmd().  The command should
 * be between -255 and 255.  A negative number will go in reverse, a posiative will go forward, and
 * 0 to stop.
 * The other two functions can be used to just change pwm or direction independently.
 */


// Call this version of setup to choose the output pins.
// Two need to be pwm capable, the others, just digital io.

void setupMotors(
    byte pin_pwma,
    byte pin_ain1,
    byte pin_ain2,
    byte pin_pwmb,
    byte pin_bin1,
    byte pin_bin2
);

void setupMotors();

void setMotorCmd(byte motor, int cmd);

void setMotorPwm(byte motor, byte pwm);
void setMotorDir(byte motor, byte cmd);



#endif  // _MOTOR_DRIVER_H_
