#ifndef __FILE_EDITOR__
#define __FILE_EDITOR__
#include <string>

struct FlagInfo {
  int offset;
  char bit;
  std::string description;
  bool status;
};

class FileEditor {
  std::vector<FlagInfo> m_flags;
  std::fstream m_file;

 public:
  FileEditor(std::string filename);

  void set_flag(int id, bool active);
  bool get_flag(int id);

  void save();
}
#endif
