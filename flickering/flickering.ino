#define PIN_HIGH 3
#define PIN_LOW 4
#define PIN_INPUT 1
#define PIN_ANALOG A1 // = PB2

/*
 * SIMULATES A FLICKERING CANDLE (ATTINY13)
 * 
 *                 R1
 *   Lamp +---+--\/\/\/--+---+ > +--------+ GND
 *            |          |   |___|
 *            +---+ > +--+    --- Q1
 *                |___|        |
 *                 --- Q2      +----------+ PB4
 *                  |
 *                  +---------------------+ PB3
 * 
 * The circuit works with an NMOS transistor (Q1) enabling the lamp through
 * a resistor (R1) and a second transistor (Q2) in parallel with the resistor
 * that varies the brightness.
 *
 *  -> PB1 is an active-high input (default - active)
 *  -> PB4 drives the transistor Q1. PB4 is on whenever PB4 is high.
 *  -> PB3 drives the transistor Q2. PB3 producing randomised signals between 2.5 and 500Hz
 *  -> A1 is an unconnected analog pin used to generate the seed on startup
 */

void setup() {
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_HIGH, OUTPUT);
  pinMode(PIN_LOW, OUTPUT);
  delay(10);
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
