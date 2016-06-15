/**
 * Relay control of lights.
 */

boolean DEBUG = false;

// Pin and status storage.
unsigned int RELAYS[][2] = {
  {4, 1},
  {5, 1},
  {6, 1},
  {7, 1},
  {8, 1},
  {9, 1},
  {10, 1},
  {11, 1}
};
int array_size = 8;

boolean START_OFF = 1;

// Lightning.
const unsigned int LIGHTNING_DELAY = 50;
const unsigned int LIGHTNING_CHANCE = 2; // Out of 10000.
const unsigned int LIGHTNING_CHANCE_BOOST = 250; // Increase while active.
boolean LIGHTNING_ACTIVE = 0;
boolean LIGHTNING_CALM = 1;

// Flicker (simulate old lightbulb).
int flicker_delay = 300;
const unsigned int CHANCE_BACK_ON = 3;
const unsigned int CHANCE_OFF = 45;
int current_light = 1;

// Strobe (just flash).
int strobe_cycle = 333;

// Rotate.
int rotate_cycle = 1000;
int rotate_position = 1;


/**
 * Setup.
 */
void setup () {
  randomSeed(analogRead(0));
  // Initialise the Arduino data pins for output.
  for (int i = 1; i < array_size; i++) {
    pinMode(RELAYS[i][0], OUTPUT);
    if (START_OFF) {
      digitalWrite(RELAYS[i][0], LOW);
    }
    else {
      digitalWrite(RELAYS[i][0], HIGH);
    }
    
  }
  if (DEBUG) {
    Serial.begin(9600);
  }
}


/**
 * Go.
 */
void loop () {
  lightning();
  //flicker();
  //strobe();
  //rotate();
}


/**
 * Rotate bulbs.
 */
void rotate () {
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
void strobe () {
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
 * Like a cloud in a storm.
 */
void lightning () {
  int chance = LIGHTNING_CHANCE;
  boolean anyOn = false;

  // Turn off all lights.
  for (int i = 0; i < array_size; i++) {
    digitalWrite(RELAYS[i][0], HIGH);

    // Increase chances for clusters.
    if (LIGHTNING_ACTIVE) {
      chance = LIGHTNING_CHANCE + LIGHTNING_CHANCE_BOOST;
    }
    else {
      chance = LIGHTNING_CHANCE;
    }

    // Determine if flashing.
    if (random(0, 1000) < chance) {
      // Pick a bulb.
      int bulb = random(1, array_size);
      // Switch it on and keep track.
      digitalWrite(RELAYS[bulb][0], LOW);
      LIGHTNING_ACTIVE = 1;
      anyOn = true;
    }
  }
  
  if (!anyOn) {
    LIGHTNING_ACTIVE = 0;
  }

  delay(LIGHTNING_DELAY);
}


/**
 * Simulate old lightbulb.
 */
void flicker () {
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

