#ifndef wdt_h
#define wdt_h

#include <string>
#include <vector>
#include "file/file.hpp"

#define WDT_SIZE 4096
#define IFF_WDTMAIN 'MAIN'
#define IFF_WDTWMO 'MWMO'

namespace wowlib {
class wdt {
public:
  std::vector<std::pair<int, int> > tiles_present;

public:
  wdt(file &f);
  ~wdt();
};
}

#endif
