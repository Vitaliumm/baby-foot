#include "EasyNextionLibrary.h"
EasyNex myNex(Serial);

const int sensor1Pin_a = 18; // Broche pour le capteur laser 1_a
const int sensor2Pin_a = 19; // Broche pour le capteur laser 2_a
const int sensor1Pin_b = 20; // Broche pour le capteur laser 1_b
const int sensor2Pin_b = 21; // Broche pour le capteur laser 2_b
volatile unsigned long sensor1Time = 0;  // millisecondes
volatile unsigned long sensor2Time = 0;  // millisecondes  // millisecondes
float distance = 0.08;                   // en mètre
volatile float speed_a = 0; 
volatile float speed_b = 0;              // Vitesse en km/h
volatile unsigned long derniereActivation = 0;

void setup() {
  pinMode(sensor1Pin_a, INPUT_PULLUP);
  pinMode(sensor2Pin_a, INPUT_PULLUP);
    pinMode(sensor1Pin_b, INPUT_PULLUP);
  pinMode(sensor2Pin_b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin_a), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin_a), sensor2ISR_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin_b), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin_b), sensor2ISR_b, FALLING);
  Serial.begin(9600);
  myNex.begin(9600);
}

void loop() {
  myNex.writeNum("n2.val", speed_a );
  myNex.writeNum("n3.val", speed_b );
}

void sensor1ISR() {
  sensor1Time = millis();
  Serial.print(" sensor1Time : ");
  Serial.println(sensor1Time);
}

void sensor2ISR_a() {
  sensor2Time = millis();
  Serial.print(" sensor2Time : ");
  Serial.println(sensor2Time);
  if (sensor1Time != 0 && sensor2Time != 0) {
    unsigned long duration = sensor2Time - sensor1Time;
    //Serial.print(" duration : ");
    //Serial.println(duration);

    speed_a = ((distance * 3.6) / (duration)) * 1000;
    //speed = int(speed);
    Serial.print("Vitesse : ");
    Serial.print(speed_a);
    Serial.println(" km/h");

    sensor1Time = 0;
    sensor2Time = 0;
  }
}

void sensor2ISR_b() {
  sensor2Time = millis();
  Serial.print(" sensor2Time : ");
  Serial.println(sensor2Time);
  if (sensor1Time != 0 && sensor2Time != 0) {
    unsigned long duration = sensor2Time - sensor1Time;
    //Serial.print(" duration : ");
    //Serial.println(duration);

    speed_b = ((distance * 3.6) / (duration)) * 1000;
    //speed = int(speed);
    Serial.print("Vitesse : ");
    Serial.print(speed_b);
    Serial.println(" km/h");

    sensor1Time = 0;
    sensor2Time = 0;
  }
}

/*
void sensor1ISR() {
  int tempsActuel = millis();

  if (tempsActuel - derniereActivation > 300) { 
    derniereActivation = tempsActuel;
    sensor1Time = millis();
    //Serial.print(" sensor1Time : ");
    //Serial.println(sensor1Time);
  }
}

void sensor2ISR() {
  int tempsActuel2 = millis();

  if (tempsActuel2 - derniereActivation > 300) { 
    derniereActivation = tempsActuel2;
    sensor2Time = millis();
    //Serial.print(" sensor2Time : ");
    //Serial.println(sensor2Time);
  }
}
*/