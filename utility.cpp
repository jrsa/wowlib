#include "utility.hpp"

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
  char x[5] = {0,};

  for (int i = 0; i <= 3; i++)
    x[i] = (cc >> ((3 - i) * 8)) & 0xff;

  return string(x);
}
