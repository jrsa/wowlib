#include <iostream>

#include "utility.h"
#include "adt/adt.h"
#include "file/local_file.h"

int main(int argc, char const *argv[])
{
  // std::string maps_dir ("/Users/jrsa/Desktop/test files/world/maps");
  std::string map_name ("Azeroth");
  int x_index(32), y_index(48);

  adt::tile t1 (map_name, x_index, y_index);

  local_file t1_base ("../test files/Azeroth_32_48.adt");
  local_file t1_obj ("../test files/Azeroth_32_48_obj0.adt");

  try
  {
    t1.load (t1_base, ADT_BASE_FILE);
    t1.load (t1_obj, ADT_OBJ_FILE);
  }
  catch (std::runtime_error e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
