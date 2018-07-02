#ifndef __FLAG__
#define __FLAG__

#include <vector>

namespace flag {
struct FlagElem {
  int offset;
  char bit;
  std::string description;
};

const std::vector<FlagElem>& list() {
  static std::vector<FlagElem> s_list = {
#include "flag_data.hpp"
  };
  return s_list;
}
}

#endif
