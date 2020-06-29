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


// ----------------------------------------------------------------------------------------------------
// -------------------------------   SNES CONTROLLERS CODE   ------------------------------------------
// ----------------------------------------------------------------------------------------------------

// Defindes bits for each button
#define BTN_A 256
#define BTN_B 1
#define BTN_X 512
#define BTN_Y 2
#define BTN_SELECT 4
#define BTN_START 8
#define BTN_UP 16
#define BTN_DOWN 32
#define BTN_LEFT 64
#define BTN_RIGHT 128
#define BTN_L 1024
#define BTN_R 2048
#define NO_GAMEPAD 61440

// PIN Mapping for each controller
static const byte CONTROLLER_ONE_PIN_LATCH = 6;
static const byte CONTROLLER_ONE_PIN_CLOCK = 7;
static const byte CONTROLLER_ONE_PIN_DATA = 8;

static const byte CONTROLLER_TWO_PIN_LATCH = 41;
static const byte CONTROLLER_TWO_PIN_CLOCK = 43;
static const byte CONTROLLER_TWO_PIN_DATA = 45;

static const byte CONTROLLER_THREE_PIN_LATCH = 48;
static const byte CONTROLLER_THREE_PIN_CLOCK = 50;
static const byte CONTROLLER_THREE_PIN_DATA = 52;

static const byte CONTROLLER_FOUR_PIN_LATCH = 49;
static const byte CONTROLLER_FOUR_PIN_CLOCK = 51;
static const byte CONTROLLER_FOUR_PIN_DATA = 53;


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

  pinMode(12, OUTPUT);
}

void loop() {

if(millis() - lastMillis > 500) {


  lastMillis = millis();
}

  // The code below currently reads the buttons from controller X, and display them in a digital display
  // This will allow me to check that the controller work before coding anything else
  
   static uint16_t oldBtns = 0;      // Anciennes valeurs des boutons
   uint16_t btns = getSnesButtons(0); // Valeurs actuelles des boutons
 
  /* Affiche l'état des boutons uniquement en cas de changement */
  if(oldBtns != btns)
    oldBtns = btns;
  else
    return;
  
  // Détecte la présence (ou non) d'une manette
  if(btns & NO_GAMEPAD) {
    Serial.println(F("No gamepad connected"));
    return;
  }
  
  // Affiche l'état de chaque bouton
  if(btns & BTN_A) {
    Serial.print(F("A "));
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
  }
  else {
    Serial.print(F("- "));
  }
 /*
  if(btns & BTN_B)
    Serial.print(F("B "));
  else
    Serial.print(F("- "));
 
  if(btns & BTN_X)
    Serial.print(F("X "));
  else
    Serial.print(F("- "));
 
  if(btns & BTN_Y)
    Serial.print(F("Y "));
  else
    Serial.print(F("- "));
 
  if(btns & BTN_SELECT)
    Serial.print(F("SELECT "));
  else
    Serial.print(F("------ "));
 
  if(btns & BTN_START)
    Serial.print(F("START "));
  else
    Serial.print(F("----- "));
 
  if(btns & BTN_UP)
    Serial.print(F("UP "));
  else
    Serial.print(F("-- "));
 
  if(btns & BTN_DOWN)
    Serial.print(F("DOWN "));
  else
    Serial.print(F("---- "));
 
  if(btns & BTN_LEFT)
    Serial.print(F("LEFT "));
  else
    Serial.print(F("---- "));
 
  if(btns & BTN_RIGHT)
    Serial.print(F("RIGHT "));
  else
    Serial.print(F("----- "));
 
  if(btns & BTN_L)
    Serial.print(F("L "));
  else
    Serial.print(F("- "));
 
  if(btns & BTN_R)
    Serial.println(F("R"));
  else
    Serial.println(F("-"));
     */
  // Buttton debounce
  delay(25);
    

 // outputDisplay();
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

  byte indexRowArtificialIncrement = 0;
  byte indexColumnArtificialIncrement = 0;
  
  for(byte displayMatrixIndex = 0; displayMatrixIndex < quantityOfSingleMatrixDisplay; displayMatrixIndex++) {

      // This is a dirty trick to plot the correct part of our game matrix to each led display
      // Top left is matrix 0, top right matrix 1, bottom left matrix 2, bottom right matrix 3
      // 0 | 1
      // 2 | 3
      // Thus for matrix 0, we plot the ledmatrix from line 0, column 0
      // Thus for matrix 1, we plot the ledmatrix from line 0, column 16
      // Thus for matrix 2, we plot the ledmatrix from line 16, column 0
      // Thus for matrix 3, we plot the ledmatrix from line 16, column 16

      // So for the bottom two, the line counting should actually start from 16
      if(displayMatrixIndex > 1) {
        indexRowArtificialIncrement = singleMatrixDisplayNumberOfRows;
      }
      // And just by security, for the other two, it should still start counting at 0
      if(displayMatrixIndex <= 1) {
        indexRowArtificialIncrement = 0;
      }
      
      // And for the right two, the column counting should actually start from 16
      if(displayMatrixIndex == 1 || displayMatrixIndex == 3) {
        indexColumnArtificialIncrement = singleMatrixDisplayNumberOfColumns;
      }
      // And just by security, for the other two, it should still start counting at 0
      if(displayMatrixIndex == 0 || displayMatrixIndex == 2) {
        indexColumnArtificialIncrement = 0;
      }

    // Now we iterate of the four 16x16 displays, one by one
    for(byte rowIndex = 0; rowIndex < singleMatrixDisplayNumberOfRows; rowIndex++) {
      for(byte columnIndex = 0; columnIndex < singleMatrixDisplayNumberOfColumns; columnIndex++) {

        // We use our artificial increments to go read the correct quarter of our LED Matrix                
        // There's also a zigzag necessary because of the way the matrices are done
        // So we'll invert one column every two compared to our digital matrix
        // If we're on an even column, we're fine, everything is straightfoward
        
        if(columnIndex%2 == 1) {
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Black) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::Black;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == White) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::White;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Green) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::Green;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Blue) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::Blue;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Red) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::Red;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Purple) {leds[displayMatrixIndex][(columnIndex + 1)*singleMatrixDisplayNumberOfRows - rowIndex - 1] = CRGB::Purple;}
        }
        // If we're on an uneven column, we do a mathematical trick to invert it
        else if(columnIndex%2 == 0) {
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Black) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::Black;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == White) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::White;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Green) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::Green;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Blue) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::Blue;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Red) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::Red;}
          if(LEDMatrix[rowIndex + indexRowArtificialIncrement][columnIndex + indexColumnArtificialIncrement] == Purple) {leds[displayMatrixIndex][columnIndex*singleMatrixDisplayNumberOfColumns + rowIndex] = CRGB::Purple;}
        }
      }
    }
  }  
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

/** Retourne l'état de chaque bouton sous la forme d'un entier sur 16 bits. */
// For a given controller, which should be from 0 to 3 (so one of the four controllers)
uint16_t getSnesButtons(const byte buttonIndex) {
 
  /* 1 bouton = 1 bit */
  uint16_t value = 0;
 
  /* Capture de l'état courant des boutons */
  if(buttonIndex == 0) {
    digitalWrite(CONTROLLER_ONE_PIN_LATCH, HIGH);
    digitalWrite(CONTROLLER_ONE_PIN_LATCH, LOW);
  }
  if(buttonIndex == 1) {
    digitalWrite(CONTROLLER_TWO_PIN_LATCH, HIGH);
    digitalWrite(CONTROLLER_TWO_PIN_LATCH, LOW);
  }
  if(buttonIndex == 2) {
    digitalWrite(CONTROLLER_THREE_PIN_LATCH, HIGH);
    digitalWrite(CONTROLLER_THREE_PIN_LATCH, LOW);
  }
  if(buttonIndex == 3) {
    digitalWrite(CONTROLLER_FOUR_PIN_LATCH, HIGH);
    digitalWrite(CONTROLLER_FOUR_PIN_LATCH, LOW);
  }
 
  /* Récupère l'état de chaque bouton (12 bits + 4 bits à "1") */
  for(byte i = 0; i < 16; ++i) {

    
    if(buttonIndex == 0) {
      /* Lit l'état du bouton et décale le bit reçu pour former l'entier sur 16 bits final */
      value |= digitalRead(CONTROLLER_ONE_PIN_DATA) << i;
   
      /* Pulsation du signal d'horloge */
      digitalWrite(CONTROLLER_ONE_PIN_CLOCK, HIGH);
      digitalWrite(CONTROLLER_ONE_PIN_CLOCK, LOW);
    }
    if(buttonIndex == 1) {
      /* Lit l'état du bouton et décale le bit reçu pour former l'entier sur 16 bits final */
      value |= digitalRead(CONTROLLER_TWO_PIN_DATA) << i;
   
      /* Pulsation du signal d'horloge */
      digitalWrite(CONTROLLER_TWO_PIN_CLOCK, HIGH);
      digitalWrite(CONTROLLER_TWO_PIN_CLOCK, LOW);
    }
    if(buttonIndex == 2) {
      /* Lit l'état du bouton et décale le bit reçu pour former l'entier sur 16 bits final */
      value |= digitalRead(CONTROLLER_THREE_PIN_DATA) << i;
   
      /* Pulsation du signal d'horloge */
      digitalWrite(CONTROLLER_THREE_PIN_CLOCK, HIGH);
      digitalWrite(CONTROLLER_THREE_PIN_CLOCK, LOW);
    }
    if(buttonIndex == 3) {
      /* Lit l'état du bouton et décale le bit reçu pour former l'entier sur 16 bits final */
      value |= digitalRead(CONTROLLER_FOUR_PIN_DATA) << i;
   
      /* Pulsation du signal d'horloge */
      digitalWrite(CONTROLLER_FOUR_PIN_CLOCK, HIGH);
      digitalWrite(CONTROLLER_FOUR_PIN_CLOCK, LOW);
    }
  }
 
  /* Retourne le résultat sous une forme facile à manipuler (bouton appuyé = bit à "1") */
  return ~value;
}
