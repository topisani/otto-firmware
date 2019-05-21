#pragma once

#include "common.hpp"

namespace otto_mcu {

  //  struct LEDStrip {
  //    LEDStrip(GPIOPin pin, int count) : cs_pin(pin), count(count) {}
  //
  //    void setup()
  //    {
  //      cs_pin.set_output(true);
  //    }
  //
  //    void colorWipe(uint32_t c, uint8_t wait)
  //    {
  //      for (uint16_t i = 0; i < strip.numPixels(); i++) {
  //        strip.setPixelColor(i, c);
  //        strip.show();
  //        delay(wait);
  //      }
  //    }
  //
  //    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
  //    {
  //      return ((uint32_t) g << 16) | ((uint32_t) r << 8) | b;
  //    }
  //
  //    int count = 0;
  //    GPIOPin cs_pin;
  //    WS2812B& strip = ws2812b_global;
  //    ;
  //  };


  struct LEDColor {
    LEDColor(uint32_t rgb) : r((rgb >> 16) & 0xFF), g((rgb >> 8) & 0xFF), b(rgb & 0xFF){};
    LEDColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    operator uint32_t() {
      return r << 16 | g << 8 | b;
    }

    uint8_t r = 0, g = 0, b = 0;
  };

  struct Leds {
    void setup()
    {
      controler.begin();
      controler.setBrightness(255);
      controler.show();
    }

    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos)
    {
      if (WheelPos < 85) {
        return WS2812B::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      } else {
        if (WheelPos < 170) {
          WheelPos -= 85;
          return WS2812B::Color(255 - WheelPos * 3, 0, WheelPos * 3);
        } else {
          WheelPos -= 170;
          return WS2812B::Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
      }
    }

    void rainbow()
    {
      //      uint16_t i, j;
      //
      //      for (j = 0; j < 256; j++) {
      //        auto set_cols = [&](WS2812B& strip) {
      //          for (i = 0; i < strip.numPixels(); i++) {
      //            strip.setPixelColor(i, Wheel(j));
      //          }
      //          strip.show();
      //        };
      //        set_cols(funcs().strip);
      //        set_cols(channels().strip);
      //        set_cols(seq().strip);
      //        delay(5);
      //      }
    }

    void test()
    {
      auto step_through = [&](WS2812B::Group& group) {
        for (int i = 0; i < group.numPixels(); i++) {
          group.clear();
          group.setPixelColor(i, 255, 0, 0);
          group.show(controler);
          delay(250);
        }
        group.clear();
        group.show(controler);
      };
      step_through(controler.group(LEDGroup::funcs));
      step_through(controler.group(LEDGroup::channels));
      step_through(controler.group(LEDGroup::seq));
    }

    void loop()
    {
      controler.show();
    }

    WS2812B controler = {{{GPIOA, 4}, 21}, {{GPIOC, 4}, 10}, {{GPIOC, 5}, 16}};

  } leds;

} // namespace otto_mcu
