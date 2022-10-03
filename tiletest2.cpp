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
  path map_path(argv[1]);
  
  std::string map_name(map_path.filename().string());
  
  std::string wdt_name(map_name + ".wdt");
  path wdt_path = map_path / wdt_name;

  local_file wdt_file(wdt_path.string());
  wowlib::wdt map(wdt_file);

  for (auto [x_index, y_index]: map.tiles_present) {
    tile t1(map_name, x_index, y_index);
    path base(filename(map_path, map_name, x_index, y_index, ADT_BASE_FILE));
    local_file t1_base(base.string());
    t1.load(t1_base, ADT_BASE_FILE);
    // break;
  }

  return (0);
}
