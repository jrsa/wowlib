#ifndef _wowlib_adt_chunk_h
#define _wowlib_adt_chunk_h

#include <vector>

#include "../utility.h"
#include "format.h"

class file;

namespace adt {

  class chunk {
  public:

    chunk();
    chunk(file&, int size, ADT_FILETYPE);

    void load(file&, int size, ADT_FILETYPE);
    void parse_header(SMChunkHeader * hdr);
    bool save(file &f, ADT_FILETYPE) const;

  private:
    float _px, _py, _pz;
    int _ix, _iy;

    int _area_id;
    SMChunkFlags _flags;
    uint32_t _hole_flags;

    std::vector<vertex> _vertices;

    vertex vert_from_heightmap_entry(float h, int idx);
  };
}

#endif
