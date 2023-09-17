#include <Adafruit_CircuitPlayground.h>


struct rgbColor {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

// Global Array of Colors
rgbColor colors[] = {
  {148, 0, 211},     // Violet
  {255, 0, 0},      // Red
  {255, 127, 0},    // Orange
  {255, 255, 0},    // Yellow
  {0, 255, 0},      // Green
  {0, 0, 255},      // Blue
  {75, 0, 130}      // Indigo
};



  
int colorIndex = 0;
const int colorLength = 7;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastLeftButtonTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 750;    // the debounce time; increase if the output flickers
bool leftButtonWasReleased = true;


#define NEOPIX_PIN    A7
#define NUM_PIXELS    3

Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(NUM_PIXELS, NEOPIX_PIN, NEO_GBR + NEO_KHZ800);

void setup() {
  // Initialize the circuit playground
  CircuitPlayground.begin();

  CircuitPlayground.clearPixels();

  // for the external NeoPixels, must use the Adafruit_CPlay_NeoPixel functions directly
  strip.clear();
  strip.show();
}

void nextColor() {
  colorIndex++;
  if (colorIndex >= colorLength) {
    colorIndex = 0;
  }

  CircuitPlayground.setPixelColor(0, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(1, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(2, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(3, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(4, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(5, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(6, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(7, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(8, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  CircuitPlayground.setPixelColor(9, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);

  strip.setPixelColor(0, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  strip.setPixelColor(1, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  strip.setPixelColor(2, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
  strip.show();  

}

void loop() {


  
  bool minColorTimeMet = ((millis() - lastLeftButtonTime) > debounceDelay);

  // If the left button is pressed....
  if (CircuitPlayground.leftButton() && leftButtonWasReleased && minColorTimeMet) {
    CircuitPlayground.redLED(HIGH); 
    nextColor();
    lastLeftButtonTime = millis();
    leftButtonWasReleased = false;
  } else {
    leftButtonWasReleased = true;
    CircuitPlayground.redLED(LOW);  
  }

  // Clear Everything
  if (CircuitPlayground.rightButton()) {
    // Go back to first color
    colorIndex = 0;
    // Turn Off LED Ring
    CircuitPlayground.clearPixels();
    // Turn Off Externals
    strip.clear();
    strip.show();
    // Turn Off Red LED
    CircuitPlayground.redLED(LOW); 
  }
}