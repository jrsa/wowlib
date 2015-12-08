#include <string>
#include <glog/logging.h>
#include <boost/filesystem.hpp>

#include "wmo/wmo.h"

using namespace boost::filesystem;

int main(int argc, char const *argv[]) {

  FLAGS_log_dir = "./wmotest_logs/";
  google::InitGoogleLogging(argv[0]);

  path wmopath;
  if (argc == 2) {
    wmopath = path(argv[1]);
  } else {
    wmopath =
        path("../data/wowassets/wotlk/World/wmo/Azeroth/Buildings/NSabbey/");
  }

  // get the name of a wmo as input (w default for testing)

  return 0;
}