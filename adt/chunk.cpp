#include <iostream>
#include <map>
#include <glog/logging.h>

#include "../file/file.hpp"
#include "chunk.hpp"

namespace wowlib {
void adt::chunk::parse_header(SMChunkHeader *hdr) {

  if (!hdr) {
    return;
  }

  _ix = hdr->idx_x;
  _iy = hdr->idx_y;
  _px = hdr->x;
  _py = hdr->y;
  _pz = hdr->z;

  _hole_flags = hdr->holes;
  _flags = hdr->flags;
  _area_id = hdr->area_id;
}

adt::chunk::chunk() {}

adt::chunk::chunk(std::vector<char> data, ADT_FILETYPE type) { load(data, type); }

void adt::chunk::load(std::vector<char> data, ADT_FILETYPE type) {

  int sub_magic = 0;
  int sub_size = 0;

  std::vector<int> doodad_ids;
  std::vector<int> object_ids;

  // XXX just make this a data member of the chunk class, i believe tileDocument does exactly that
  // the "parsing" is just copying individual fields of the header into class data members
  SMChunkHeader* header = (SMChunkHeader*) &data[0];
  if (type == ADT_BASE_FILE) {
    parse_header(header);
  }

  // i straight copied this from adt::tile::load, should maybe make a
  // std::multimap< uint32_t, std::vector<char> > parse_iff_chunks (std::vector<char>) function somewhere

  std::multimap< uint32_t, std::vector<char> > sub_chunks;
  std::map < uint32_t, uint32_t > size_overrides {
    { 'MCNR', 448 },
    { 'MCLQ', header->size_mclq },
    { 'MCAL', header->alpha_size },
  };
  
  // TODO: for obj0/tex0 files, skip the header
  size_t sub_chunk_offset = sizeof(SMChunkHeader);
  while (sub_chunk_offset < data.size())
  {
    uint32_t token = * (uint32_t*) &data[sub_chunk_offset];
    uint32_t sub_chunk_size = * (uint32_t*) &data[sub_chunk_offset + 4];

    if ((sub_chunk_offset + sub_chunk_size) > data.size())
      break;

    if (auto el = size_overrides.find(token); el != size_overrides.end())
      sub_chunk_size = el->second;

    sub_chunks.insert({token, std::vector<char> (&data[sub_chunk_offset + 8], &data[sub_chunk_offset + sub_chunk_size + 8])});
    sub_chunk_offset += (sub_chunk_size + 8);
  }

  for (auto& [iff_token, data] : sub_chunks) {
    // std::cout << "MCNK subchunk: " << utility::cc_as_str(iff_token) << ", size: " << data.size() << "b" <<'\n';

    switch (sub_magic) {

    case IFF_C_DREF: {
      doodad_ids = std::vector<int>(&data[0], &data[data.size()]);
      break;
    }
    case IFF_C_WREF: {
      object_ids = std::vector<int>(&data[0], &data[data.size()]);
      break;
    }

    case IFF_C_VERTS: {
      _vertices = std::vector<float>(&data[0], &data[C_VERT_COUNT * 4]);
      break;
    }
    /*
    case IFF_C_NORMs: {
      f.seek_from_current(448);
      break;
    }
    */
    default: {
      break;
    }
    }
  }
}

void adt::chunk::save(file &f, ADT_FILETYPE type) const {
  LOG(FATAL) << "adt::chunk::save nyi";

  // write header
  // write subchunks
}
}
