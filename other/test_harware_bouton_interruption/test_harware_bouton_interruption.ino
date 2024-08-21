const int pinBouton = 19;  // Broche utilisée pour le bouton d'interruption
volatile bool boutonPresse = false;  // Variable volatile pour indiquer si le bouton a été pressé

void setup() {
  pinMode(pinBouton, INPUT_PULLUP);  // Configure la broche du bouton en entrée avec une résistance de pull-up interne
  attachInterrupt(digitalPinToInterrupt(pinBouton), boutonInterruption, FALLING);  // Attache l'interruption à la broche du bouton lorsque le signal tombe (FALLING)
  
  Serial.begin(9600);  // Initialise la communication série à 9600 bauds
  Serial.println("Attente de l'interruption du bouton...");
}

void loop() {
  if (boutonPresse) {
    Serial.println("Bouton pressé !");
    boutonPresse = false;  // Réinitialise le drapeau du bouton à false
  }
  // Autres instructions à exécuter dans la boucle principale
}

void boutonInterruption() {
  boutonPresse = true;  // Définit le drapeau du bouton à true lorsqu'une interruption se produit
}
