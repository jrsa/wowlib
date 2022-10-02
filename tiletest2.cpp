#include <string>
#include <iostream>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include "wdt.hpp"
#include "adt/tile.hpp"
#include "adt/filename.hpp"
#include "file/local_file.hpp"

using namespace wowlib::adt;
using namespace boost::filesystem;

int main(int argc, char const *argv[]) {
  path mappath("/Volumes/data/wow/wowassets/vanilla/World/Maps/Azeroth");
  path wdtpath(mappath);
  
  std::string map_name(mappath.filename().string());
  
  std::string wdtname(map_name + ".wdt");
  wdtpath /= wdtname;

  local_file wdtfile(wdtpath.string());
  wowlib::wdt map(wdtfile);

  for (auto [x_index, y_index]: map.tiles_present) {
    tile t1(map_name, x_index, y_index);
    path base(filename(mappath, map_name, x_index, y_index, ADT_BASE_FILE));
    local_file t1_base(base.string());
    t1.load(t1_base, ADT_BASE_FILE);
  }

  return (0);
}
