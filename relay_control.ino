// Relay control.

const unsigned int RELAY1 = 1;
const unsigned int RELAY2 = 2;
const unsigned int RELAY3 = 3;
const unsigned int RELAY4 = 4;
const unsigned int RELAY5 = 5;
const unsigned int RELAY6 = 6;
const unsigned int RELAY7 = 7;
const unsigned int DELAY = 200;
 
void setup() {    
// Initialise the Arduino data pins for OUTPUT
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
}
 
void loop() {
  digitalWrite(RELAY1,LOW);
  delay(DELAY);
  digitalWrite(RELAY1,HIGH);

  digitalWrite(RELAY2,LOW);
  delay(DELAY);
  digitalWrite(RELAY2,HIGH);
 
  digitalWrite(RELAY3,LOW);
  delay(DELAY);
  digitalWrite(RELAY3,HIGH);

  digitalWrite(RELAY4,LOW);
  delay(DELAY);
  digitalWrite(RELAY4,HIGH);

  digitalWrite(RELAY5,LOW);
  delay(DELAY);
  digitalWrite(RELAY5,HIGH);

  digitalWrite(RELAY6,LOW);
  delay(DELAY);
  digitalWrite(RELAY6,HIGH);

  digitalWrite(RELAY7,LOW);
  delay(DELAY);
  digitalWrite(RELAY7,HIGH);
}
