//const int interruptPin = 2;  // Broche d'interruption

volatile bool interruptFlag = false;

void setup() {
  Serial.begin(9600);
  
  // Configure les broches 2 à 13 comme des entrées
  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, INPUT_PULLUP);
  }
  
  // Attache les interruptions aux broches 2 à 13
  for (int pin = 2; pin <= 13; pin++) {
    attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt, FALLING);
  }
}

void loop() {
  if (interruptFlag) {
    // Le drapeau d'interruption est activé, faire quelque chose...
    Serial.println("Interruption détectée !");
    
    // Réinitialise le drapeau d'interruption
    interruptFlag = false;
  }
  
  // Autres opérations à effectuer dans la boucle principale
}

// Fonction de gestion de l'interruption
void handleInterrupt() {
  interruptFlag = true;  // Met à jour le drapeau d'interruption
}
