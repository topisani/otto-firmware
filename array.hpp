#pragma once

#include <initializer_list>

#define FWD(x) static_cast<decltype(x)>(x)

namespace otto_mcu {
  namespace util {

    template<typename T, size_t N>
    struct array {
      using value_type = T;
      using iterator = T*;
      using const_iterator = const T*;
      static size_t size()
      {
        return N;
      }

      T& operator[](size_t i)
      {
        return data_[i];
      }

      const T& operator[](size_t i) const
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


    template<typename T, size_t Capacity>
    struct local_vector {
      using value_type = T;
      using iterator = typename array<T, Capacity>::iterator;
      using const_iterator = typename array<T, Capacity>::const_iterator;

      local_vector() : _data(), _size(0) {}
      local_vector(std::initializer_list<value_type> il) : _data(il), _size(il.size()) {}

      // Queries

      static constexpr size_t capacity() noexcept
      {
        return Capacity;
      }

      size_t size() const noexcept
      {
        return _size;
      }

      iterator begin()
      {
        return _data.begin();
      }

      const_iterator begin() const
      {
        return _data.begin();
      }

      iterator end()
      {
        return _data.begin() + _size;
      }

      const_iterator end() const
      {
        return _data.begin() + _size;
      }

      value_type& front()
      {
        return _data.front();
      }

      const value_type& front() const
      {
        return _data.front();
      }

      value_type& back()
      {
        return _data[_size - 1];
      }

      const value_type& back() const
      {
        return _data[_size - 1];
      }

      const value_type& operator[](size_t idx) const
      {
        return _data[idx];
      }

      value_type& operator[](size_t idx)
      {
        return _data[idx];
      }

      value_type& push_back(value_type v)
      {
        _data[_size] = v;
        _size += 1;
        return back();
      }

      void pop_back()
      {
        _size -= 1;
      }

      void clear()
      {
        _size = 0;
      }

      value_type* data()
      {
        return _data.begin();
      }

      const value_type* data() const
      {
        return _data.begin();
      }

    private:
      array<value_type, capacity()> _data;
      size_t _size;
    };

    template<typename Cont, typename T>
    void fill(Cont&& c, T&& t)
    {
      for (auto&& e : FWD(c)) {
        e = t;
      }
    }

  } // namespace util
} // namespace otto_mcu
