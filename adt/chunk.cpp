#include "../file/file.h"
#include "chunk.h"

// todo: for debug only
#include <iostream>

adt::chunk::chunk(): _drefs(nullptr), _wrefs(nullptr), _raw_verts(nullptr) {
  // todo: for debug only
  std::cout << "new chunk created" << std::endl;
}

adt::chunk::~chunk() {

  if(_drefs)
  {
    delete _drefs;
  }

  if(_wrefs)
  {
    delete _wrefs;
  }

  if(_raw_verts)
  {
    delete[] _raw_verts;
  }
}

void adt::chunk::parse_header(SMChunkHeader *hdr) {

  if(!hdr) {

    return;
  }

  _ix = hdr->idx_x;
  _iy = hdr->idx_y;
  _px = hdr->x;
  _py = hdr->y;
  _pz = hdr->z;

  hole_flags = hdr->holes;
  _flags = hdr->flags;
  _area_id = hdr->area_id;
}

void adt::chunk::load(file &f, int size, ADT_FILETYPE type) {

  int sub_magic = 0;
  int sub_size = 0;
  int sub_idx = 0;

  if(type == ADT_BASE_FILE) {

    SMChunkHeader * header = new SMChunkHeader;
    f.read((char *)header, sizeof(SMChunkHeader));
    parse_header(header);
    sub_idx += sizeof(SMChunkHeader);
  }

  while(sub_idx < size) {

    f.read(&sub_magic, 4);
    f.read(&sub_size, 4);

    sub_idx += (sub_size + 8);

    switch(sub_magic) {

      case IFF_A_CHUNK: {

        throw new std::runtime_error("adt file misread");
        break;
      }

      case IFF_C_DREF: {

        int dref_count = sub_size / 4;

        int *i_drefs = new int[dref_count];
        f.read((char *)i_drefs, 4 * dref_count);

        _drefs = new std::vector<int>(i_drefs, &i_drefs[dref_count]);

        break;
      }

      case IFF_C_WREF: {

        int wref_count = sub_size / 4;

        int *i_wrefs = new int[wref_count];
        f.read((char *)i_wrefs, 4 * wref_count);

        _wrefs = new std::vector<int>(i_wrefs, &i_wrefs[wref_count]);

        break;
      }

      case IFF_C_VERTS: {

        _raw_verts = new float[C_VERT_COUNT];
        f.read((char *)_raw_verts, 4 * C_VERT_COUNT);

        break;
      }


      default: {

        f.seek_from_current(sub_size);
        break;
      }
    }
  }
}

bool adt::chunk::save(file &f, ADT_FILETYPE type) const {

  return true;
}


float* adt::chunk::raw_verts() const {

  return _raw_verts;
}

