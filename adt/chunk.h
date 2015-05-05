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
    chunk(int x, int y);

    ~chunk();

    void load(file&, int size, ADT_FILETYPE);

    void parse_header(SMChunkHeader * hdr);

    bool save(file &f, ADT_FILETYPE) const;

    float* raw_verts() const;

  private:
    float _px, _py, _pz;
    int _ix, _iy;

    int _area_id;
    SMChunkFlags _flags;
    uint32_t hole_flags;

    float* _raw_verts;

    std::vector<int> * _drefs;
    std::vector<int> * _wrefs;
  };
}

#endif
