#ifndef __UTILS__
#define __UTILS__

#include <cstdint>

template <class T>
void int_to_raw(T val, char *buff) {
  for (auto i = 0u; i < sizeof(T); ++i) buff[i] = val << (i * 8);
}

std::uint32_t raw_to_int(char *buff, int bytes);

#endif
