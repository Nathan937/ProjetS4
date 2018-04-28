

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

#define SENS_DPIN 0 //Droite
#define SENS_GPIN 1 //Gauche
#define SENS_CPIN 2 //Croisement

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

}

//=========================================================================
void loop()
{

// lecture capteur infra
//seuil suiveur de ligne blanc <100 noir>100
GoUntil(SENS_DPIN);
GoUp(500);
GoUntil(SENS_DPIN);
Join(SENS_DPIN);
do {
GoToCross();
}
while(1);

  
}

//=========================================================================
//FONCTIONS A BOUCLE

void GoToCross(){
  bool phase=0;
do{
  LedCheck();
  if(100>analogRead(SENS_DPIN)){
  motors.setM1Speed(vitesseM1);
}
if(100<analogRead(SENS_DPIN)){
  motors.setM1Speed(0);
}

if(100>analogRead(SENS_GPIN)){
  motors.setM2Speed(vitesseM2);
}
if(100<analogRead(SENS_GPIN)){
  motors.setM2Speed(0);
}

if(100<analogRead(SENS_GPIN)&&100<analogRead(SENS_DPIN)){
  phase=true;
}
 delay(1);
}
while(phase==false);

}
//-----------------------------------------------------------

void Center(){
  bool phase=false;
do{
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(vitesseM1);

 if(100>analogRead(SENS_DPIN)||100>analogRead(SENS_GPIN)) phase=true;
 

}
while(phase==false);
phase=false;
do{
   LedCheck();
  if(100>analogRead(SENS_DPIN)){
  motors.setM1Speed(vitesseM1);
}
if(100<analogRead(SENS_DPIN)){
  motors.setM1Speed(0);
}

if(100>analogRead(SENS_GPIN)){
  motors.setM2Speed(vitesseM2);
}
if(100<analogRead(SENS_GPIN)){
  motors.setM2Speed(0);
}

if(100<analogRead(SENS_CPIN)){
  phase=true;
}
 delay(1);
}
while(phase==false);
}

//-----------------------------------------------------------
void CrossRight(){
  bool phase=false;
  GoRight(500);

do{
  if(100<analogRead(SENS_GPIN))phase=true;
  GoRight(1);
 }
while(phase==false);
}
//-----------------------------------------------------------
void CrossLeft(){
  bool phase=false;
  GoLeft(500);

do{
  if(100<analogRead(SENS_DPIN)) phase=true;
  GoLeft(1);
 }
while(phase==false);
}
//-----------------------------------------------------------
void GoUntil(int sensor){
  bool phase=false;
do{
  LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(vitesseM1);

 if(100<analogRead(sensor)) phase=true;
 

}
while(phase==false);
}
//-----------------------------------------------------------
void Join(int sensor){
  bool phase=false;
do{
  LedCheck();
switch(sensor){
case SENS_DPIN:
if(100>analogRead(SENS_GPIN)) {
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(-vitesseM1/2);
}
if(100<analogRead(SENS_GPIN)) GoUp(1);
if(100>analogRead(SENS_GPIN)&&100>analogRead(SENS_DPIN))  phase=true;
  break;
  
case SENS_GPIN:
if(100>analogRead(SENS_DPIN))  {
  motors.setM2Speed(-vitesseM2/2);
  motors.setM1Speed(vitesseM1);
}
if(100<analogRead(SENS_DPIN)) GoUp(1);
if(100>analogRead(SENS_DPIN)&&100>analogRead(SENS_GPIN)) phase=true;
  break;
default:
break;
}
}
while(phase==false);
}
//-----------------------------------------------------------------------------------------------------------------

//FONCTIONS SIMPLES

void LedCheck(){
  if(100>analogRead(SENS_DPIN)) digitalWrite(LED_D,HIGH);
else digitalWrite(LED_D,LOW);
if(100>analogRead(SENS_GPIN)) digitalWrite(LED_G,HIGH);
else digitalWrite(LED_G,LOW);
if(100>analogRead(SENS_CPIN)) digitalWrite(LED_C,HIGH);
else digitalWrite(LED_C,LOW);

}
//-----------------------------
void GoUp(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void GoDown(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(-vitesseM2);
  motors.setM1Speed(-vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void GoRight(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(-vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void GoLeft(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(-vitesseM2);
  motors.setM1Speed(vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void JustRight(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(0);
  motors.setM1Speed(vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void JustRightBack(int temp){
  int count=0;
  do{
    LedCheck();
  motors.setM2Speed(0);
  motors.setM1Speed(-vitesseM1);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void JustLeft(int temp){
  int count=0;
  do{
    LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(0);
  count++;
  delay(1);
  }
  while(count<temp);
}
//-----------------------------
void JustLeftBack(int temp){
  int count=0;
  do{
    LedCheck();
  motors.setM2Speed(-vitesseM2);
  motors.setM1Speed(0);
  count++;
  delay(1);
  }
  while(count<temp);
}


