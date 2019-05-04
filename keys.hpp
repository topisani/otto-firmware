#pragma once

#include "leds.hpp"

namespace otto_mcu {

  struct KeyDef {
    KeyDef(const char* name, LEDId led) : name(name), led(led) {}

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
                                   {
                                     "C1",
                                     {LEDGroup::channels, 0},
                                   },
                                   {"S2", {LEDGroup::seq, 1}},
                                   {"S3", {LEDGroup::seq, 2}},
                                   {"C2", {LEDGroup::channels, 1}},
                                   {"S4", {LEDGroup::seq, 3}},
                                   {"S5", {LEDGroup::seq, 4}},
                                   {"C3", {LEDGroup::channels, 2}},
                                   {"S6", {LEDGroup::seq, 5}},
                                 },
                                 {
                                   // Col 2
                                   {"C4", {LEDGroup::channels, 3}},
                                   {"S7", {LEDGroup::seq, 6}},
                                   {"S8", {LEDGroup::seq, 7}},
                                   {"C5", {LEDGroup::channels, 4}},
                                   {"S9", {LEDGroup::seq, 8}},
                                   {"S10", {LEDGroup::seq, 9}},
                                   {"C6", {LEDGroup::channels, 5}},
                                   {"C7", {LEDGroup::channels, 6}},
                                 },
                                 {// Col 3
                                  {"C8", {LEDGroup::channels, 7}},
                                  {"S12", {LEDGroup::seq, 11}},
                                  {"S13", {LEDGroup::seq, 12}},
                                  {"C9", {LEDGroup::channels, 8}},
                                  {"S14", {LEDGroup::seq, 13}},
                                  {"S15", {LEDGroup::seq, 14}},
                                  {"C10", {LEDGroup::channels, 9}},
                                  {"S11", {LEDGroup::seq, 10}}},
                                 {
                                   // Col 4
                                   {"SHIFT", {LEDGroup::funcs, 2}},
                                   {"OCT+", {LEDGroup::funcs, 1}},
                                   {"OCT-", {LEDGroup::funcs, 0}},
                                   {"S1", {LEDGroup::seq, 0}},
                                   {"S16", {LEDGroup::seq, 15}},
                                   {"TWIST2", {LEDGroup::funcs, 16}},
                                   {"EXT", {LEDGroup::funcs, 17}},
                                   {"SETTINGS", {LEDGroup::funcs, 20}},
                                 },
                                 {// Col 5
                                  {"SENDS", {LEDGroup::funcs, 3}},
                                  {"ROUTING", {LEDGroup::funcs, 10}},
                                  {"FX2", {LEDGroup::funcs, 9}},
                                  {"FX1", {LEDGroup::funcs, 4}},
                                  {"ARP", {LEDGroup::funcs, 8}},
                                  {"LOOPER", {LEDGroup::funcs, 5}},
                                  {"SAMPLER", {LEDGroup::funcs, 7}},
                                  {"SEQ", {LEDGroup::funcs, 6}}},
                                 {// Col 6
                                  {"INVALID C6:R1", {LEDGroup::funcs, 25}},
                                  {"RECORD", {LEDGroup::funcs, 11}},
                                  {"VOLUME", {LEDGroup::funcs, 13}},
                                  {"PLAY", {LEDGroup::funcs, 12}},
                                  {"SLOTS", {LEDGroup::funcs, 14}},
                                  {"TWIST1", {LEDGroup::funcs, 15}},
                                  {"ENVELOPE", {LEDGroup::funcs, 18}},
                                  {"SYNTH", {LEDGroup::funcs, 19}}},
                                 {
                                   // Col 7
                                   {"BLUE CLICK", {LEDGroup::funcs, 25}},
                                   {"YELLOW CLICK", {LEDGroup::funcs, 25}},
                                   {"INVALID C7:R3", {LEDGroup::funcs, 25}},
                                   {"RED CLICK", {LEDGroup::funcs, 25}},
                                   {"INVALID C7:R5", {LEDGroup::funcs, 25}},
                                   {"INVALID C7:R6", {LEDGroup::funcs, 25}},
                                   {"GREEN CLICK", {LEDGroup::funcs, 25}},
                                   {"INVALID C7:R8", {LEDGroup::funcs, 25}},
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
            } else {
              log("  UP: C%d:R%d %s", i + 1, j + 1, key.name);
            }
          }
          leds.controler.setPixelColor(key.led,
                             key.state ? WS2812B::Color(255, 0, 255) : WS2812B::Color(0, 0, 0));
        }
        col.write(false);
      }
      leds.controler.show();
      delay(10);
    }
  };
} // namespace otto_mcu
