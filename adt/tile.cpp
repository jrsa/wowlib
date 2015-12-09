#include "tile.hpp"
#include "../file/file.hpp"
#include "../utility.hpp"

#include <glog/logging.h>

using namespace wowlib::adt;

tile::tile()
    : _name("blank tile"), _x(0), _y(0), _doodads(nullptr), _doodad_count(0),
      _map_objects(nullptr), _map_obj_count(0) {}

tile::tile(std::string name, int x, int y)
    : _name(name), _x(x), _y(y), _doodads(nullptr), _doodad_count(0),
      _map_objects(nullptr), _map_obj_count(0) {}

tile::~tile() {
  delete _doodads;

  // TODO: why is this broken (crashes with memory error here)
  // delete _map_objects;
}

void tile::load(file &f, ADT_FILETYPE type) {

  int magic = 0;
  int size = 0;
  char *buffer = 0;
  int version = 0;

  f.seek_from_beg(0);

  f.read(&magic, 4);
  f.read(&size, 4);
  f.read(&version, 4);

  if (!f.is_open()) {
    LOG(FATAL) << "tried to load tile from unopened file " << f.path();
  }

  if (magic != IFFC_VERSION || size != 0x4 || version != 0x12) {
    LOG(FATAL) << "invalid adt hdr: " << utility::cc_as_str(magic) << ", "
               << version;
  }

  while (true) {
    if (!f.read(&magic, 4)) {
      break;
    }

    f.read(&size, 4);

    LOG(INFO) << "found " << utility::cc_as_str(magic) << " with size " << size;

    switch (magic) {
    case IFF_A_MDXFILES:
      LOG(INFO) << "  loading..." << std::endl;

      buffer = new char[size];
      f.read(buffer, size);

      utility::parse_strings(buffer, size, _doodad_names);
      delete[] buffer;

      break;

    case IFF_A_WMOFILES:
      LOG(INFO) << "  loading..." << std::endl;
      buffer = new char[size];
      f.read(buffer, size);

      utility::parse_strings(buffer, size, _map_object_names);
      delete[] buffer;

      break;

    case IFF_A_DOODDEF:
      LOG(INFO) << "  loading..." << std::endl;
      _doodad_count = size / sizeof(SMODoodadDef);
      buffer = (char *)new SMODoodadDef[_doodad_count];
      f.read(buffer, size);
      _doodads = (SMODoodadDef *)buffer;

      break;

    case IFF_A_MAPOBJDEF:
      LOG(INFO) << "  loading..." << std::endl;
      buffer = (char *)new SMOMapObjDef[_map_obj_count];
      f.read(buffer, size);
      _map_obj_count = size / sizeof(SMOMapObjDef);
      _map_objects = (SMOMapObjDef *)buffer;

      break;

    case IFF_A_CHUNK:
      LOG(INFO) << "  loading chunks..." << std::endl;
      for (int i = 0; i < 255; ++i) {
        _chunks.push_back(chunk(f, size, type));
        f.read(&magic, 4);
        f.read(&size, 4);
      }

      f.read(&magic, 4);
      f.read(&size, 4);

      break;

    default:

      f.seek_from_current(size);
      break;
    }
  }
  _loaded_files_mask = (ADT_FILETYPE)(_loaded_files_mask | type);
}

void tile::save(file &f, ADT_FILETYPE type) {
  if (!f.is_open()) {
    LOG(ERROR) << "tried to save tile to an unopened file " << f.path();
  }

  int magic = IFFC_VERSION;
  int size = 0x4;
  int version = 0x12;

  f.write((char *)&magic, 4);
  f.write((char *)&size, 4);
  f.write((char *)&version, 4);

  if (type == ADT_OBJ_FILE) {
    LOG(FATAL) << "obj file saving nyi";

    // todo: saving obj
    //  * filenames
    //  * id's
    //  * entries
  }

  if (type == ADT_BASE_FILE) {
    // todo:
    // * tex
    // * water

    for (int i = 0; i < 255; i++) {
      _chunks[i].save(f, ADT_BASE_FILE);
    }
    // todo: mfbo
  }
}

std::vector<chunk>::iterator tile::first_chunk() { return _chunks.begin(); }

std::vector<chunk>::iterator tile::last_chunk() { return _chunks.end(); }

std::vector<std::string> tile::map_object_names() { return _map_object_names; }

std::vector<std::string> tile::doodad_names() { return _doodad_names; }
