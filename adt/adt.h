#ifndef _wowlib_adt_adt_h
#define _wowlib_adt_adt_h

#include <vector>
#include <string>

#include "chunk.h"
#include "../utility.h"
#include "format.h"

class file;

namespace adt {
  // class map; (contains WDT data)

  class chunk; // chunk.h

  class tile {

  public:
    tile();
    tile(std::string, int, int);
    tile(int, int);
    ~tile();

    bool load(file&, ADT_FILETYPE);
    bool save(file&, ADT_FILETYPE);

    const adt::chunk& get_chunk(int) const;

    std::vector<std::string> map_object_names();
    std::vector<std::string> doodad_names();

  private:

    ADT_FILETYPE _loaded_files;
    std::string _name;

    int _x, _y;

    std::vector<std::string> _doodad_names;
    std::vector<std::string> _map_object_names;

    std::vector<SMODoodadDef> _v_doodads;
    std::vector<SMOMapObjDef> _v_map_objs;

    SMODoodadDef * _doodads;
    int _doodad_count;

    SMOMapObjDef * _map_objects;
    int _map_obj_count;

    chunk _chunk[16][16];
  };
}

#endif
