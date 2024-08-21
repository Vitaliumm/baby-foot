
#include "EasyNextionLibrary.h"
const int buttonPin = 2; // Broche du bouton poussoir
const int buttonPin2 = 3;
volatile int count = 0; // Compteur à incrémenter en interruption
volatile int conteur = -1;
volatile unsigned long derniereActivation = 0; // pour éviter les rebonds du bouton poussoir
String tableau [4][2] = {{"t5.txt"," "},{"t6.txt"," "},{"t7.txt"," "},{"t8.txt"," "}};
String texteAafficher = "";
String valeur = "";
EasyNex myNex(Serial);

void setup() {
  myNex.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Configuration de la broche du bouton en entrée avec résistance de tirage
  pinMode(buttonPin2, INPUT_PULLUP); // Configuration de la broche du bouton en entrée avec résistance de tirage
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Attache l'interruption sur la broche du bouton
  attachInterrupt(digitalPinToInterrupt(buttonPin2), buttonInterrupt2, FALLING); // Attache l'interruption sur la broche du bouton
  Serial.begin(9600); // Démarrage de la communication série
}

void loop() {
  if (texteAafficher != "") {
    String nom = tableau[conteur][0] ;
    myNex.writeStr(nom, texteAafficher);
    myNex.writeStr(nom, texteAafficher);
    //delay(100);
    texteAafficher = "";
  }
  if (valeur !=""){
    //myNex.writeNum("n0.val", count);
    valeur = "";
  }
}

void buttonInterrupt() {
  valeur = "oui";
  count++;
  myNex.writeNum("n0.val", count);
  //Serial.println(count);
}

void buttonInterrupt22() {
  int tempsActuel = millis();
  if (tempsActuel - derniereActivation > 500) { 
    derniereActivation = tempsActuel;
    conteur++;
    tableau [conteur][1]= "20";
   myNex.writeStr(tableau [conteur][0],"20");
   /*
   Serial.print("conteur = ");
   Serial.print(conteur);
   Serial.print("valeur");
  Serial.println(tableau [conteur][1]);
  */
  }
}

void buttonInterrupt2() {
  int tempsActuel = millis();
  if (tempsActuel - derniereActivation > 500) { 
    derniereActivation = tempsActuel;
    conteur++;
  texteAafficher = "20";
  }
}
