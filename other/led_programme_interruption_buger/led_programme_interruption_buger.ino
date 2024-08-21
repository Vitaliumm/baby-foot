#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

int pinLumiere = 19; 
volatile int timer = 0;
volatile int affichage_led = 0;
volatile bool arret_programme_1 = false;
volatile bool accee_programme_2 = false;
volatile unsigned long derniereActivation = 0;

#define LED_PIN    A8
#define LED_COUNT 40
uint32_t blue = 0x0000FF;
uint32_t white = 0xFFFFFF;
uint32_t red = 0xFF0000;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
 
//#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
 // clock_prescale_set(clock_div_1);
//#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)
  
  Serial.begin(9600);
  pinMode(pinLumiere, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinLumiere), programme_led, FALLING);

}

void loop() {
}

void programme_1(int wait) {
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      Serial.print(arret_programme_1);
    Serial.println("dans programme_1");
      if (arret_programme_1){
        accee_programme_2 = true;
        Serial.println("return");
        return;}
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
    Chronometre(wait);
  }
}
  
void programme_2(int wait){
  Serial.println("dans programme_2    ");
  arret_programme_1 = true;
  if (accee_programme_2){
    arret_programme_1 = false;
    accee_programme_2 = false;
    
    for(int i=0; i<LED_COUNT/3; i++) { // For each pixel...
      Serial.println("dans programme_2");
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
}
    
void Chronometre(int wait){
    while ( timer < wait){
    Serial.println(timer);
    timer++;
    }
  timer = 0;
}

void programme_led(){
   int tempsActuel = millis();
   if (tempsActuel - derniereActivation > 1000) { 
    derniereActivation = tempsActuel;
    
  affichage_led ++;
  if (affichage_led == 3){
    affichage_led = 0;
  }
  //Serial.println(affichage_led);
  
  if (affichage_led == 1){
    programme_1(5);   // 10 ms 
  }
  if (affichage_led == 2){
    programme_2(50);// 500ms
    //programme_2(500);// 500ms
  }
  if (affichage_led == 0){
    
  }
  }
}
  
