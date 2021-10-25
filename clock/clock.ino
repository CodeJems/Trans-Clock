#include <FastLED.h>

#define LED_DT 6                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B and GBR for APA102
#define LED_TYPE WS2812                                       // What kind of strip are you using (APA102, WS2801 or WS2812B)?
#define NUM_LEDS 16 

uint8_t max_bright = 40;
struct CRGB leds[NUM_LEDS];


void setup() {
  delay(2000);
  FastLED.clear();
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
} // Setup

void loop() {
  clock_time_leds();
}

void clock_time_leds(){
  static uint8_t bright = 0;
  static uint8_t hue = 0;
  static uint8_t saturation = 0;

  // 3 LEDs
  for(int i = 0;;i++){ // i and j push at different rates so the color and brightness are changed at separate rates to give an interesting affect on the LED ring
    for(int j = 0;j<16; j++){
//      hue = hue + 1 // Nice Rainbow effects
//      hue = 135 + (cos8(j*(2)+i)*60)/255; // Cyan/Purple Ocean vibes [ j changes color difference per LED / i changes color difference per full rotation through all LEDs ]
      bright = 60*cos8(i + j*30)/255+40;
      hue = 90 + 90*cos8((j/16)*255)/255;
//      saturation = 75 + 180*cos8(i + j*30)/255;
      // For all LEDs
//      leds[j] = CHSV(hue, 255, (cos8((j*30+i*15)))/5+30);  // use for hue change only
      leds[j] = CHSV(hue, 255, bright);
    }
    FastLED.show();
    FastLED.delay(1000/32);
  };
} // Display moving clock
