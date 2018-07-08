#include "flag.hpp"

namespace flag {
const std::vector<FlagElem>& list() {
  static std::vector<FlagElem> s_list = {
#include "flag_data.hpp"
  };
  return s_list;
}
}
