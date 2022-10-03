#ifndef _wowlib_adt_chunk_h
#define _wowlib_adt_chunk_h

#include <vector>

#include "../utility.hpp"
#include "format.h"

class file;

namespace wowlib {
namespace adt {
class chunk {
public:
  chunk();
  chunk(std::vector<char>, ADT_FILETYPE);

  void load(const std::vector<char> &, ADT_FILETYPE);
  void parse_header(SMChunkHeader *hdr);
  void save(file &f, ADT_FILETYPE) const;

private:
  float _px, _py, _pz;
  int _ix, _iy;

  int _area_id;
  SMChunkFlags _flags;
  uint32_t _hole_flags;

  std::vector<float> _vertices;
};
}
}

#endif
