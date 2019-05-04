#pragma once

namespace otto_mcu {
  namespace util {

    template<typename T, uint16_t N>
    struct array {
      static uint16_t size()
      {
        return N;
      }

      T& operator[](uint16_t i)
      {
        return data_[i];
      }

      const T& operator[](uint16_t i) const
      {
        return data_[i];
      }

      T* begin()
      {
        return data_;
      }

      T* end()
      {
        return data_ + N;
      }

      const T* begin() const
      {
        return data_;
      }

      const T* end() const
      {
        return data_ + N;
      }

      T data_[N];
    };
  } // namespace util
} // namespace otto_mcu
