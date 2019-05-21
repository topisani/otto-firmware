#include "OTTO_WS2812B.hpp"

#include "common.hpp"
#include "encoders.hpp"
#include "keys.hpp"
#include "leds.hpp"
#include "serial.hpp"

namespace otto_mcu {
  SerCom serial;
  Keys keys;
  Encoders encoders;
} // namespace otto_mcu

using namespace otto_mcu;

void setup()
{
  // Disable debug ports. Lets us use pins for key matrix.
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);


  serial.setup();

  leds.setup();
  keys.setup();
  encoders.setup();
  log("Testing LEDs one by one");
  // leds.test();
  log("Done testing LEDs.");
}

enum Command : uint8_t {
  debug_message = 0x23,
  request_alive = 0x0A,
  respond_alive = 0x0B,
  clear_all_leds = 0xE0,
  clear_led_group = 0xE1,
  set_led_color = 0xEC,
  request_key_dump = 0x2A,
  key_down = 0x20,
  key_up = 0x21,
  respond_key_dump = 0x2B,
  blue_enc_step = 0x30,
  green_enc_step = 0x31,
  yellow_enc_step = 0x32,
  red_enc_step = 0x33
};

void msg_handler(const SerCom::Message& msg)
{
  auto cmd = msg[0];
  switch (static_cast<Command>(cmd)) {
  case Command::request_alive:
    Serial.write(Command::respond_alive);
    Serial.write('\n');
    break;
  case Command::clear_all_leds: {
    LEDColor c = {msg[1], msg[2], msg[3]};
    leds.controler.clear();
  } break;
  case Command::set_led_color: {
    auto* key = keys.get_key(msg[1]);
    if (key == nullptr) {
      log("unknown key %d", key);
      return;
    }
    LEDColor c = {msg[2], msg[3], msg[4]};
    leds.controler.setPixelColor(key->led, c);
  } break;
  default:
    log("[ECHO] %s", msg.data());
  }
}

void loop()
{
  serial.loop(msg_handler);
  keys.loop();
  encoders.loop();
  leds.loop();
}
