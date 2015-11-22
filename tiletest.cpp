#include <glog/logging.h>
#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include "adt/adt.h"
#include "adt/filename.h"
#include "file/local_file.h"

using namespace wowlib::adt;
using namespace boost::filesystem;

int main(int argc, char const *argv[]) {
  google::InitGoogleLogging(argv[0]);

  std::string map_name("PVPZone05");
  int x_index(26);
  int y_index(25);

  tile t1(map_name, x_index, y_index);

  path mappath;
  if (argc == 2) {
    mappath = path(argv[1]);
  } else {
    mappath = path("../data/wowassets/wotlk/World/Maps/");
  }

  path base(filename(mappath, map_name, x_index, y_index, ADT_BASE_FILE));
  local_file t1_base(base.string());
  t1.load(t1_base, ADT_BASE_FILE);
  return (0);
}
