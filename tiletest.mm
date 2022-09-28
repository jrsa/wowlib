//#include <Cocoa/Cocoa.h>

#include <glog/logging.h>
#include <string>
#include <iostream>

#include <nanobench.h>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include "wdt.hpp"
#include "adt/tile.hpp"
#include "adt/filename.hpp"
#include "file/local_file.hpp"

using namespace wowlib::adt;
using namespace boost::filesystem;

int main(int argc, char const *argv[]) {
  FLAGS_log_dir = ".";
  google::InitGoogleLogging(argv[0]);

//  NSOpenPanel* panel = [NSOpenPanel openPanel];
//
//  panel.message = @"select a map folder";
//  panel.canChooseDirectories = YES;
//  panel.canChooseFiles = NO;
//  [panel runModal];
//
//  path mappath(panel.URLs[0].fileSystemRepresentation);
  path mappath("/Volumes/data/wow/wowassets/vanilla/World/Maps/EmeraldDream");
  path wdtpath(mappath);
  
  std::string map_name(mappath.filename().string());
  
  std::string wdtname(map_name + ".wdt");
  wdtpath /= wdtname;

  // load wdt lol
  // check if terrain exists
  local_file wdtfile(wdtpath.string());
  wowlib::wdt map(wdtfile);

  auto i = map.tiles_present.begin();

  ankerl::nanobench::Bench().epochs(map.tiles_present.size()).run("load all tiles", [&] {
    
    auto [x_index, y_index] = *i++;
    // auto [x_index, y_index] = map.tiles_present[i];
      tile t1(map_name, x_index, y_index);
      path base(filename(mappath, map_name, x_index, y_index, ADT_BASE_FILE));
      local_file t1_base(base.string());
      t1.load(t1_base, ADT_BASE_FILE);

      // for (auto &name: t1._doodad_names)
      //   std::cout << name << '\n';

  });

  return (0);
}
