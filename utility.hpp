#ifndef _wowlib_utility_h
#define _wowlib_utility_h

#include <vector>
#include <string>

namespace utility {

void parse_strings(char *data, int size, std::vector<std::string> &strings);
std::string cc_as_str(int cc);
};

#endif
