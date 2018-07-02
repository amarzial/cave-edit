#include "file_editor.hpp"

#include <iostream>

int main(int ac, char* av[]) {
  if (ac < 2 or ac > 3) return 1;
  FileEditor savefile(av[1], ac == 2 ? 1 : std::stoi(av[2]));

  savefile.print_flags();
  savefile.print_player();

  return 0;
}
