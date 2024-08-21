#include <Arduino.h>


const int sensor1Pin_a = 18; // Broche pour le capteur laser 1_a
const int sensor2Pin_a = 19; // Broche pour le capteur laser 2_a
const int sensor1Pin_b = 20; // Broche pour le capteur laser 1_b
const int sensor2Pin_b = 21; // Broche pour le capteur laser 2_b
volatile unsigned long sensor1Time = 0;  // millisecondes
volatile unsigned long sensor2Time = 0;  // millisecondes
float distance = 0.08;                   // en mètre
volatile float speed_a = 0; 
volatile float speed_b = 0;  

volatile bool send_a = false ;
volatile bool send_b = false ;

volatile unsigned long derniereActivation = 0;
void sensor1ISR();
void sensor2ISR();

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600); // uart with main board

  pinMode(sensor1Pin_a, INPUT_PULLUP); // CAPTEUR VITESSE
  pinMode(sensor2Pin_a, INPUT_PULLUP);
  pinMode(sensor1Pin_b, INPUT);
  pinMode(sensor2Pin_b, INPUT);

  attachInterrupt(digitalPinToInterrupt(sensor1Pin_a), sensor1ISR_a, FALLING); // CAPTEUR VITESSE
  attachInterrupt(digitalPinToInterrupt(sensor2Pin_a), sensor2ISR_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin_b), sensor1ISR_b, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin_b), sensor2ISR_b, FALLING);

}

void loop() {
  if(send_a){  // le but est dans le coté A donc c'est l'équipe B qui a marqué le point 
    String speedAStr = "B" + String(speed_a);
    Serial3.println(speedAStr);
    send_a = false ;
  }

  if(send_b){  // le but est dans le coté A donc c'est l'équipe B qui a marqué le point 
    String speedBStr = "A" + String(speed_b);
    Serial3.println(speedBStr);
    Serial.print("speed_b_sent");
    send_b = false ;
  }


}

void sensor1ISR_a() {
  sensor1Time = micros();
  Serial.print(" sensor1Time_a : ");
  Serial.println(sensor1Time);
}

void sensor1ISR_b() {
  sensor1Time = micros();
  Serial.print(" sensor1Time_b : ");
  Serial.println(sensor1Time);
}

void sensor2ISR_a() {
  static unsigned long time_detection = 0 ;
  unsigned long duration = 0;

  sensor2Time = micros();
  Serial.print(" sensor2Time_A : ");
  Serial.println(sensor2Time);

 if (sensor1Time != 0 && sensor2Time != 0 && (sensor1Time - time_detection > 500000) ) {

    time_detection = micros();

    duration = sensor2Time - sensor1Time; // durée en microsecondes
    sensor1Time = 0;
    sensor2Time = 0;
    // Calcul de la vitesse en km/h
    speed_a = (distance * 3.6) / (duration / 1000000.0);  
    speed_a = int(speed_a);
    if (speed_a > 60)
    {
      speed_a = 1; // code erreur 
    }
    Serial.print("speed_a : ");
    Serial.print(speed_a);
    Serial.println(" km/h");
     // le but est dans le coté A donc c'est l'équipe B qui a marqué le point 
    send_a = true ;
  }
}

void sensor2ISR_b() {
  static unsigned long time_detection = 0 ;
  unsigned long duration = 0;

  sensor2Time = micros();
  Serial.print(" sensor2Time_B : ");
  Serial.println(sensor2Time);

 if (sensor1Time != 0 && sensor2Time != 0 && (sensor1Time - time_detection > 500000) ) {

    time_detection = micros();

    duration = sensor2Time - sensor1Time; // durée en microsecondes
    sensor1Time = 0;
    sensor2Time = 0;
    // Calcul de la vitesse en km/h
    speed_b = (distance * 3.6) / (duration / 1000000.0);  
    speed_b = int(speed_b);
    if (speed_b > 100)
    {
      speed_b = 1; // code erreur 
    }
    Serial.print("speed_b : ");
    Serial.print(speed_b);
     // le but est dans le coté B donc c'est l'équipe A qui a marqué le point 
    Serial.println(" km/h");

    send_b = true;

  }
}

