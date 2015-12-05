#ifndef wdt_h
#define wdt_h

#include <string>
#include <vector>
#include "file/file.h"

#define WDT_SIZE 4096
#define IFF_WDTMAIN 'MAIN'

namespace wowlib {
class wdt {
private:
  std::vector<std::pair<int, int> > tiles_present;

public:
  wdt(file &f);
  ~wdt();
};
}

#endif