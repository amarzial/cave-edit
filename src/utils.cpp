#include "utils.hpp"
void int_to_raw(std::uint32_t val, char *buff, int bytes) {
  for (auto i = 0; i < bytes; ++i) buff[i] = val << (i * 8);
}

std::uint32_t raw_to_int(char *buff, int bytes) {
  std::uint32_t val{};
  for (auto i = 0; i < bytes; ++i) {
    val <<= 8;
    val |= buff[bytes - 1 - i];
  }
  return val;
}
