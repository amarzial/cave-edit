#ifndef __FILE_EDITOR__
#define __FILE_EDITOR__

#include "utils.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct FlagByte {
  char data;
  bool changed;
};

struct Weapon {
  std::uint32_t id;
  std::uint32_t level;
  std::uint32_t energy;
  std::uint32_t max_ammo;
  std::uint32_t current_ammo;
};

struct PlayerInfo {
  enum offset : int {
    e_max_health = 0x1c,
    e_whimsical_stars = 0x1e,
    e_current_health = 0x20,
    e_weapons = 0x38,
    e_inventory = 0xd8,
    e_flags = 0x21c,
    e_flags_end = 0x603,
    e_profile = 0x620
  };
  std::uint32_t current_health;
  std::uint32_t maximum_health;
  std::uint32_t whimsical_stars;
  std::array<Weapon, 6> weapons;
  std::array<std::uint32_t, 24> inventory;
};

class FileEditor {
  std::array<FlagByte,
             PlayerInfo::offset::e_flags_end - PlayerInfo::offset::e_flags>
      m_flags;
  std::fstream m_file;
  int m_save_slot;
  PlayerInfo m_player;
  bool m_modified;

  void load_profile();

 public:
  FileEditor(const std::string& filename, int profile = 1);

  void set_flag(int id, bool active);
  bool get_flag(int id);

  void print_player();
  void print_flags();

  void save();
};
#endif
