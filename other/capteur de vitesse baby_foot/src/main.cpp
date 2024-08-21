#include <Arduino.h>


const int sensor1Pin = 20;    // A3            // Broche pour le capteur laser 1
const int sensor2Pin = 21;                // Broche pour le capteur laser 2
volatile unsigned long sensor1Time = 0;  // millisecondes
volatile unsigned long sensor2Time = 0;  // millisecondes
float distance = 0.08;                   // en mètre
float speed = 0;                         // Vitesse en km/h

volatile unsigned long derniereActivation = 0;
void sensor1ISR();
void sensor2ISR();
void setup() {
  pinMode(sensor1Pin, INPUT_PULLUP);
  pinMode(sensor2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), sensor2ISR, FALLING);
  
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 1, 3);
}

void loop() {
  unsigned long duration = 0;

  if (sensor1Time != 0 && sensor2Time != 0) {

    noInterrupts();  // Désactiver les interruptions

    duration = sensor2Time - sensor1Time; // durée en microsecondes
    sensor1Time = 0;
    sensor2Time = 0;
    // Calcul de la vitesse en km/h
    speed = (distance * 3.6) / (duration / 1000000.0);  
  
    Serial2.println(speed); // Envoie de la vitesse via Serial2
    Serial.print("Vitesse : ");
    Serial.print(speed);
    Serial.println(" km/h");
    delay(2000);

    interrupts();  // Réactiver les interruptions
  }

}

void sensor1ISR() {
  sensor1Time = micros();
  Serial.print(" sensor1Time : ");
  Serial.println(sensor1Time);

}

void sensor2ISR() {
  sensor2Time = micros();
  Serial.print(" sensor2Time : ");
  Serial.println(sensor2Time);
}
