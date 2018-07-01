#include "file_editor.hpp"

#include <iostream>

int main(int ac, char* av[]) {
  if (ac != 2) return 1;
  FileEditor savefile(av[1]);

  for (auto& flag : savefile.flag_list()) {
    std::cout << flag.description << " = " << (flag.status ? "true" : "false")
              << "\n";
  }

  

  return 0;
}
