#include <string>
#include <glog/logging.h>
#include <boost/filesystem.hpp>

#include "wmo/wmo.hpp"
#include "file/local_file.hpp"

#include <iostream>

using namespace boost::filesystem;

int main(int argc, char const *argv[]) {

  FLAGS_log_dir = "./wmotest_logs/";
  google::InitGoogleLogging(argv[0]);

  path wmopath;
  if (argc == 2) {
    wmopath = path(argv[1]);
  } else {
    wmopath =
        path("/Volumes/data/wow/wowassets/wotlk/World/wmo/Azeroth/Buildings/Stormwind/Stormwind.wmo");
        // path("/Users/jrsa/wow/wowassets/wotlk/World/wmo/Dungeon/AZ_Karazahn/Kharazan.wmo");
  }


  std::string basename = wmopath.stem().string();

  local_file root_file( wmopath.string() );
  wmo object;

  object.load( root_file );

  int i = 0;
  for( group_itr g = object.first_group(); g != object.last_group(); ++g ) {
    std::cout << g->name() << " loaded, flags: " << g->flags() << ", ";
    std::cout << basename << group_filename(i++) << std::endl;
  }

  return 0;
}
