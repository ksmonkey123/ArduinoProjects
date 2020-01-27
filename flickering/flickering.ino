#define PIN_HIGH 2
#define PIN_LOW 1
#define PIN_INPUT 3
#define PIN_ANALOG A2 // = PB4

/*
 * SIMULATES A FLICKERING CANDLE (ATTINY13)
 * 
 *                 R1
 *   Lamp +---+--\/\/\/--+---+   >--------+ GND
 *            |          |    \ / 
 *            +---+   >--+    --- Q1
 *                 \ /         |
 *                 --- Q2      +--/\/\/\--+ PB1
 *                  |
 *                  +-------------/\/\/\--+ PB2
 * 
 * The circuit works with an NPN transistor (Q1) enabling the lamp through
 * a resistor (R1) and a second transistor (Q2) in parallel with the resistor
 * that varies the brightness.
 *
 *  -> PB3 is an active-high input (default - active)
 *  -> PB2 drives the transistor Q1. PB2 is on whenever PB3 is high.
 *  -> PB1 drives the transistor Q2. PB1 producing randomised signals between 2.5 and 500Hz
 *  -> A2 is an unconnected analog pin used to generate the seed on startup
 */

void setup() {
  pinMode(PIN_INPUT, INPUT_PULLUP);
  pinMode(PIN_HIGH, OUTPUT);
  pinMode(PIN_LOW, OUTPUT);
  
  randomSeed(analogRead(PIN_ANALOG));
}

boolean high = false;

void loop() {
  if (digitalRead(PIN_INPUT)) {
    digitalWrite(PIN_LOW, true);
    digitalWrite(PIN_HIGH, high);
    high = !high;
    // wait a random time between 1 and 200 milliseconds
    delay(1 + random(200));
  } else {
    digitalWrite(PIN_LOW, false);
    digitalWrite(PIN_HIGH, false);
    delay(20);
  }
}
