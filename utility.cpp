#include "utility.h"

void utility::parse_strings(char *data, int size,
                            std::vector<std::string> &strings) {

  int i = 0;

  while (i < size) {

    std::string current = std::string(data + i);

    if (current.length() > 0) {

      strings.push_back(current);
      i += current.length() + 1;
    } else
      i++;
  }
}
