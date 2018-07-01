#ifndef __FILE_EDITOR__
#define __FILE_EDITOR__
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct FlagInfo {
  int offset;
  char bit;
  std::string description;
  bool status;
  bool changed;

  FlagInfo(int off, char b, const std::string& s)
      : offset(off), bit(b), description(s), status(false), changed(false) {}
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
    e_inventory = 0xd8
  };
  std::uint16_t current_health;
  std::uint16_t maximum_health;
  std::uint16_t whimsical_stars;
  std::array<Weapon, 5> weapons;
  std::array<std::uint32_t, 24> inventory;
};

class FileEditor {
  std::vector<FlagInfo> m_flags;
  std::fstream m_file;
  PlayerInfo m_player;

  void load_player();

 public:
  FileEditor(const std::string& filename);

  void set_flag(int id, bool active);
  bool get_flag(int id);
  const std::vector<FlagInfo>& flag_list() { return m_flags; }

  void print_player() {
    std::cout << "Player info:\nHealth: " << m_player.current_health << "/"
              << m_player.maximum_health
              << "\nWhimsical stars: " << m_player.whimsical_stars << "\n";
  }

  void save();
};
#endif
