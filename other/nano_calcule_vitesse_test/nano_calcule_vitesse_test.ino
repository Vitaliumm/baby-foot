#include <Arduino.h>

const int sensor1Pin = 3;  // Broche pour le capteur laser 1
const int sensor2Pin = 2;  // Broche pour le capteur laser 2
volatile unsigned long sensor1Time = 0;  // Millisecondes
volatile unsigned long sensor2Time = 0;  // Millisecondes
float distance = 0.08;                   // En mètres
float speed = 0;                         // Vitesse en km/h

volatile bool measurementDone = false;

void sensor1ISR();
void sensor2ISR();

void setup() {
  pinMode(sensor1Pin, INPUT_PULLUP);
  pinMode(sensor2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), sensor2ISR, FALLING);
  
  Serial.begin(115200);
  //Serial2.begin(9600, SERIAL_8N1, 1, 3);
}

void loop() {
  if (measurementDone) {
    // Désactiver les interruptions spécifiques aux capteurs
    detachInterrupt(digitalPinToInterrupt(sensor1Pin));
    detachInterrupt(digitalPinToInterrupt(sensor2Pin));

    unsigned long duration = sensor2Time - sensor1Time; // Durée en microsecondes
    sensor1Time = 0;
    sensor2Time = 0;

    // Calcul de la vitesse en km/h
    speed = (distance * 3.6) / (duration / 1000000.0);  
  
    //Serial2.println(speed); // Envoi de la vitesse via Serial2
    Serial.print("Vitesse : ");
    Serial.print(speed);
    Serial.println(" km/h");

    // Attendre 2000 ms entre chaque mesure
    delay(2000);

    // Réinitialiser le drapeau
    measurementDone = false;

    // Réactiver les interruptions spécifiques aux capteurs
    attachInterrupt(digitalPinToInterrupt(sensor1Pin), sensor1ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(sensor2Pin), sensor2ISR, FALLING);
  }
}

void sensor1ISR() {
  if (!measurementDone) {
    sensor1Time = micros();
    Serial.print(" sensor1Time : ");
    Serial.println(sensor1Time);
  }
}

void sensor2ISR() {
  if (!measurementDone) {
    sensor2Time = micros();
    Serial.print(" sensor2Time : ");
    Serial.println(sensor2Time);
    if (sensor1Time != 0) {
      measurementDone = true;
    }
  }
}
