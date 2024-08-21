
const int interruptPin = 3;

volatile bool interruptFlag = false;




void setup() {

  Serial.begin(9600);

 

  // Configure le pin 3 comme une entrée

  pinMode(interruptPin, INPUT_PULLUP);

 

  // Attache l'interruption au pin 3

  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

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

  // Met à jour le drapeau d'interruption

  interruptFlag = true;

}
