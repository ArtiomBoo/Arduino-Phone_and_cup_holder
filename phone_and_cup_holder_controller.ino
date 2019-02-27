//port 13
#define BLACK 0x0000

#include "FastLED.h"

#define STRIP_2 16 //ssd
#define STRIP_3 16 //ssd

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 255

CRGB leds_2[STRIP_2];
CRGB leds_3[STRIP_3];
        
void setup() {    
  FastLED.addLeds<LED_TYPE, 2,COLOR_ORDER>(leds_2, STRIP_2).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 3,COLOR_ORDER>(leds_3, STRIP_3).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);// global brightness
}

//******* Main program **************************************************
void loop() {   
  randomSeed(millis());
  //int wait=random(10,30);
  int wait= 5;
  //int dim=random(4,6);
  int dim=1;
  int max_cycles=8;
  //int cycles=random(1,max_cycles+1); 
  int cycles= 1; 

  //*** Working ***
  //rainbowCycle(wait, cycles, dim);
  single_color(); 
  //leds_off();
}

//********* Efects *******************************************************

void one_color(uint8_t r_2, uint8_t g_2, uint8_t b_2, uint8_t BRIGHTNESS_2, 
               uint8_t r_3, uint8_t g_3, uint8_t b_3, uint8_t BRIGHTNESS_3) {
  for (int i = 0; i < STRIP_2; ++i) { leds_2[i] = CRGB( r_2, g_2, b_2); }
  for (int i = 0; i < STRIP_3; ++i) { leds_3[i] = CRGB( r_3, g_3, b_3); }

  FastLED[0].showLeds(BRIGHTNESS_2);
  FastLED[1].showLeds(BRIGHTNESS_3);
}

void leds_off() {
  for (int i = 0; i < 60; ++i) {        
    leds_2[i] = BLACK; 
    leds_3[i] = BLACK; 
    FastLED.show();
  }
}

void rainbowCycle(int wait, int cycles, int dim) {
  for(int cycle=0; cycle < cycles; cycle++){
    byte dir=0;
    int k=255;
    
    for (int j=0; j < 256; j++,k--) { 
      if(k<0) {
        k=255;
      }
      
      for(int i=0; i<STRIP_2; i++) {
        CRGB ledColor = wheel(((i * 256 / STRIP_2) + (dir==0?j:k)) % 256,dim);        
        leds_2[i]=ledColor;        
      }
      for(int i=0; i<STRIP_3; i++) {
        CRGB ledColor = wheel(((i * 256 / STRIP_3) + (dir==0?j:k)) % 256,dim);        
        leds_3[i]=ledColor;        
      }
      FastLED.show();
      FastLED.delay(wait);
    }
  }
}

//********* Help method ***********************************************
CRGB wheel(int WheelPos, int dim) {
  CRGB color;
  if (85 > WheelPos) {
   color.r=0;
   color.g=WheelPos * 3/dim;
   color.b=(255 - WheelPos * 3)/dim;;
  } 
  else if (170 > WheelPos) {
   color.r=WheelPos * 3/dim;
   color.g=(255 - WheelPos * 3)/dim;
   color.b=0;
  }
  else {
   color.r=(255 - WheelPos * 3)/dim;
   color.g=0;
   color.b=WheelPos * 3/dim;
  }
  return color;
}

void single_color(){
  uint8_t r_2 = 0;
  uint8_t g_2 = 0; 
  uint8_t b_2 = 255; 
  uint8_t BRIGHTNESS_2 = 255; 
  
  uint8_t r_3 = 0;
  uint8_t g_3 = 0;
  uint8_t b_3 = 255;
  uint8_t BRIGHTNESS_3 = 255; 

  one_color(r_2, g_2, b_2, BRIGHTNESS_2, 
            r_3, g_3, b_3, BRIGHTNESS_3);
}
