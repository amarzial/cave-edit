#ifndef __UTILS__
#define __UTILS__

#include <cstdint>

void int_to_raw(std::uint32_t val, char *buff, int bytes);
std::uint32_t raw_to_int(char *buff, int bytes);

#endif
