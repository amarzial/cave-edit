#include "file_editor.hpp"
#include "utils.hpp"

#include <fstream>
#include <string>

FileEditor::FileEditor(const std::string& filename)
    : m_file(filename, std::fstream::in | std::fstream::out) {
  if (!m_file) {
    throw "Error opening file";
  }

  load_player();

  m_flags = std::vector<FlagInfo>{
#include "flag_data.hpp"
  };
  for (auto& flag : m_flags) {
    m_file.seekg(flag.offset);
    char byte;
    m_file.read(&byte, 1);
    flag.status = (byte & (1 << flag.bit));
  }
}

void FileEditor::set_flag(int id, bool active) {
  if (id < 0 or id > m_flags.size()) {
    throw "Trying to access an invalid flag";
    return;
  }
  m_flags[id].status = active;
  m_flags[id].changed = true;
}

bool FileEditor::get_flag(int id) {
  if (id < 0 or id > m_flags.size()) {
    throw "Trying to access an invalid flag";
    return false;
  }
  return m_flags[id].status;
}

void FileEditor::load_player() {
  auto get_val = [this](std::uint32_t& val, int offset, int size) {
    m_file.seekg(offset);
    char buff[sizeof(val)];
    m_file.read(buff, sizeof(val));
    val = raw_to_int(buff, size);
  };

  get_val(m_player.current_health, PlayerInfo::offset::e_current_health, 2);
  get_val(m_player.whimsical_stars, PlayerInfo::offset::e_whimsical_stars, 2);
  get_val(m_player.maximum_health, PlayerInfo::offset::e_max_health, 2);

  std::uint32_t offset = PlayerInfo::offset::e_weapons;
  for (auto& w : m_player.weapons) {
    get_val(w.id, offset, 4);
    offset += 4;
    get_val(w.level, offset, 4);
    offset += 4;
    get_val(w.energy, offset, 4);
    offset += 4;
    get_val(w.max_ammo, offset, 4);
    offset += 4;
    get_val(w.current_ammo, offset, 4);
    offset += 4;
  }

  offset = PlayerInfo::offset::e_inventory;
  for (auto& itm : m_player.inventory) {
    get_val(itm, offset, 4);
    offset += 4;
  }
}

void FileEditor::print_player() {
  std::cout << "Player info:\nHealth: " << m_player.current_health << "/"
  << m_player.maximum_health
  << "\nWhimsical stars: " << m_player.whimsical_stars << "\n";
}
