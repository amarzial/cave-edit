#include "file_editor.hpp"

FileEditor::FileEditor(std::string filename)
    : m_file(filename, std::fstream::in | std::fstream::out) {
  if (!m_file) {
    throw "Error opening file";
  }
}
