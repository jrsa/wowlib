#include <iostream>
#include <string>
#include <sstream>

#include "utility.h"
#include "adt/adt.h"
#include "file/local_file.h"

using namespace std;

string filename(string dir, string name, int x, int y, ADT_FILETYPE type) {
  stringstream result;
  string typetoken;

  switch (type) {
  case ADT_BASE_FILE:
    typetoken = string("");
  case ADT_OBJ_FILE:
    typetoken = string("_obj0");
  }

  result << dir << name << "_" << x << "_" << y << typetoken << ".adt";
  return result.str();
}

int main(int argc, char const *argv[]) {
  string maps_dir("../data/wowassets/wotlk/World/Maps/");
  string map_name("Azeroth");
  int x_index(32), y_index(48);

  wowlib::adt::tile t1(map_name, x_index, y_index);

  local_file t1_base(
      filename(maps_dir, map_name, x_index, y_index, ADT_BASE_FILE));
  local_file t1_obj(
      filename(maps_dir, map_name, x_index, y_index, ADT_OBJ_FILE));

  try {
    t1.load(t1_base, ADT_BASE_FILE);
    t1.load(t1_obj, ADT_OBJ_FILE);
  } catch (runtime_error e) {
    cerr << "error: " << e.what() << endl;
  }

  return 0;
}
