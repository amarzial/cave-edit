#include "file_editor.hpp"
#include "utils.hpp"

#include <fstream>
#include <string>

FileEditor::FileEditor(const std::string& filename)
    : m_file(filename, std::fstream::in | std::fstream::out) {
  if (!m_file) {
    throw "Error opening file";
  }
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
  auto get_val = [this](auto& val, int offset) {
    m_file.seekg(offset);
    char buff[sizeof(val)];
    m_file.read(buff, sizeof(val));
    val = raw_to_int<std::remove_reference<decltype(val)>>(buff);
  };

  get_val(m_player.current_health, PlayerInfo::offset::e_current_health);
  get_val(m_player.whimsical_stars, PlayerInfo::offset::e_whimsical_stars);
  get_val(m_player.maximum_health, PlayerInfo::offset::e_max_health);
}
