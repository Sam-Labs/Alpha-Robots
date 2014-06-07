/*
 * TB6612FNG.cpp
 *
 * A library to interface with the motor driver TB6612FNG using the Arduino Uno.
 *
 * Author: James Jensen
 *
 * 30-jun-2013 - initial revision
 *
 */
#include "TB6612FNG.h"

// default values will work for uno
byte PIN_DRIVER_PWMA = 10;
byte PIN_DRIVER_AIN1 = 2;
byte PIN_DRIVER_AIN2 = 3;

byte PIN_DRIVER_PWMB = 11;
byte PIN_DRIVER_BIN1 = 4;
byte PIN_DRIVER_BIN2 = 5;

void setupMotors(
    byte pin_pwma,
    byte pin_ain1,
    byte pin_ain2,
    byte pin_pwmb,
    byte pin_bin1,
    byte pin_bin2
){
    PIN_DRIVER_PWMA = pin_pwma;
    PIN_DRIVER_AIN1 = pin_ain1;
    PIN_DRIVER_AIN2 = pin_ain2;

    PIN_DRIVER_PWMB = pin_pwmb;
    PIN_DRIVER_BIN1 = pin_bin1;
    PIN_DRIVER_BIN2 = pin_bin2;
    setupMotors();
}

void setupMotors(){
  pinMode(PIN_DRIVER_PWMA, OUTPUT);     
  pinMode(PIN_DRIVER_AIN1, OUTPUT);     
  pinMode(PIN_DRIVER_AIN2, OUTPUT);   
  pinMode(PIN_DRIVER_BIN1, OUTPUT);     
  pinMode(PIN_DRIVER_BIN2, OUTPUT);
}

void setMotorPwm(byte motor, byte pwm = 0){
  if( motor == MOTOR_A ){
    analogWrite(PIN_DRIVER_PWMA, pwm); // 0 to 255
  }else if( motor == MOTOR_B ){
    analogWrite(PIN_DRIVER_PWMB, pwm); // 0 to 255
  }
}

void setMotorDir(byte motor, byte dir){
  if( motor == MOTOR_A ){
    if( dir == CMD_FORWARD ){
      digitalWrite(PIN_DRIVER_AIN1, LOW);
      digitalWrite(PIN_DRIVER_AIN2, HIGH);
    }else if( dir == CMD_REVERSE ){
      digitalWrite(PIN_DRIVER_AIN1, HIGH);
      digitalWrite(PIN_DRIVER_AIN2, LOW);
    }else if( dir == CMD_STOP ){
      digitalWrite(PIN_DRIVER_AIN1, HIGH);
      digitalWrite(PIN_DRIVER_AIN2, HIGH);
    }
  }else if( motor == MOTOR_B ){
    if( dir == CMD_FORWARD ){
      digitalWrite(PIN_DRIVER_BIN1, LOW);
      digitalWrite(PIN_DRIVER_BIN2, HIGH);
    }else if( dir == CMD_REVERSE ){
      digitalWrite(PIN_DRIVER_BIN1, HIGH);
      digitalWrite(PIN_DRIVER_BIN2, LOW);
    }else if( dir == CMD_STOP ){
      digitalWrite(PIN_DRIVER_BIN1, HIGH);
      digitalWrite(PIN_DRIVER_BIN2, HIGH);
    }
  }
}

void setMotorCmd(byte motor, int cmd){
  byte dir = CMD_STOP;
  if( cmd > 0 ){
    dir = CMD_FORWARD;
  }
  if( cmd < 0 ){
    dir = CMD_REVERSE;
  }
  int absCmd = ( cmd < 0 ) ? -cmd : cmd;
  int clampedCmd = ( absCmd > 255 ) ? 255 : absCmd;
  setMotorPwm( motor, (byte)clampedCmd );
  setMotorDir( motor, dir );
}


