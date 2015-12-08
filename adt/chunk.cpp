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

adt::chunk::chunk(file &f, int size, ADT_FILETYPE type) { load(f, size, type); }

void adt::chunk::load(file &f, int size, ADT_FILETYPE type) {

  int sub_magic = 0;
  int sub_size = 0;
  int sub_idx = 0;

  std::vector<int> doodad_ids;
  std::vector<int> object_ids;

  if (type == ADT_BASE_FILE) {
    SMChunkHeader *header = new SMChunkHeader;
    f.read((char *)header, sizeof(SMChunkHeader));
    parse_header(header);

    sub_idx += sizeof(SMChunkHeader);

    delete header;
  }

  while (sub_idx < size) {
    f.read(&sub_magic, 4);
    f.read(&sub_size, 4);
    sub_idx += (sub_size + 8);

    LOG(INFO) << "found " << utility::cc_as_str(sub_magic) << " with size "
              << sub_size << " at offset " << sub_idx << " into chunk " << _ix
              << ", " << _iy;

    switch (sub_magic) {
    case IFF_A_CHUNK: {
      LOG(FATAL) << "read past end of MCNK: " << sub_idx << "/" << size;
    }
    case IFF_C_DREF: {
      int dref_count = sub_size / 4;
      int *i_drefs = new int[dref_count];
      f.read((char *)i_drefs, 4 * dref_count);
      doodad_ids = std::vector<int>(i_drefs, &i_drefs[dref_count]);
      delete[] i_drefs;
      break;
    }
    case IFF_C_WREF: {
      int wref_count = sub_size / 4;
      int *i_wrefs = new int[wref_count];
      f.read((char *)i_wrefs, 4 * wref_count);
      object_ids = std::vector<int>(i_wrefs, &i_wrefs[wref_count]);
      delete[] i_wrefs;
      break;
    }

    case IFF_C_VERTS: {
      float *heightmap = new float[C_VERT_COUNT];
      f.read((char *)heightmap, 4 * C_VERT_COUNT);

      _vertices = std::vector<float>(heightmap, &heightmap[C_VERT_COUNT]);

      delete[] heightmap;
      break;
    }
    case IFF_C_NORMs: {
      f.seek_from_current(448);
      sub_idx += 13;
      break;
    }
    default: {

      f.seek_from_current(sub_size);
      break;
    }
    }
  }
}

void adt::chunk::save(file &f, ADT_FILETYPE type) const {
  LOG(FATAL) << "adt::chunk::save nyi";
}
}
