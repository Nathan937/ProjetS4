

#include <DRV8835MotorShield.h>

/*
 * This example uses the DRV8835MotorShield library to drive each motor with the
 * Pololu DRV8835 Dual Motor Driver Shield for Arduino forward, then backward. 
 * The yellow user LED is on when a motor is set to a positive speed and off when
 * a motor is set to a negative speed.
 */

 //Les pins du moteur 1 sont 7 et 9, moteur 2 sont 8 et 10.
#define MODE_PIN 2
#define LED_D 3
#define LED_G 4
#define LED_C 5
#define BOUTON 12
#define SOL 13

#define SENS_DPIN 0 //Droite
#define SENS_GPIN 1 //Gauche
#define SENS_CPIN 2 //Croisement
#define SENS_DPIN 3 //Distance

//La veritable vitesse max(PWM) est 400.
#define MAX_S 200

#define REF_VIT 200

DRV8835MotorShield motors;

//resultat vitesse moteur de la regulation avec capteur infra 
int vitesseM1=100;
int vitesseM2=120;

//=========================================================================
void setup()
{

  Serial.begin(9600);
  
  pinMode(LED_D, OUTPUT);
   pinMode(LED_G, OUTPUT);
pinMode(LED_C, OUTPUT);
pinMode(BOUTON, INPUT);
pinMode(SOL, OUTPUT);
  //M2 est a gauche (correction de +25?); M1 est à droite
  
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipM1(true);
  //motors.flipM2(true);


// Ne pas oublier de brancher le mode sur le motor driver!!
digitalWrite(BOUTON, HIGH);
  digitalWrite(MODE_PIN, HIGH);


// Le bouton doit etre appuyé pour demarrer le programme
bool phase0=false;
  do{
  delay(1);
  phase0=!digitalRead(BOUTON);
}
while(phase0==false);

delay(1000);
Serial.begin(9600);
}

//=========================================================================
void loop()
{

// lecture capteur infra
//seuil suiveur de ligne blanc <100 noir>100

if(digitalRead(BOUTON)==true)digitalWrite(SOL,HIGH);
else digitalWrite(SOL,LOW);

  
}


