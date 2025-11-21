#include <Keypad.h>
#include <FastLED.h>
#include <FastLED_NeoPixel.h>
#include <Adafruit_NeoPixel.h>

#define KP_ROWS 4
#define KP_COLS 4
#define LED_PIN 2
#define NUM_LEDS 256
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B

char keyLayout[KP_ROWS][KP_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte keypadRowPins[KP_ROWS] = {9, 8, 7, 6};
byte keypadColPins[KP_COLS] = {5, 4, 3, 2};

// Keypad kp = Keypad(makeKeymap(keyLayout), keypadRowPins, keypadColPins, KP_ROWS, KP_COLS);

CRGB leds[NUM_LEDS];

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int i = 3;

void setup() {
  Serial.begin(9600);
  // FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  // FastLED.clear();
  // FastLED.show();

  // leds[11] = CRGB::Purple;
  // FastLED.show();

  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  // char key = kp.getKey();

  // if (key) Serial.println(key);

  for (int i = 0; i < 16; i++)
  {
    for(int j = 0; j < 16; j++)
    {
      setLEDXY(&strip, j, i, strip.Color(10, 0, 10));
      delay(50);
    }
    // strip.clear();
    // strip.setPixelColor(i, 128, 0, 128);
    // strip.show();
    // delay(50);
  }
  // setLEDXY(&strip, 1, 2, strip.Color(10, 0, 10));
  // delay(50);
  // setLEDXY(&strip, 2, 2, strip.Color(10, 0, 10));
  // delay(50);
}