#include "utility.h"

using namespace std;

void utility::parse_strings(char *data, int size, vector<string> &strings) {

  int i = 0;
  while (i < size) {
    string current = string(data + i);

    if (current.length() > 0) {
      strings.push_back(current);
      i += current.length() + 1;
    } else {
      i++;
    }
  }
}

string utility::cc_as_str(int cc) {
  static char x[5] = {'\0','\0','\0','\0','\0'};
  memcpy(x, &cc, 4);
  return string(x, 4);
}