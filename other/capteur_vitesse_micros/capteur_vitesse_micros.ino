const int sensor1Pin = 18;    // A3            // Broche pour le capteur laser 1
const int sensor2Pin = 17;                // Broche pour le capteur laser 2
volatile unsigned long sensor1Time = 0;  // microsecondes
volatile unsigned long sensor2Time = 0;  // microsecondes
float distance = 0.08;                   // en mètre
float speed = 0;                         // Vitesse en km/h

void setup() {
  pinMode(sensor1Pin, INPUT_PULLUP);
  pinMode(sensor2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1Pin), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), sensor2ISR, FALLING);
  
  Serial.begin(9600);
}

void loop() {
  if (sensor1Time != 0 && sensor2Time != 0) {
    unsigned long duration = sensor2Time - sensor1Time;
    // Serial.print("duration : ");
    // Serial.println(duration);

    speed = ((distance * 3.6) / (duration / 1000000.0));
    Serial.print("Vitesse : ");
    Serial.print(speed);
    Serial.println(" km/h");

    sensor1Time = 0;
    sensor2Time = 0;
  }
}

void sensor1ISR() {
  sensor1Time = micros();
  Serial.print("sensor1Time : ");
  Serial.println(sensor1Time);
}

void sensor2ISR() {
  sensor2Time = micros();
  Serial.print("sensor2Time : ");
  Serial.println(sensor2Time);
}
