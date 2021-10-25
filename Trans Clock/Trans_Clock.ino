#include <FastLED.h>

#define LED_DT 6                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B and GBR for APA102
#define LED_TYPE WS2812                                       // What kind of strip are you using (APA102, WS2801 or WS2812B)?
#define NUM_LEDS 16                                           // Number of LED's
//#define UPDATES_PER_SECOND 50
// Initialize changeable global variables.
uint8_t max_bright = 25;                                     // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
struct CRGB trans_pattern[3] = {CRGB::Cyan, CRGB(255, 69, 120), CRGB::White};

uint8_t max_refresh = 50;

void setup() {
  delay(2000);                                                        // Powerup safety delay
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);         // For WS2812B/WS2811 (NeoPixels)
  FastLED.setMaxRefreshRate(max_refresh);
  FastLED.setBrightness(max_bright);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1200);              // FastLED power management set at 5V, 1200mA
  FastLED.clear();
} // setup()



void loop () {
//  FastLED.clear();
  trans_march(10);                                                  // Delay - Bigger number slower rotation
//  rainbow_wave(50,255/NUM_LEDS);                                        // Speed, delta hue values.
//  FastLED.show();                                                       // Activate this for rainbow_wave funciton only
} // loop()

// Rainbow
void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {     // The fill_rainbow call doesn't support brightness levels.
// uint8_t thisHue = beatsin8(thisSpeed,0,255);               // A simple rainbow wave.
 uint8_t thisHue = beat8(thisSpeed,255);                     // A simple rainbow march.
 fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            // Use FastLED's fill_rainbow routine.
} // rainbow_wave()

//void clock_lights() {
//  // connect to internet, get time, discconect from internet, display time
//}

// Trans colors throughout whole ring
void trans_march(uint8_t Delay) {
  for(int i = 0; i< NUM_LEDS; i++) {
    for(int n = 0; n < NUM_LEDS; n++) {
      if(n<NUM_LEDS/4){
        leds[(n+i)%NUM_LEDS] = trans_pattern[0];
      }
      else if(n < NUM_LEDS/2) {
        leds[(n+i)%NUM_LEDS] = trans_pattern[1];
      }
      else if(n < (3*NUM_LEDS)/4) {
        leds[(n+i)%NUM_LEDS] = trans_pattern[2];
      }
      else if(n < NUM_LEDS) {
        leds[(n+i)%NUM_LEDS] = trans_pattern[1];
      }
    }
    FastLED.show();
    FastLED.delay(Delay);
  };
}
