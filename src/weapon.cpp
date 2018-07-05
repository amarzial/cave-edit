#include "weapon.hpp"

namespace weapon {
const std::vector<WeaponElem>& list() {
  static std::vector<WeaponElem> s_list = {
#include "weapon_ids.hpp"
  };
  return s_list;
}

std::string get_name(unsigned int id) {
  auto l = list();
  for (const auto& w : l) {
    if (w.id == id) {
      return w.name;
    }
  }
  return "";
}
int get_id(const std::string);
}
