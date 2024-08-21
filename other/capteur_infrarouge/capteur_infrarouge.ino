// Broche du capteur infrarouge
const int pinIR = 20;

void setup() {
  // Initialisation du port série
  Serial.begin(9600);
  // Configuration de la broche du capteur en entrée
  pinMode(pinIR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinIR), yeas, RISING);//CAPTEURS INFRAROUGE
}

void loop() {

 // int valeurIR = analogRead(pinIR);
  int valeur_digital = digitalRead(pinIR);

  //Serial.print("valeur_analog: ");
  //Serial.print(valeurIR);
 // Serial.print("   valeur_digital: ");
  //Serial.println(valeur_digital);
  
//debug();
}

void yeas(){
  for (int i =0; i<1; i++){
  Serial.println("balle detecter");
  }
}


void debug (){
  if (digitalRead(pinIR) == 1){
    for (int i = 0; i < 20; i++) {
  Serial.println("Erreur");
    }
  }
}

