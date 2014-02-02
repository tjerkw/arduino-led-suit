#include <IRremote.h> // note conflicts with Tone.cpp, update IRRemoteInt.h to use a different timer pin
#include <Adafruit_NeoPixel.h>
#include "constants.h"
#include "ledfacade.h"
#include "runner.h"
#include "controller.h"

// runs all the tickets
Runner runner = Runner();
// controlls the led suit using ir-remote
IRrecv irrecv(IR_PIN);
Controller controller = Controller();
// needed to control the leds
LedFacade leds = LedFacade();


// button effects
ButtonClickEffect change_effect = ButtonClickEffect();
ResetEffect reset_effect = ResetEffect();
Strobo strobo = Strobo();

// effects
Effect* effects[] = {
  &strobo,
  new RandomFill(),
  new FunctionEffect(&glowRed),
  new FunctionEffect(&colorFade)
  //new FunctionEffect(&glowColors),
  //new FunctionEffect(&colorWheelFull),
  //new FunctionEffect(&colorWheelHighRes),
  //new FunctionEffect(&colorWheel2)
};
int num_effects = 2;

void play_tone(int freq, int duration) {
  tone(BUZZER, freq, duration); // 100ms
}

void setup() {
  // for std out
  Serial.begin(9600);
  //leds.begin();
  Serial.println("setup");
  play_tone(1000, 300);
  play_tone(2000, 500);
  leds.begin();
  irrecv.enableIRIn(); 
}

void loop() {
  Serial.println("looping");
  runner.loop();
}
