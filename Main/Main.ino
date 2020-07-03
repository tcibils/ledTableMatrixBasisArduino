/* 
 *  Creator : Thomas Cibils
 *  FastLED tuto : https://github.com/FastLED/FastLED/wiki/Basic-usage - used for WS2812B 5050 RGB LED Strip 5M 150 300 Leds 144 60LED/M Individual Addressable 5V
 *  */

#include <TimerOne.h>
#include "FastLED.h"
#include <avr/pgmspace.h>


// ----------------------------------------------------------------------------------------------------
// ----------------------------------   LED MATRIX CODE   ---------------------------------------------
// ----------------------------------------------------------------------------------------------------

// This marix is actually composed of four distinct 16x16 LED matrices. Constant below mirror that.

// Total number of LEDs
#define totalDisplayNumberOfRows 32                          // Number of rows
#define totalDisplayNumberOfColumns 32                       // Number of coumns
#define TOTAL_NUM_LEDS totalDisplayNumberOfRows * totalDisplayNumberOfColumns // Number of LEDs

// Number of LEDs by display
#define quantityOfSingleMatrixDisplay 4
#define singleMatrixDisplayNumberOfRows 16
#define singleMatrixDisplayNumberOfColumns 16
#define SINGLE_NUM_LEDS singleMatrixDisplayNumberOfRows * singleMatrixDisplayNumberOfColumns

// And here are the displays.
CRGB leds[quantityOfSingleMatrixDisplay][SINGLE_NUM_LEDS];

// And their respective data pins
#define LEDSONE_DATA_PIN 2       // Top left
#define LEDSTWO_DATA_PIN 3       // Top right
#define LEDSTHREE_DATA_PIN 4     // Bottom left
#define LEDSFOUR_DATA_PIN 5      // Bottom right

// On the other hand, here is our updatable digital LED Matrix
byte LEDMatrix[totalDisplayNumberOfRows][totalDisplayNumberOfColumns];

// Original colours for leds.
const byte Black = 0;
const byte White = 1;
const byte Blue = 2;
const byte Red = 3;
const byte Green = 4;
const byte Purple = 5;


// ----------------------------------------------------------------------------------------------------
// -------------------------------   SNES CONTROLLERS CODE   ------------------------------------------
// ----------------------------------------------------------------------------------------------------


#define NUMBER_PLAYERS 4

// PIN Mapping for each controller

// P1 is on the vent side
static const byte CONTROLLER_ONE_PIN_LATCH = 40;
static const byte CONTROLLER_ONE_PIN_CLOCK = 42;
static const byte CONTROLLER_ONE_PIN_DATA = 44;

// P2 is on the USB side
static const byte CONTROLLER_TWO_PIN_LATCH = 41;
static const byte CONTROLLER_TWO_PIN_CLOCK = 43;
static const byte CONTROLLER_TWO_PIN_DATA = 45;

// Etc
static const byte CONTROLLER_THREE_PIN_LATCH = 48;
static const byte CONTROLLER_THREE_PIN_CLOCK = 50;
static const byte CONTROLLER_THREE_PIN_DATA = 52;

static const byte CONTROLLER_FOUR_PIN_LATCH = 49;
static const byte CONTROLLER_FOUR_PIN_CLOCK = 51;
static const byte CONTROLLER_FOUR_PIN_DATA = 53;

// Table storing which player is pushing which buttons, so it can easily be accessed anywhere in the code (there are 12 buttons)
// Stored as follows: UP - RIGHT - DOWN - LEFT - START - SELECT - A - B - X - Y - L - R
byte playerButtonPushed[NUMBER_PLAYERS][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};



// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------

// Useful struct
struct pointOnMatrix {
  byte lineCoordinate;
  byte columnCoordinate;
};

unsigned long lastMillis = 0;
unsigned const int growthSpeed = 1500;  // In miliseconds. Can be used to make something happen every X miliseconds.





void setup() {

  Serial.begin(9600);

  // Set the four matrix pins to output
  FastLED.addLeds<NEOPIXEL, LEDSONE_DATA_PIN>(leds[0], SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSTWO_DATA_PIN>(leds[1], SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSTHREE_DATA_PIN>(leds[2], SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSFOUR_DATA_PIN>(leds[3], SINGLE_NUM_LEDS);

  // Sets the controllers as inputs or outputs
  pinMode(CONTROLLER_ONE_PIN_LATCH, OUTPUT);
  pinMode(CONTROLLER_ONE_PIN_CLOCK, OUTPUT);
  pinMode(CONTROLLER_ONE_PIN_DATA, INPUT); 
  
  pinMode(CONTROLLER_TWO_PIN_LATCH, OUTPUT);
  pinMode(CONTROLLER_TWO_PIN_CLOCK, OUTPUT);
  pinMode(CONTROLLER_TWO_PIN_DATA, INPUT); 
  
  pinMode(CONTROLLER_THREE_PIN_LATCH, OUTPUT);
  pinMode(CONTROLLER_THREE_PIN_CLOCK, OUTPUT);
  pinMode(CONTROLLER_THREE_PIN_DATA, INPUT); 
  
  pinMode(CONTROLLER_FOUR_PIN_LATCH, OUTPUT);
  pinMode(CONTROLLER_FOUR_PIN_CLOCK, OUTPUT);
  pinMode(CONTROLLER_FOUR_PIN_DATA, INPUT); 
}

void loop() {

if(millis() - lastMillis > 500) {


  lastMillis = millis();
}

  

    

 // outputDisplay();
  delay(1);
}
