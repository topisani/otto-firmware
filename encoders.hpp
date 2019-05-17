#pragma once

#include "common.hpp"

namespace otto_mcu {

  struct Encoder {
    GPIOPin pin_a;
    GPIOPin pin_b;
    volatile int value = 0;
    volatile bool fired = false;

    Encoder(GPIOPin a, GPIOPin b) : pin_a(a), pin_b(b) {}

    void setup()
    {
      pin_a.set_input(HIGH);
      pin_b.set_input(HIGH);
      attachInterrupt(
        pin_a.board_pin_number,
        [](void* self) { static_cast<Encoder*>(self)->interrupt_routine(); }, this, RISING);
    }

    void interrupt_routine()
    {
      bool a = pin_a.read();
      bool b = pin_b.read();

      if (a && !b) {
        value++;
      } else if (a &&  b) {
        value--;
      }
      fired = true;
    }
  };

  struct Encoders {
    Encoder blue = {{GPIOC, 6}, {GPIOC, 8}};
    Encoder green = {{GPIOC, 7}, {GPIOB, 14}};
    Encoder yellow = {{GPIOA, 3}, {GPIOA, 2}};
    Encoder red = {{GPIOA, 1}, {GPIOA, 0}};

    void setup()
    {
      blue.setup();
      green.setup();
      yellow.setup();
      red.setup();
    }

    void loop()
    {
      handle(blue, 0x30, "BLUE");
      handle(green, 0x31, "GREEN");
      handle(yellow, 0x32, "YELLOW");
      handle(red, 0x33, "RED");
    }

    void handle(Encoder& e, uint8_t code, const char* name) {
      if (e.fired) {
        auto value = e.value;
        e.value = 0;
        //log("%s: %d", name, value);
        Serial.write(code);
        Serial.write(value);
        Serial.write('\n');
        e.fired = false;
      }
    }
  };
} // namespace otto_mcu
