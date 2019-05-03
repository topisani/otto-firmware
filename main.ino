#include <WS2812B.h>

#include "common.hpp"
#include "leds.hpp"
#include "keys.hpp"

Keys keys;

void setup() {
  Serial.begin(9600);
  delay(1000);
  log("USB SERIAL IS UP");


  leds.setup();
  keys.setup();
  log("Testing LEDs one by one");
  //leds.test();
  log("Done testing LEDs.");
}

void loop() {
  keys.loop();
}
