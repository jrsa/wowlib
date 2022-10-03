#include "tile.hpp"
#include "../file/file.hpp"
#include "../utility.hpp"

#include <cassert>
#include <iostream>
#include <glog/logging.h>

using namespace wowlib::adt;

tile::tile()
    : _x(0), _y(0), _doodads(nullptr), _doodad_count(0),
      _map_objects(nullptr), _map_obj_count(0) {}

tile::tile(std::string name, int x, int y)
    : _x(x), _y(y), _doodads(nullptr), _doodad_count(0),
      _map_objects(nullptr), _map_obj_count(0) {}

tile::~tile() {
}

void tile::load(file &f, ADT_FILETYPE type) {

  f.seek_end();
  auto size = f.position();
  f.seek_from_beg(0);

  // loop through file chunk map
  // "file chunks" are like MHDR, MWMO, etc
  // "map chunks" are MCNKs

  // this takes ~20ms, which adds up when loading big maps ------------------------- 
  // how much of that is i/o and how much is allocating memory?
  file_contents_ = std::vector<char> (size);
  file_contents_.reserve(size);
  f.read((char *) &file_contents_[0], size);
  //-------------------------------------------------------------------------------- 

  // by my very rough calculations this part takes ~8ms
  std::multimap< uint32_t, std::vector<char> > file_chunks;
  
  size_t file_chunk_offset = 0;
  while (file_chunk_offset < size)
  {
    uint32_t token = * (uint32_t*) &file_contents_[file_chunk_offset];
    uint32_t file_chunk_size = * (uint32_t*) &file_contents_[file_chunk_offset + 4];
    file_chunks.insert({token, std::vector<char> (&file_contents_[file_chunk_offset + 8], &file_contents_[file_chunk_offset + file_chunk_size + 8])});
    file_chunk_offset += (file_chunk_size + 8);
  }
  //-------------------------------------------------------------------------------- 

  for (auto& [iff_token, data] : file_chunks) {
    // std::cout << utility::cc_as_str(iff_token) << '\n';

    switch (iff_token) {
    case IFFC_VERSION: {
      // assert (version == 0x12);
      uint32_t version = * (uint32_t*) &data[0];
      assert (version == 18);
      // std::cout << (int)data[0] << '\n';
      break;
    }
    case IFF_A_MDXFILES:
      // XXX rewrite to just take the char vector directly
      utility::parse_strings(&data[0], data.size(), _doodad_names);
      break;

    case IFF_A_WMOFILES:
      utility::parse_strings(&data[0], data.size(), _map_object_names);
      break;

    case IFF_A_DOODDEF:
      _doodad_count = data.size() / sizeof(SMODoodadDef);
      // std::cout << _doodad_count << ' ' << data.size() << '\n';
      _doodads = (SMODoodadDef *) &data[0];

      break;

    case IFF_A_MAPOBJDEF:
      _map_obj_count = data.size() / sizeof(SMOMapObjDef);
      _map_objects = (SMOMapObjDef *) &data[0];

      break;

    case IFF_A_CHUNK:
      _chunks.push_back(chunk(data, type));
      break;

    default:
      _unhandled_chunks[iff_token] = data;
      break;
    }
  }
  _loaded_files_mask = (ADT_FILETYPE)(_loaded_files_mask | type);

  // std::cout << "unhandled chunks: ";
  // for (auto& [token, data] : _unhandled_chunks)
  //   std::cout << utility::cc_as_str(token) << " (" << data.size() << " bytes), ";
  // std::cout << '\n';
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

std::vector<std::string>::iterator tile::begin_doodad_name() { return _doodad_names.begin(); }
std::vector<std::string>::iterator tile::end_doodad_name() { return _doodad_names.end(); }

std::vector<std::string>::iterator tile::begin_object_name() { return _map_object_names.begin(); }
std::vector<std::string>::iterator tile::end_object_name() { return _map_object_names.end(); }
