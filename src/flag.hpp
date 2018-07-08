#ifndef __FLAG__
#define __FLAG__

#include <vector>
#include <string>

namespace flag {
struct FlagElem {
  int offset;
  char bit;
  std::string description;
};

const std::vector<FlagElem>& list();
}

#endif
