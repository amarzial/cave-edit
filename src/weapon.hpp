#ifndef __WEAPON__
#define __WEAPON__

#include <string>
#include <vector>

namespace weapon {
struct WeaponElem {
  std::uint32_t id;
  std::string name;
};

std::string get_name(int id);
int get_id(const std::string);

const std::vector<WeaponElem>& list();
}

#endif
