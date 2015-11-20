#include "group.h"
#include "../file/file.h"

group::group(group_info &data)
    : _geometry(nullptr), _polygon_flags(nullptr), _loaded(false),
      _name(std::string("")) {

  _bounds0[0] = data.bb0[0];
  _bounds0[1] = data.bb0[1];
  _bounds0[2] = data.bb0[2];

  _bounds1[0] = data.bb1[0];
  _bounds1[1] = data.bb1[1];
  _bounds1[2] = data.bb1[2];

  _mogi_flags = data.flags;
}

group::group()
    : _geometry(nullptr), _polygon_flags(nullptr), _loaded(false),
      _name(std::string("")) {}

group::~group() {

  delete[] _geometry;
  delete[] _polygon_flags;
}

void group::load(file &f) {

  int token = 0, size = 0, version = 0;
  group_header *hdr = nullptr;

  if (!f.is_open()) {

    return;
  }

  f.seek_from_beg(0);

  f.read(&token, 4);
  f.read(&size, 4);
  f.read(&version, 4);

  if (token != 'MVER') {

    throw std::logic_error("");
  }

  f.read(&token, 4);
  f.read(&size, 4);

  if (token != WMO_GROUP) {

    throw std::logic_error("");
  }

  hdr = new group_header;
  f.read(hdr, sizeof(group_header));

  _name_idx = hdr->name_idx;
  _mogi_flags = hdr->flags;

  while (!f.eof()) {

    f.read(&token, 4);
    f.read(&size, 4);

    switch (token) {

    case GRP_VERTICES: {

      _geometry = (float *)new char[size];
      f.read(_geometry, size);

      break;
    }

    case GRP_MATINFO: {

      _polygon_flags = (poly_flags *)new char[size];
      f.read(_polygon_flags, size);

      break;
    }
    }
  }

  _loaded = true;
}

std::string group::name() const { return _name; }

void group::setName(std::string s) { _name = std::string(s); }
