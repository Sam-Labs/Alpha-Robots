/* 
 * code to exercise the motor TB6612FNG motor driver chip on Pololu carrier
 *
 *  Runs robot through a sequence to try out different drive combos
 */
 
#include "Arduino.h"
#include "TB6612FNG.h"

const byte PIN_LED = 13;

const byte XAXIS_ANALOG = 1;
const byte YAXIS_ANALOG = 2;

uint32_t lastMs = 0;
uint32_t blinkEms = 0;
uint32_t tmpEms = 0;

// ==================================================================

void setup(){             
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(PIN_LED, OUTPUT);  
  
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
  digitalWrite(PIN_LED, LOW);

  lastMs = millis();
  blinkEms = 0;
  tmpEms = 0;
}

// ==================================================================

bool ledOn = false;

void loop(){
  
  // --------------------------------------------------------
  // calculate time since last
  uint32_t nowMs = millis();
  uint32_t delta = nowMs - lastMs;
  lastMs = nowMs;

  // incr elapsed vars
  blinkEms += delta;
  tmpEms += delta;

  // --------------------------------------------------------

  if( ledOn && blinkEms > 20 ){
    blinkEms = 0;
    ledOn = false;
  }else if( !ledOn && blinkEms > 50 ){
    blinkEms = 0;
    ledOn = true;
  }

  // --------------------------------------------------------
  // handle joystick to motor
  uint16_t xAxisRead = analogRead(XAXIS_ANALOG);
  uint16_t yAxisRead = analogRead(YAXIS_ANALOG);
  float xAxisDuty = (xAxisRead - 507) / 512.0f;
  float yAxisDuty = (yAxisRead - 504) / 512.0f;

  float turnScale = 0.4f; // derate turning strength
  float fwdDuty = yAxisDuty;
  float turnDuty = xAxisDuty*turnScale; 
  float rightDuty = max(-1.0f, min(1.0f, fwdDuty - turnDuty));
  float leftDuty = max(-1.0f, min(1.0f, fwdDuty + turnDuty));

  if( tmpEms > 1000 ){
    tmpEms = 0;
    Serial.print("Readings x=");
    Serial.print(xAxisRead);
    Serial.print(" y=");
    Serial.print(yAxisRead);
    Serial.print(" duty x=");
    Serial.print(xAxisDuty);
    Serial.print(" y=");
    Serial.print(yAxisDuty);
    Serial.print("   fwd=");
    Serial.print(fwdDuty);
    Serial.print(" turn=");
    Serial.print(turnDuty);
    Serial.print(" right=");
    Serial.print(rightDuty);
    Serial.print(" left=");
    Serial.println(leftDuty);
  }

  setMotorCmd(MOTOR_A, (int)(254 * rightDuty) ); 
  setMotorCmd(MOTOR_B, (int)(254 * leftDuty) ); 
  digitalWrite(PIN_LED, ledOn);
}

