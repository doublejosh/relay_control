/**
 * Relay control of lights.
 */

boolean DEBUG = false;

// Pin and status storage.
unsigned int RELAYS[][2] = {
  {2, 1},
  {3, 1},
  {4, 1},
  {5, 1},
  {6, 1},
  {7, 1},
  {8, 1},
  {9, 1}
};
int array_size = 8;

// Flicker.
int flicker_delay = 100;
const unsigned int CHANCE_BACK_ON = 3;
const unsigned int CHANCE_OFF = 25;
int current_light = 1;

// Strobe.
int strobe_cycle = 333;

// Rotate.
int rotate_cycle = 1000;
int rotate_position = 1;

/**
 * Setup.
 */
void setup() {
  randomSeed(analogRead(0));
  // Initialise the Arduino data pins for output.
  for (int i = 1; i < array_size; i++) {
    pinMode(RELAYS[i][0], OUTPUT);
    digitalWrite(RELAYS[i][0], LOW);
  }
  if (DEBUG) {
    Serial.begin(9600);
  }
}

/**
 * Go.
 */
void loop() { 
  flicker();
  //strobe();
  //rotate();
}

void rotate() {
  for (int i = 1; i < array_size; i++) {
    if (i == rotate_position) {
      digitalWrite(RELAYS[i][0], LOW);
    }
    else {
      digitalWrite(RELAYS[i][0], HIGH);
    }
  }
  if (rotate_position < array_size) {
    rotate_position++;
  }
  else {
    rotate_position = 1;
  }
  delay(rotate_cycle / array_size);
}

/**
 * Just flash.
 */
void strobe() {
  int off_delay = strobe_cycle - 50;
  for (int i = 1; i < array_size; i++) {
    digitalWrite(RELAYS[i][0], HIGH);
  }
  delay(strobe_cycle);
  for (int i = 1; i < array_size; i++) {
    digitalWrite(RELAYS[i][0], LOW);
  }
  delay(50);
}

/**
 * Simulate old lightbulb.
 */
void flicker() {
  for (int i = 1; i < array_size; i++) {
    if (DEBUG) {
      Serial.print(i);
      Serial.print(":");
      Serial.print(RELAYS[i][1]);
      Serial.print(":");
    }

    if (RELAYS[i][1] == 1) {
      if (random(CHANCE_OFF) == 1) {
        if (DEBUG) {
          Serial.print("OFF");
        }
        digitalWrite(RELAYS[i][0], HIGH);
        RELAYS[i][1] = 0;
      }
      else {
        if (DEBUG) {
          Serial.print("   ");
        }
      }
    }
    else {      
      if (random(CHANCE_BACK_ON) == 1) {
        if (DEBUG) {
          Serial.print("ON ");
        }
        digitalWrite(RELAYS[i][0], LOW);
        RELAYS[i][1] = 1;
      }
      else {
        if (DEBUG) {
          Serial.print("   ");
        }
      }
    }
    if (DEBUG) {
      Serial.print("    ");
    }
  }
  if (DEBUG) {
    Serial.println("");
  }
  delay(flicker_delay);
}

