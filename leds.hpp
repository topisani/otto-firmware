#pragma once

#include "common.hpp"

WS2812B ws2812b_global = {21};

struct LEDStrip {
  LEDStrip(GPIOPin pin, int count) : cs_pin(pin), count(count) {}

  void setup() { cs_pin.set_output(true); }

  void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }

  static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
  }

  int count = 0;
  GPIOPin cs_pin;
  WS2812B &strip = ws2812b_global;
  ;
};

struct Leds {
  void setup() {
    for (auto &&strip : {&seq_, &channels_, &funcs_}) {
      strip->setup();
    }
    funcs().strip.begin();
    ws2812b_global.setBrightness(255);
    funcs().strip.show();
    channels().strip.show();
    seq().strip.show();
  }

  void select(LEDStrip &in_strip) {
    if (&in_strip == current_) return;
    delay(1);
    for (auto &strip : {seq_, channels_, funcs_}) {
      strip.cs_pin.write(true);
    }
    in_strip.strip.updateLength(in_strip.count);
    ws2812b_global.clear();
    in_strip.cs_pin.write(false);
    current_ = &in_strip;
  }

  LEDStrip &funcs() {
    select(funcs_);
    return funcs_;
  }

  LEDStrip &channels() {
    select(channels_);
    return channels_;
  }

  LEDStrip &seq() {
    select(seq_);
    return seq_;
  }

  void setPixelColor(LEDId led, uint32_t color = LEDStrip::Color(255, 0, 255)) {
    if (led.strip != LEDGroup::funcs) return;
    auto& strip = [&] () -> LEDStrip& {
      switch (led.strip) {
      case LEDGroup::funcs: return funcs();
      case LEDGroup::channels: return channels();
      case LEDGroup::seq: return seq(); 
      default: return funcs();
    }
    }();
    strip.strip.setPixelColor(led.number, color);
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos) {
    if (WheelPos < 85) {
      return ws2812b_global.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else {
      if (WheelPos < 170) {
        WheelPos -= 85;
        return ws2812b_global.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      } else {
        WheelPos -= 170;
        return ws2812b_global.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
    }
  }

  void rainbow() {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
      auto set_cols = [&](WS2812B &strip) {
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(j));
        }
        strip.show();
      };
      set_cols(funcs().strip);
      set_cols(channels().strip);
      set_cols(seq().strip);
      delay(5);
    }
  }

  void test() {
    auto step_through = [&](WS2812B &strip) {
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.clear();
        strip.setPixelColor(i, LEDStrip::Color(255, 0, 0));
        strip.show();
        delay(250);
      }
      strip.clear();
      strip.show();
    };
    step_through(funcs().strip);
    step_through(channels().strip);
    step_through(seq().strip);
  }

  LEDStrip funcs_ = {{GPIOA, 4}, 21};
  LEDStrip seq_ = {{GPIOC, 5}, 16};
  LEDStrip channels_ = {{GPIOC, 4}, 10};
  LEDStrip* current_ = &funcs_;
} leds;
