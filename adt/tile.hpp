#ifndef _wowlib_adt_adt_h
#define _wowlib_adt_adt_h

#include <vector>
#include <string>

#include "chunk.hpp"
#include "format.h"

class file;

namespace wowlib {
namespace adt {
class tile {
public:
  tile();
  tile(std::string, int, int);
  tile(int, int);
  ~tile();

  void load(file &, ADT_FILETYPE);
  void save(file &, ADT_FILETYPE);

  std::vector<chunk>::iterator first_chunk();
  std::vector<chunk>::iterator last_chunk();

  std::vector<std::string> map_object_names();
  std::vector<std::string> doodad_names();

  std::vector<std::string>::iterator begin_doodad_name();
  std::vector<std::string>::iterator end_doodad_name();

  std::vector<std::string>::iterator begin_object_name();
  std::vector<std::string>::iterator end_object_name();


private:
  ADT_FILETYPE _loaded_files_mask;
  std::string _name;

  int _x, _y;

  std::vector<std::string> _doodad_names;
  std::vector<std::string> _map_object_names;

  std::vector<SMODoodadDef> _v_doodads;
  std::vector<SMOMapObjDef> _v_map_objs;

  std::vector<chunk> _chunks;

  SMODoodadDef *_doodads;
  int _doodad_count;

  SMOMapObjDef *_map_objects;
  int _map_obj_count;
};
}
}
#endif
