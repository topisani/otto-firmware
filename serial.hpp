#pragma once

#include "array.hpp"

namespace otto_mcu {

  struct SerCom {
    using Message = util::local_vector<uint8_t, 128>;
    void setup()
    {
      Serial.begin(9600);
      delay(1000);
      log("USB SERIAL IS UP");
    };

    template<typename Handler>
    void loop(Handler&& h)
    {
      int res = -1;
      while ((res = Serial.read()) != -1 && res != '\n') {
        next_msg.push_back(res);
      }
      *next_msg.end() = 0;
      if (next_msg.size() > 0) {
        h(next_msg);
      }
      next_msg.clear();
      if (res == '\n') loop(FWD(h));
    };

    Message next_msg;
  };

} // namespace otto_mcu
