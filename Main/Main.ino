/* 
 *  Creator : Thomas Cibils
 *  FastLED tuto : https://github.com/FastLED/FastLED/wiki/Basic-usage - used for WS2812B 5050 RGB LED Strip 5M 150 300 Leds 144 60LED/M Individual Addressable 5V
 *  */

#include <TimerOne.h>
#include "FastLED.h"
#include <avr/pgmspace.h>

// LED MATRIX CODE
// This marix is actually composed of four distinct 16x16 LED matrices. Constant below mirror that.

// Total number of LEDs
#define totalDisplayNumberOfRows 32                          // Number of rows
#define totalDisplayNumberOfColumns 32                       // Number of coumns
#define TOTAL_NUM_LEDS totalDisplayNumberOfRows * totalDisplayNumberOfColumns // Number of LEDs

// Number of LEDs by display
#define singleMatrixDisplayNumberOfRows 16
#define singleMatrixDisplayNumberOfColumns 16
#define SINGLE_NUM_LEDS singleMatrixDisplayNumberOfRows * singleMatrixDisplayNumberOfColumns

// And here are the four displays
CRGB ledsOne[SINGLE_NUM_LEDS];                                          // Defining leds table for FastLed
CRGB ledsTwo[SINGLE_NUM_LEDS];                                          // Defining leds table for FastLed
CRGB ledsThree[SINGLE_NUM_LEDS];                                          // Defining leds table for FastLed
CRGB ledsFour[SINGLE_NUM_LEDS];                                          // Defining leds table for FastLed

// And their respective data pins
#define LEDSONE_DATA_PIN 2                                            // Output pin for FastLed
#define LEDSTWO_DATA_PIN 3                                            // Output pin for FastLed
#define LEDSTHREE_DATA_PIN 4                                            // Output pin for FastLed
#define LEDSFOUR_DATA_PIN 5                                            // Output pin for FastLed

// On the other hand, here is our updatable digital LED Matrix
byte LEDMatrix[totalDisplayNumberOfRows][totalDisplayNumberOfColumns];

// Original colours for leds.
const byte Black = 0;
const byte White = 1;
const byte Blue = 2;
const byte Red = 3;
const byte Green = 4;
const byte Purple = 5;

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
  FastLED.addLeds<NEOPIXEL, LEDSONE_DATA_PIN>(ledsOne, SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSTWO_DATA_PIN>(ledsTwo, SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSTHREE_DATA_PIN>(ledsThree, SINGLE_NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LEDSFOUR_DATA_PIN>(ledsFour, SINGLE_NUM_LEDS);
  
}

void loop() {

if(millis() - lastMillis > 500) {


  lastMillis = millis();
}

    

  outputDisplay();
  delay(1);
}

// Makes the whole "LEDMatrix" equals to 0, i.e. each LED is off
void clearLEDMatrix() {
  // Just seting le LEDmatrix to Wall
  for (byte i = 0; i < totalDisplayNumberOfRows; i++)  {
    for (byte j = 0; j < totalDisplayNumberOfColumns; j++) {
      LEDMatrix[i][j] = Black;
    }
  }
}


// We update the physical display of the LED matrix, based on the LEDMatrix
void outputDisplay() {
  /*
  for(byte rowIndex = 0; rowIndex < displayNumberOfRows; rowIndex++) {
    for(byte columnIndex = 0; columnIndex < displayNumberOfColumns; columnIndex++) {
      // Useful because of the way my matrix is soldered.
      // So we'll invert one column every two compared to our digital matrix
      // If we're on an even column, we're fine, everything is straightfoward
      if(columnIndex%2 == 0) {
        
        if(LEDMatrix[rowIndex][columnIndex] == Black) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::Black;}
        if(LEDMatrix[rowIndex][columnIndex] == White) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::White;}
        if(LEDMatrix[rowIndex][columnIndex] == Green) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::Green;}
        if(LEDMatrix[rowIndex][columnIndex] == Blue) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::Blue;}
        if(LEDMatrix[rowIndex][columnIndex] == Red) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::Red;}
        if(LEDMatrix[rowIndex][columnIndex] == Purple) {leds[(columnIndex + 1)*displayNumberOfRows - rowIndex - 1] = CRGB::Purple;}
      }
      // If we're on an uneven column, we do a mathematical trick to invert it
      else if(columnIndex%2 == 1) {
        if(LEDMatrix[rowIndex][columnIndex] == Black) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::Black;}
        if(LEDMatrix[rowIndex][columnIndex] == White) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::White;}
        if(LEDMatrix[rowIndex][columnIndex] == Green) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::Green;}
        if(LEDMatrix[rowIndex][columnIndex] == Blue) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::Blue;}
        if(LEDMatrix[rowIndex][columnIndex] == Red) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::Red;}
        if(LEDMatrix[rowIndex][columnIndex] == Purple) {leds[columnIndex*displayNumberOfRows + rowIndex] = CRGB::Purple;}
      }
    }
  }*/
  
  // Display the matrix physically
  FastLED.show(); 
}

// We update the digital display of the LED matrix
void digitalOutputDisplay() {
  Serial.print("\n We print digitally the current theoritical state of the LED Matrix : \n");
  for (byte i = 0; i < totalDisplayNumberOfRows; i++) {
    for (byte j = 0; j < totalDisplayNumberOfColumns; j++) {
      Serial.print(LEDMatrix[i][j]);
      if (j < totalDisplayNumberOfColumns - 1) {
        Serial.print(", ");
      }
      else {
        Serial.print("\n");
      }
    }
  }
}
