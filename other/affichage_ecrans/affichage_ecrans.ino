#include "EasyNextionLibrary.h"
const int buttonPin = 2; // Broche du bouton poussoir
const int buttonPin2 = 3;
volatile int count = 0; // Compteur à incrémenter en interruption
volatile int conteur = -1;
volatile unsigned long derniereActivation = 0; // pour éviter les rebonds du bouton poussoir
EasyNex myNex(Serial);

void setup() {
  myNex.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Configuration de la broche du bouton en entrée avec résistance de tirage
  pinMode(buttonPin2, INPUT_PULLUP); // Configuration de la broche du bouton en entrée avec résistance de tirage
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Attache l'interruption sur la broche du bouton
  //attachInterrupt(digitalPinToInterrupt(buttonPin2), buttonInterrupt2, FALLING); // Attache l'interruption sur la broche du bouton
  Serial.begin(9600); // Démarrage de la communication série
}

void loop() {
  /*
 myNex.NextionListen(); 

  if (Serial.available()) {
    int i ;
    //Serial.println(Serial.available());
    for (i=0; i<20; i++){
      Serial.println("dans le for");
      char data = Serial.read();
      myNex.writeNum("n0.val",count);
    }
    */

    /*
    // Si des données sont disponibles
    //char data = Serial.read(); // Lit une seule donnée du buffer série
    String data = Serial.readString(); 
    
    // Faites quelque chose avec les données lues
    // Par exemple, vous pouvez les afficher
    Serial.print("Donnée reçue : ");
    Serial.println(data);
    int lengt = data.length(); // Obtient la longueur de la chaîne de caractères
    Serial.print("Longueur de la chaîne : ");
    Serial.println(lengt); // Affiche la longueur de la chaîne
    delay (1000);
    myNex.writeNum("n0.val", count);
  
  }
  // */
  myNex.writeNum("n0.val", count);
}

void buttonInterrupt() {
  int tempsActuel = millis();
  if (tempsActuel - derniereActivation > 500) { 
    derniereActivation = tempsActuel;
    count++;
    myNex.writeNum("n0.val", count);
  //Serial.println(count);
  }
}
