#include "OTTO_WS2812B.hpp"

#include "common.hpp"
#include "leds.hpp"
#include "keys.hpp"

namespace otto_mcu {
  Keys keys;
}

using namespace otto_mcu;

void setup() {
  // Disable debug ports. Lets us use pins for key matrix.
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  Serial.begin(9600);
  delay(1000);
  log("USB SERIAL IS UP");


  leds.setup();
  keys.setup();
  log("Testing LEDs one by one");
  leds.test();
  log("Done testing LEDs.");
}

void loop() {
  keys.loop();
}
