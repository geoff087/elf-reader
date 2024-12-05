#pragma once

#include "elf-types.h"

class endian_converter {
public:
  endian_converter() {}

  void setup(unsigned char file_encoding) {
    if (file_encoding != get_host_encoding()) {
      _need_convert = true;
    } else {
      _need_convert = false;
    }
  }

  template<typename T>
  T operator()(T value) const {
    if (!_need_convert) return value;
    int iteration = sizeof(T);
    T ret = 0;
    while(iteration --) {
      ret = (ret << 8) | (value & 0xff);
      value >>= 8;
    }
    return ret;
  }

private:
  bool _need_convert;

  unsigned char get_host_encoding() const {
    static const int tmp = 1;
    if (*reinterpret_cast<const char *>(&tmp) == 1) {
      return ELFDATA2LSB;
    } else {
      return ELFDATA2MSB;
    }
  }
};