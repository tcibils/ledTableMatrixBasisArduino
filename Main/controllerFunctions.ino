
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



// Updating the input from all players
void checkAllButtons() {
  for(byte playerIndex=0; playerIndex < NUMBER_PLAYERS; playerIndex++) {
    checkButtons(playerIndex);
  }
}

// Stored as follows: UP - RIGHT - DOWN - LEFT - START - SELECT - A - B - X - Y - L - R
void checkButtons(const byte playerID) {

    static uint16_t oldBtns = 0;      // Anciennes valeurs des boutons
    uint16_t btns = getSnesButtons(playerID); // Valeurs actuelles des boutons
  
    if(btns & NO_GAMEPAD) {
      Serial.println(F("No gamepad connected"));
      return;
    }

    if   (btns & BTN_UP)   {playerButtonPushed[playerID][0] = 1;}
    else                   {playerButtonPushed[playerID][0] = 0;}
    
    if   (btns & BTN_RIGHT){playerButtonPushed[playerID][1] = 1;}
    else                   {playerButtonPushed[playerID][1] = 0;}
    
    if   (btns & BTN_DOWN) {playerButtonPushed[playerID][2] = 1;}
    else                   {playerButtonPushed[playerID][2] = 0;}
    
    if   (btns & BTN_LEFT) {playerButtonPushed[playerID][3] = 1;}
    else                   {playerButtonPushed[playerID][3] = 0;}

    
    if(btns & BTN_START)   {playerButtonPushed[playerID][4] = 1;}
    else                   {playerButtonPushed[playerID][4] = 0;}
   
    if(btns & BTN_SELECT)  {playerButtonPushed[playerID][5] = 1;}
    else                   {playerButtonPushed[playerID][5] = 0;}
    

    if(btns & BTN_A)       {playerButtonPushed[playerID][6] = 1;}
    else                   {playerButtonPushed[playerID][6] = 0;}

    if(btns & BTN_B)       {playerButtonPushed[playerID][7] = 1;}
    else                   {playerButtonPushed[playerID][7] = 0;}
    
    if(btns & BTN_X)       {playerButtonPushed[playerID][8] = 1;}
    else                   {playerButtonPushed[playerID][8] = 0;}
    
    if(btns & BTN_Y)       {playerButtonPushed[playerID][9] = 1;}
    else                   {playerButtonPushed[playerID][9] = 0;}
        
    
    if(btns & BTN_L)       {playerButtonPushed[playerID][10] = 1;}
    else                   {playerButtonPushed[playerID][10] = 0;}
    
    if(btns & BTN_R)       {playerButtonPushed[playerID][11] = 1;}
    else                   {playerButtonPushed[playerID][11] = 0;}
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
