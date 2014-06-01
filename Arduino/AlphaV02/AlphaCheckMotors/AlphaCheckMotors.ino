/* 
 * code to exercise the motor TB6612FNG motor driver chip on Pololu carrier
 *
 *  Runs robot through a sequence to try out different drive combos
 */
 
#include "Arduino.h"
#include "TB6612FNG.h"

const byte PIN_LED = 13;

// ==================================================================

void setup(){             
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(PIN_LED, OUTPUT);  
  
  // setupMotors(); // Uno, AlphaV01
  setupMotors( // Teensy 3, AlphaV02
    10, // PWMA
    12, // AIN1
    11, // AIN2
    9, // PWMB
    7, // BIN1
    8  // BIN2
  );
    
  digitalWrite(PIN_LED, HIGH);
  delay(1000);

  uint8_t power = 80; // pwr can be between 0 and 255
  
  // left motor forward
  setMotorCmd(MOTOR_A, 0); 
  setMotorCmd(MOTOR_B, power); 
  delay(1000);
 
  // left motor backward
  setMotorCmd(MOTOR_A, 0); 
  setMotorCmd(MOTOR_B, -power); 
  delay(1000);
 
  // right motor forward
  setMotorCmd(MOTOR_A, power); 
  setMotorCmd(MOTOR_B, 0); 
  delay(1000);

  // right motor backward
  setMotorCmd(MOTOR_A, -power); 
  setMotorCmd(MOTOR_B, 0); 
  delay(1000);
 
  // robot forward
  setMotorCmd(MOTOR_A, power);
  setMotorCmd(MOTOR_B, power); 
  delay(1000);

  // robot backward
  setMotorCmd(MOTOR_A, -power);
  setMotorCmd(MOTOR_B, -power); 
  delay(1000);

  // robot spin CCW
  setMotorCmd(MOTOR_A, power);
  setMotorCmd(MOTOR_B, -power); 
  delay(1000);

  // robot spin CW
  setMotorCmd(MOTOR_A, -power);
  setMotorCmd(MOTOR_B, power); 
  delay(1000);

  // stop
  setMotorCmd(MOTOR_A, 0);
  setMotorCmd(MOTOR_B, 0); 

  digitalWrite(PIN_LED, LOW);
}



void loop(){
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  digitalWrite(PIN_LED, LOW);
  delay(1000);

}

