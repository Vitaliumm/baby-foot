#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int pinLumiere_a = 2; 
const int pinLumiere_b = 3 ;
const int capteur_infra_rouge_a = 19;
const int capteur_infra_rouge_b = 21;
volatile int numero_programme_a = -1 ;
volatile int numero_programme_b = -1 ;
volatile unsigned long derniereActivation = 0;

#define LED_PIN  A0
#define LED_PIN_2  A2
#define LED_COUNT 40
uint32_t blue = 0x0000FF;
uint32_t white = 0xFFFFFF;
uint32_t red = 0xFF0000;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.begin();          // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)
  
  pinMode(pinLumiere_a, INPUT_PULLUP);
  pinMode(pinLumiere_b, INPUT_PULLUP);
  pinMode(capteur_infra_rouge_a, INPUT_PULLUP);
  pinMode(capteur_infra_rouge_b, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinLumiere_a), programme_led_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinLumiere_b), programme_led_b, FALLING);
  attachInterrupt(digitalPinToInterrupt(capteur_infra_rouge_a), bute_bleu, FALLING);
  attachInterrupt(digitalPinToInterrupt(capteur_infra_rouge_b), bute_rouge, FALLING);
}

void loop() {
  if (numero_programme_a == 0) {
    //Serial.println("dans le if programme 0");
    programme_0_a(5);
  }
  if (numero_programme_a == 1) {
    programme_1_a(2);
  }
  if (numero_programme_a == 2) {
    strip.clear();
    programme_2_a(50);
  }
  if (numero_programme_a == 3) {
    programme_3_a(5);
  }
  if (numero_programme_a == 4) {
    numero_programme_a = 0;
  }
  /////// COTE B ///////
  if (numero_programme_b == 0) {
    programme_0_b(5);
  }
  if (numero_programme_b == 1) {
    programme_1_b(2);
  }
  if (numero_programme_b == 2) {
    strip.clear();
    programme_2_b(50);
  }
  if (numero_programme_b == 3) {
    programme_3_b(5);
  }
  if (numero_programme_b == 4) {
    numero_programme_b = 0;
  }
  Serial.print("numero_programme_a :");
  Serial.print(numero_programme_a);
  Serial.print("  numero_programme_b :");
  Serial.println(numero_programme_b);
}

void bute_rouge (){
  strip.fill(blue);
  strip2.fill(blue);
  strip.show();
  strip2.show();
}

void bute_bleu (){
  strip.fill(red);
  strip2.fill(red);
  strip.show();
  strip2.show();
}


void programme_led_a () {
  int tempsActuel = millis();
   if (tempsActuel - derniereActivation > 1000) { 
    derniereActivation = tempsActuel;
    numero_programme_a++;
    Serial.println("programme_led");
   }
}

void programme_led_b () {
  int tempsActuel = millis();
   if (tempsActuel - derniereActivation > 1000) { 
    derniereActivation = tempsActuel;
    numero_programme_b++;
    Serial.println("programme_led");
   }
}

void programme_0_a(int wait){
  strip.fill(white);
  strip.show();
}

void programme_0_b(int wait){
  Serial.println("white_ruban_led_2");
  strip2.fill(white);
  strip2.show();
}

void programme_1_a(int wait) {
    for(long firstPixelHue = 0; firstPixelHue < 65424; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
    Serial.println(firstPixelHue);
    Chronometre(wait);
  }
}

void programme_1_b(int wait) {
    for(long firstPixelHue = 0; firstPixelHue < 65424; firstPixelHue += 256) {
    strip2.rainbow(firstPixelHue);
    strip2.show(); // Update strip with new contents
    Serial.println(firstPixelHue);
    Chronometre(wait);
  }
}

void programme_2_a(int wait){
    Serial.println("dans programme_2");
    for(int i=0; i<LED_COUNT/3; i++) { // For each pixel...
    strip.setPixelColor(i,blue);
    strip.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait); // Pause before next pass through loop
    }
    for (int i=LED_COUNT/3; i<2*LED_COUNT/3; i++) {
      strip.setPixelColor(i,white);
    strip.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait);   
  }
    for (int i=2*LED_COUNT/3; i<LED_COUNT; i++) {
      strip.setPixelColor(i,red);
    strip.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait);
  }
}

void programme_2_b(int wait){
    Serial.println("dans programme_2");
    for(int i=0; i<LED_COUNT/3; i++) { // For each pixel...
    strip2.setPixelColor(i,blue);
    strip2.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait); // Pause before next pass through loop
    }
    for (int i=LED_COUNT/3; i<2*LED_COUNT/3; i++) {
      strip2.setPixelColor(i,white);
    strip2.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait);   
  }
    for (int i=2*LED_COUNT/3; i<LED_COUNT; i++) {
      strip2.setPixelColor(i,red);
    strip2.show();   // Send the updated pixel colors to the hardware.
    Chronometre(wait);
  }
}

void programme_3_a(int wait){
  strip.clear();
}

void programme_3_b(int wait){
  strip.clear();
}

void Chronometre(int wait){
  int timer = 0;
    while ( timer < wait){
    Serial.println("timer");
    timer++;
    }
  timer = 0;
}
