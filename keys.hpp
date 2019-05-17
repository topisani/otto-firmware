#pragma once

#include "leds.hpp"

namespace otto_mcu {

  struct KeyDef {
    KeyDef(int code, const char* name, LEDId led) : code(code), name(name), led(led) {}

    uint8_t code;
    const char* name;
    LEDId led;
    bool state = false;
  };

  struct Keys {
    static constexpr int ncols = 7;
    static constexpr int nrows = 8;

    GPIOPin columns[ncols] = {{GPIOA, 9}, {GPIOC, 10}, {GPIOB, 5}, {GPIOA, 15},
                              {GPIOC, 0}, {GPIOC, 1},  {GPIOC, 3}};
    GPIOPin rows[nrows] = {{GPIOC, 11}, {GPIOC, 2}, {GPIOB, 4}, {GPIOA, 10},
                           {GPIOB, 3},  {GPIOD, 2}, {GPIOA, 8}, {GPIOC, 12}};

    KeyDef keys[ncols][nrows] = {{
                                   // Col 1
                                   {(2 << 6) | 0, "C1", {LEDGroup::channels, 0}},
                                   {(3 << 6) | 1, "S2", {LEDGroup::seq, 1}},
                                   {(3 << 6) | 2, "S3", {LEDGroup::seq, 2}},
                                   {(2 << 6) | 1, "C2", {LEDGroup::channels, 1}},
                                   {(3 << 6) | 3, "S4", {LEDGroup::seq, 3}},
                                   {(3 << 6) | 4, "S5", {LEDGroup::seq, 4}},
                                   {(2 << 6) | 2, "C3", {LEDGroup::channels, 2}},
                                   {(3 << 6) | 5, "S6", {LEDGroup::seq, 5}},
                                 },
                                 {
                                   // Col 2
                                   {(2 << 6) | 3, "C4", {LEDGroup::channels, 3}},
                                   {(3 << 6) | 6, "S7", {LEDGroup::seq, 6}},
                                   {(3 << 6) | 7, "S8", {LEDGroup::seq, 7}},
                                   {(2 << 6) | 4, "C5", {LEDGroup::channels, 4}},
                                   {(3 << 6) | 8, "S9", {LEDGroup::seq, 8}},
                                   {(3 << 6) | 9, "S10", {LEDGroup::seq, 9}},
                                   {(2 << 6) | 5, "C6", {LEDGroup::channels, 5}},
                                   {(2 << 6) | 6, "C7", {LEDGroup::channels, 6}},
                                 },
                                 {// Col 3
                                  {(2 << 6) | 7, "C8", {LEDGroup::channels, 7}},
                                  {(3 << 6) | 11, "S12", {LEDGroup::seq, 11}},
                                  {(3 << 6) | 12, "S13", {LEDGroup::seq, 12}},
                                  {(2 << 6) | 8, "C9", {LEDGroup::channels, 8}},
                                  {(3 << 6) | 13, "S14", {LEDGroup::seq, 13}},
                                  {(3 << 6) | 14, "S15", {LEDGroup::seq, 14}},
                                  {(2 << 6) | 9, "C10", {LEDGroup::channels, 9}},
                                  {(3 << 6) | 10, "S11", {LEDGroup::seq, 10}}},
                                 {
                                   // Col 4
                                   {(1 << 6) | 17, "SHIFT", {LEDGroup::funcs, 2}},
                                   {(1 << 6) | 1, "OCT+", {LEDGroup::funcs, 1}},
                                   {(1 << 6) | 2, "OCT-", {LEDGroup::funcs, 0}},
                                   {(3 << 6) | 0, "S1", {LEDGroup::seq, 0}},
                                   {(3 << 6) | 15, "S16", {LEDGroup::seq, 15}},
                                   {(1 << 6) | 20, "TWIST2", {LEDGroup::funcs, 16}},
                                   {(1 << 6) | 16, "EXT", {LEDGroup::funcs, 17}},
                                   {(1 << 6) | 12, "SETTINGS", {LEDGroup::funcs, 20}},
                                 },
                                 {// Col 5
                                  {(1 << 6) | 3, "SENDS", {LEDGroup::funcs, 3}},
                                  {(1 << 6) | 4, "ROUTING", {LEDGroup::funcs, 10}},
                                  {(1 << 6) | 7, "FX2", {LEDGroup::funcs, 9}},
                                  {(1 << 6) | 6, "FX1", {LEDGroup::funcs, 4}},
                                  {(1 << 6) | 13, "ARP", {LEDGroup::funcs, 8}},
                                  {(1 << 6) | 9, "LOOPER", {LEDGroup::funcs, 5}},
                                  {(1 << 6) | 11, "SAMPLER", {LEDGroup::funcs, 7}},
                                  {(1 << 6) | 10, "SEQ", {LEDGroup::funcs, 6}}},
                                 {// Col 6
                                  {-1, "INVALID C6:R1", {LEDGroup::funcs, 25}},
                                  {(1 << 6) | 5, "RECORD", {LEDGroup::funcs, 11}},
                                  {(1 << 6) | 0, "MASTER", {LEDGroup::funcs, 13}},
                                  {(1 << 6) | 8, "PLAY", {LEDGroup::funcs, 12}},
                                  {(1 << 6) | 18, "SLOTS", {LEDGroup::funcs, 14}},
                                  {(1 << 6) | 19, "TWIST1", {LEDGroup::funcs, 15}},
                                  {(1 << 6) | 15, "ENVELOPE", {LEDGroup::funcs, 18}},
                                  {(1 << 6) | 14, "SYNTH", {LEDGroup::funcs, 19}}},
                                 {
                                   // Col 7
                                   {(0 << 6) | 0, "BLUE CLICK", {LEDGroup::funcs, 25}},
                                   {(0 << 6) | 2, "YELLOW CLICK", {LEDGroup::funcs, 25}},
                                   {-1, "INVALID C7:R3", {LEDGroup::funcs, 25}},
                                   {(0 << 6) | 3, "RED CLICK", {LEDGroup::funcs, 25}},
                                   {-1, "INVALID C7:R5", {LEDGroup::funcs, 25}},
                                   {-1, "INVALID C7:R6", {LEDGroup::funcs, 25}},
                                   {(0 << 6) | 1, "GREEN CLICK", {LEDGroup::funcs, 25}},
                                   {-1, "INVALID C7:R8", {LEDGroup::funcs, 25}},
                                 }};

    void setup()
    {
      for (auto&& pin : rows) {
        pin.set_input();
      }
      for (auto&& pin : columns) {
        pin.set_output();
        pin.write(false);
      }
    }

    void loop()
    {
      for (int i = 0; i < ncols; i++) {
        auto& col = columns[i];
        col.write(true);
        for (int j = 0; j < nrows; j++) {
          auto& key = keys[i][j];
          bool old_val = key.state;
          bool new_val = (key.state = rows[j].read());
          if (new_val != old_val) {
            if (new_val) {
              log("DOWN: C%d:R%d %s", i + 1, j + 1, key.name);
              Serial.write(uint8_t{0x20});
              Serial.write(key.code);
              Serial.write('\n');
            } else {
              log("  UP: C%d:R%d %s", i + 1, j + 1, key.name);
              Serial.write(uint8_t{0x21});
              Serial.write(key.code);
              Serial.write('\n');
            }
          }
          leds.controler.setPixelColor(
            key.led, key.state ? WS2812B::Color(255, 0, 0) : WS2812B::Color(16, 16, 16));
        }
        col.write(false);
        delay(10);
      }
      leds.controler.show();
    }
  };
} // namespace otto_mcu
