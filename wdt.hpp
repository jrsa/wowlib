#ifndef wdt_h
#define wdt_h

#include <string>
#include <vector>
#include "file/file.hpp"

#define WDT_SIZE 4096
#define IFF_WDTMAIN 'MAIN'

namespace wowlib {
class wdt {
private:
  std::vector<std::pair<int, int> > _tiles_present;

public:
  wdt(file &f);
  ~wdt();
    
  bool check_tile(int x, int y);

  std::vector<std::pair<int, int> >::iterator tiles_present();

  //std::vector<std::pair<int, int> >::iterator tiles_present();
};
}

#endif
