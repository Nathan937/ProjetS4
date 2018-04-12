#include <DRV8835MotorShield.h>

/*
 * This example uses the DRV8835MotorShield library to drive each motor with the
 * Pololu DRV8835 Dual Motor Driver Shield for Arduino forward, then backward. 
 * The yellow user LED is on when a motor is set to a positive speed and off when
 * a motor is set to a negative speed.
 */
#define MODE_PIN 2
#define LED_PIN 13
#define SENS_LPIN 0

//La veritable vitesse max(PWM) est 400.
#define MAX_S 200

#define REF_VIT 200

DRV8835MotorShield motors;

//resultat viteese moteur de la regulation avec capteur infra 


void setup()
{

  Serial.begin(9600);
  
  pinMode(LED_PIN, OUTPUT);
  
  
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipM1(true);
  //motors.flipM2(true);


// Ne pas oublier de brancher le mode sur le motor driver!!
  digitalWrite(MODE_PIN, HIGH);


  
}

void loop()
{



  
  // run M1 motor with positive speed
  
  digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= MAX_S; speed++)
  {
    motors.setM1Speed(speed);
    delay(4);
  }

  for (int speed = MAX_S; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(4);
  }
  
  // run M1 motor with negative speed
  
  digitalWrite(LED_PIN, LOW);
  
  for (int speed = 0; speed >= -MAX_S; speed--)
  {
    motors.setM1Speed(speed);
    delay(4);
  }
  
  for (int speed = -MAX_S; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(4);
  }

//Sequences de 2 secondes à differentes vitesses


 for (int speed = 0; speed >= -MAX_S; speed=speed-50)
  {
    motors.setM1Speed(speed);
    delay(2000);
  }

  for (int speed = -MAX_S; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(4);
  }
  
  for (int speed = 0; speed <= MAX_S; speed=speed+50)
  {
    motors.setM1Speed(speed);
    delay(2000);
  }

  for (int speed = MAX_S; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(4);
  }

  
}
