#ifndef __UTILS__
#define __UTILS__

template <class T>
void int_to_raw(T val, char *buff) {
  for (auto i = 0u; i < sizeof(T); ++i) buff[i] = val << (i * 8);
}

template <class T>
T raw_to_int(char *buff) {
  T val{};
  for (auto i = 0u; i < sizeof(T); ++i) {
    val <<= 8;
    val |= buff[sizeof(T) - 1 - i];
  }
  return val;
}

#endif
