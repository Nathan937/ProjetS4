



#include <DRV8835MotorShield.h>
#include <hcsr04.h>
/*
 * This example uses the DRV8835MotorShield library to drive each motor with the
 * Pololu DRV8835 Dual Motor Driver Shield for Arduino forward, then backward. 
 * The yellow user LED is on when a motor is set to a positive speed and off when
 * a motor is set to a negative speed.
 */

 //Les pins du moteur 1 sont 7 et 9, moteur 2 sont 8 et 10.
#define MODE_PIN 11

#define TRIG_PIN 2
#define ECHO_PIN 3

#define LED_C 4 //JAUNE
#define LED_P 5 //BLEU
#define BOUTON 6
#define SOL 12

#define SENS_DPIN 0 //Droite
#define SENS_GPIN 1 //Gauche
#define SENS_CPIN 2 //Croisement
#define SENS_PDPIN 3 //Palet Droite
#define SENS_PGPIN 4 //Palet Gauche



//La veritable vitesse max(PWM) est 400.
#define MAX_S 200

#define SEUIL 100
#define SEUILBLANC 100
#define SEUILNOIR 600
#define SEUILD 590

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
DRV8835MotorShield motors;

//resultat vitesse moteur de la regulation avec capteur infra 
int vitesseM1=100;
int vitesseM2=100;
int countB=0;
int countT=0;
bool tir=false;
String readString;
//=========================================================================
void setup()
{

  Serial.begin(9600);
  

pinMode(LED_C, OUTPUT);
pinMode(LED_P, OUTPUT);

pinMode(SOL, OUTPUT);
pinMode(BOUTON, INPUT);

  //M2 est a gauche (correction de +25?); M1 est à droite
  
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipM1(true);
  //motors.flipM2(true);


// Ne pas oublier de brancher le mode sur le motor driver!!
digitalWrite(BOUTON, HIGH);
digitalWrite(SOL, HIGH);
  digitalWrite(MODE_PIN, HIGH);


// Le bouton doit etre appuyé pour demarrer le programme
bool phase0=false;

  do{
  delay(1);
while(Serial.available()){
  delay(3);
  char c=Serial.read();
  readString+=c; 
}
if (readString.length()>0){
  Serial.println(readString);
  if(readString=="go")phase0=true;
  readString="";
}
  
  if(0==digitalRead(BOUTON))phase0=true;
}
while(phase0==false);

delay(2000);

}

//=========================================================================
void loop()
{

// lecture capteur infra
//seuil suiveur de ligne blanc <100 noir>100
Stop(2000);
Shoot();

//Serial.println(analogRead(SENS_PPIN));


/*GoToCross();

  GoLeft(200);
GoUntil(SENS_GPIN);
Join(SENS_GPIN);


if(
  Center();
  CrossLeft();
  Shoot();*/


}


//=========================================================================
//FONCTIONS A BOUCLE

void GoToCross(){
  bool phase=0;
  int taux= SEUILNOIR-SEUILBLANC;
  double diviseur=1;
   
do{
  LedCheck();

diviseur=analogRead(SENS_DPIN)-SEUILBLANC;
diviseur=diviseur/taux;
int V1=vitesseM1-(vitesseM1*diviseur);

diviseur=analogRead(SENS_GPIN)-SEUILBLANC;
diviseur=diviseur/taux;
int V2=vitesseM2-(vitesseM2*diviseur);

  if(SEUILBLANC>analogRead(SENS_DPIN)){
  motors.setM1Speed(vitesseM1);
}
if(SEUILBLANC<analogRead(SENS_DPIN)&&SEUILNOIR>analogRead(SENS_DPIN)){
  motors.setM1Speed(V1);
}
 if(SEUILNOIR<analogRead(SENS_DPIN)){
  motors.setM1Speed(0);
}


if(SEUILBLANC>analogRead(SENS_GPIN)){
  motors.setM2Speed(vitesseM2);
}
if(SEUILBLANC<analogRead(SENS_GPIN)&&SEUILNOIR>analogRead(SENS_GPIN)){
  motors.setM2Speed(V2);
}
if(SEUILNOIR<analogRead(SENS_GPIN)){
  motors.setM2Speed(0);
}

if(SEUILNOIR<analogRead(SENS_GPIN)&&SEUILNOIR<analogRead(SENS_DPIN)){
  phase=true;
}
 
}
while(phase==false);

}
//-----------------------------------------------------------

void Center(){
  bool phase=false;
do{
  GoUp(300);
 if(SEUIL>analogRead(SENS_DPIN)||SEUIL>analogRead(SENS_GPIN)) phase=true;
 }
while(phase==false);
phase=false;

  int taux= SEUILNOIR-SEUILBLANC;
  double diviseur=1;
   

do{
   LedCheck();

diviseur=analogRead(SENS_DPIN)-SEUILBLANC;
diviseur=diviseur/taux;
int V1=vitesseM1-(vitesseM1*diviseur);

diviseur=analogRead(SENS_GPIN)-SEUILBLANC;
diviseur=diviseur/taux;
int V2=vitesseM2-(vitesseM2*diviseur);

  if(SEUILBLANC>analogRead(SENS_DPIN)){
  motors.setM1Speed(vitesseM1);
}
if(SEUILBLANC<analogRead(SENS_DPIN)&&SEUILNOIR>analogRead(SENS_DPIN)){
  motors.setM1Speed(V1);
}
 if(SEUILNOIR<analogRead(SENS_DPIN)){
  motors.setM1Speed(0);
}


if(SEUILBLANC>analogRead(SENS_GPIN)){
  motors.setM2Speed(vitesseM2);
}
if(SEUILBLANC<analogRead(SENS_GPIN)&&SEUILNOIR>analogRead(SENS_GPIN)){
  motors.setM2Speed(V2);
}
if(SEUILNOIR<analogRead(SENS_GPIN)){
  motors.setM2Speed(0);
}

if(SEUILNOIR<analogRead(SENS_CPIN)){
  phase=true;
}
 
}
while(phase==false);
}

//-----------------------------------------------------------
void CrossRight(){
  bool phase=false;
  GoRight(500);

do{
  if(SEUIL<analogRead(SENS_GPIN))phase=true;
  GoRight(1);
 }
while(phase==false);
}
//-----------------------------------------------------------
void CrossLeft(){
  bool phase=false;
  GoLeft(500);

do{
  if(SEUIL<analogRead(SENS_DPIN)) phase=true;
  GoLeft(1);
 }
while(phase==false);
}
//-----------------------------------------------------------
void CrossRightWithP(){
  bool phase=false;
  JustLeft(500);

do{
  if(SEUIL<analogRead(SENS_GPIN))phase=true;
  JustLeft(1);
 }
while(phase==false);
}
//-----------------------------------------------------------
void CrossLeftWithP(){
  bool phase=false;
  JustRight(500);

do{
  if(SEUIL<analogRead(SENS_DPIN)) phase=true;
  JustRight(1);
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

 if(SEUIL<analogRead(sensor)) phase=true;
 

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
if(SEUIL>analogRead(SENS_GPIN)) {
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(-vitesseM1*0.5);
}
if(SEUIL<analogRead(SENS_GPIN)) GoUp(1);
if(SEUIL>analogRead(SENS_GPIN)&&SEUIL>analogRead(SENS_DPIN))  phase=true;
  break;
  
case SENS_GPIN:
if(SEUIL>analogRead(SENS_DPIN))  {
  motors.setM2Speed(-vitesseM2*0.5);
  motors.setM1Speed(vitesseM1);
}
if(SEUIL<analogRead(SENS_DPIN)) GoUp(1);
if(SEUIL>analogRead(SENS_DPIN)&&SEUIL>analogRead(SENS_GPIN)) phase=true;
  break;
default:
break;
}
}
while(phase==false);
}
//-----------------------------------------------------------
void GoPerp(){
  bool phase=false;
  int sensor;
do{
  LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(vitesseM1);

 if(SEUIL<analogRead(SENS_GPIN)){
  phase=true;
  sensor=SENS_GPIN;
 }
 if(SEUIL<analogRead(SENS_DPIN)){
  phase=true;
  sensor=SENS_DPIN;
 }
 }
 
while(phase==false);
phase=false;
do{
  LedCheck();
 
switch(sensor){
case SENS_DPIN:
 if(SEUIL<analogRead(SENS_DPIN))JustRightBack(1);
 if(SEUIL>analogRead(SENS_DPIN))JustLeft(1);
 break;
 case SENS_GPIN:
 if(SEUIL<analogRead(SENS_GPIN))JustLeftBack(1);
 if(SEUIL>analogRead(SENS_GPIN))JustRight(1);
 break;
}
if(SEUIL<analogRead(SENS_DPIN)&&SEUIL<analogRead(SENS_GPIN))phase=true;
 }
while(phase==false);
}
//-----------------------------------------------------------------------------------------------------------------

//FONCTIONS SIMPLES

void LedCheck(){
  
  if(SEUIL>analogRead(SENS_DPIN)) digitalWrite(LED_C,HIGH);
else digitalWrite(LED_C,LOW);

if(0==digitalRead(BOUTON)){
   motors.setM2Speed(0);
  motors.setM1Speed(0);
   digitalWrite(LED_C, LOW);
digitalWrite(LED_P, LOW);
  digitalWrite(BOUTON, HIGH);
digitalWrite(SOL, HIGH);
  digitalWrite(MODE_PIN, HIGH);
  asm volatile ("jmp 0");
}

while(Serial.available()){
  delay(3);
  char c=Serial.read();
  readString+=c; 
}

if (readString.length()>0){
  Serial.println(readString);
  if(readString=="s"){
    motors.setM2Speed(0);
  motors.setM1Speed(0);
   digitalWrite(LED_C, LOW);
digitalWrite(LED_P, LOW);
  digitalWrite(BOUTON, HIGH);
digitalWrite(SOL, HIGH);
  digitalWrite(MODE_PIN, HIGH);
  asm volatile ("jmp 0");
  }
  readString="";
}


int a=hcsr04.distanceInMillimeters();

delay(1);

countB++;
if(39>a){
  digitalWrite(LED_P,HIGH);  
}
else {
  digitalWrite(LED_P,LOW);
}
if(countB>=400){
 if(39>=a&&tir==false) Serial.println("d");
 if(39<a&&tir==false) Serial.println("n");
 if(tir==true){
  Serial.println("t");
  countT++;
 }
 if(countT>=5){
  countT=0;
  tir==false;
 }
 countB=0;
}

}
//-----------------------------
void GoUp(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(vitesseM2);
  motors.setM1Speed(vitesseM1);
  count++;
  
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
  
  }
  while(count<temp);
}
//-----------------------------
void GoRight(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(vitesseM2*0.75);
  motors.setM1Speed(-vitesseM1*0.75);
  count++;
  
  }
  while(count<temp);
}
//-----------------------------
void GoLeft(int temp){
 int count=0;
  do{
    LedCheck();
  motors.setM2Speed(-vitesseM2*0.75);
  motors.setM1Speed(vitesseM1*0.75);
  count++;
  
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
  
  }
  while(count<temp);
}
//-----------------------------
void Stop(int temp){
  int count=0;
  do{
    LedCheck();
  motors.setM2Speed(0);
  motors.setM1Speed(0);
  count++;
  
  }
  while(count<temp);
}
//-----------------------------
void Shoot(){
  int temp =50;
  int count=0;
 tir=true;
  
  do{
    LedCheck();
  
  count++;
  if(count>30)digitalWrite(SOL,LOW);
  delay(1);
  }
  while(count<temp);
  Stop(1);
  delay(100);
  digitalWrite(SOL,HIGH);
}

