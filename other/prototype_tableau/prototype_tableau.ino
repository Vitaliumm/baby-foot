#include <stdio.h>
#include <stdint.h>


//{4,6,7,8,9,5,4,9,6,115,9,6,4,8,5,2,41,4,7} ;
int tableau_vitesse [] = {};

void setup (){
  Serial.begin(9600);
  tableau_vitesse [0]= 4;
  tableau_vitesse [2]= 3;
  Serial.print(tableau_vitesse[100]);
}

void loop(){ }

/*
  int longueur = sizeof(tableau_vitesse) / sizeof(tableau_vitesse[0]);

uint32_t plusGrand = tableau_vitesse[0]; 

 for (int i = 1; i < longueur; i++) {
   Serial.print("i");
   Serial.print(i);
   Serial.print("valeur tableau");
   Serial.println(tableau_vitesse[i]);
    if (tableau_vitesse[i] > plusGrand) {
      plusGrand = tableau_vitesse[i];
    }
  }
Serial.print("le_plus_grand");
Serial.println(plusGrand);
}

void loop (){
  int longueur = sizeof(tableau_vitesse) / sizeof(tableau_vitesse[0]);
  //Serial.println(longueur); 
}
*/

