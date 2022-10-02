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
    std::cerr << "usage: " << argv[0] << " <wmo root filename>\n";
    return -1;
  }

  path basename = wmopath.stem();
  path directory = wmopath.parent_path();

  wmo object;
  object.load(local_file(wmopath.string()));

  int i = 0;
  for( group_itr g = object.first_group(); g != object.last_group(); ++g ) {
    std::cout << g->name() << '\t' << std::hex << g->flags() << '\n';
    path group_fn = directory / path(basename.string() + group_filename(i++));

    if (0) {
      local_file group_file(group_fn.string());
      object.load_group(i, group_file);
    }
  }

  return 0;
}
