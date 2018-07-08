#include "file_editor.hpp"
#include "flag.hpp"
#include "utils.hpp"
#include "weapon.hpp"

#include <fstream>
#include <string>

FileEditor::FileEditor(const std::string& filename, int profile)
    : m_file(filename, std::fstream::in | std::fstream::out),
      m_save_slot(profile),
      m_modified(false) {
  if (profile < 1 or profile > 3) {
    throw "Trying to load a profile out of range 1-3";
  }
  if (!m_file) {
    throw "Error opening file";
  }

  load_profile();
}

FileEditor::~FileEditor() { m_file.close(); }

void FileEditor::set_flag(unsigned int id, bool active) {
  auto flist = flag::list();
  if (id >= flist.size()) {
    throw "Trying to access an invalid flag";
    return;
  }
  const auto& finfo = flist[id];
  auto& flag = m_flags[finfo.offset - Player::offset::e_flags];
  if (active) {
    flag.data |= 1 << finfo.bit;
  } else {
    flag.data &= ~(1 << finfo.bit);
  }
  flag.changed = true;
}

bool FileEditor::get_flag(unsigned int id) {
  auto flist = flag::list();
  if (id >= flist.size()) {
    throw "Trying to access an invalid flag";
    return false;
  }
  bool f;
  const auto& finfo = flist[id];
  f = m_flags[finfo.offset - Player::offset::e_flags].data & (1 << finfo.bit);
  return f;
}

void FileEditor::load_profile() {
  int profile_offset = (m_save_slot - 1) * Player::offset::e_profile;

  auto get_val = [this, profile_offset](std::uint32_t& val, int offset,
                                        int size) {
    m_file.seekg(offset + profile_offset);
    char buff[sizeof(val)];
    m_file.read(buff, sizeof(val));
    val = raw_to_int(buff, size);
  };

  get_val(m_player.current_health, Player::offset::e_current_health, 2);
  get_val(m_player.whimsical_stars, Player::offset::e_whimsical_stars, 2);
  get_val(m_player.maximum_health, Player::offset::e_max_health, 2);

  std::uint32_t offset = Player::offset::e_weapons;
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

  offset = Player::offset::e_inventory;
  for (auto& itm : m_player.inventory) {
    get_val(itm, offset, 4);
    offset += 4;
  }

  m_file.seekg(Player::offset::e_flags + profile_offset);
  for (auto& flag : m_flags) {
    char byte;
    m_file.read(&byte, 1);
    flag.data = byte;
    flag.changed = false;
  }
}

void FileEditor::print_player() {
  std::cout << "Player info:\nHealth: " << m_player.current_health << "/"
            << m_player.maximum_health
            << "\nWhimsical stars: " << m_player.whimsical_stars << "\n";
  std::cout << "Weapons:\n";
  for (auto& w : m_player.weapons) {
    if (w.id) {
      std::cout << weapon::get_name(w.id) << " (id: " << w.id
                << ")\n  level: " << w.level << "\n  energy: " << w.level
                << "\n  ammo: " << w.current_ammo << "/" << w.max_ammo << "\n";
    }
  }
}

void FileEditor::print_flags() {
  const auto& flist = flag::list();

  for (const auto flag : flist) {
    auto f =
        m_flags[flag.offset - Player::offset::e_flags].data & (1 << flag.bit);
    std::cout << flag.description << " = " << (f ? "true" : "false") << "\n";
  }
}

void FileEditor::save() {
  int profile_offset = (m_save_slot - 1) * Player::offset::e_profile;

  if (m_modified) {
    auto store_val = [this, profile_offset](std::int32_t val, int offset,
                                            int size) {
      char buff[4];
      int_to_raw(val, buff, size);
      m_file.seekg(offset + profile_offset);
      m_file.write(buff, size);
    };
    store_val(m_player.current_health, Player::offset::e_current_health, 2);
    store_val(m_player.maximum_health, Player::offset::e_max_health, 2);
    store_val(m_player.whimsical_stars, Player::offset::e_whimsical_stars, 2);
    for (auto i = 0u; i < m_flags.size(); ++i) {
      if (m_flags[i].changed) {
        m_file.seekg(i + Player::offset::e_flags + profile_offset);
        m_file.write(&(m_flags[i].data), 1);
      }
    }
    m_file.flush();
  }
}
