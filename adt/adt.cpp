#include "adt.h"
#include "../file/file.h"
#include "../utility.h"

// todo: iostream for debugging only
#include <iostream>
#include <exception>

adt::tile::tile():
_x(0), _y(0), _doodads(nullptr), _map_objects(nullptr), _doodad_count(0), _map_obj_count(0) {


adt::tile::tile():_name("blank tile")
                  , _x(0)
                  , _y(0)
                  , _doodads(nullptr)
                  , _doodad_count(0)
                  , _map_objects(nullptr)
                  , _map_obj_count(0)
{
}


adt::tile::tile(std::string name, int x, int y):_name(name),_x(x)
                                              , _y(y)
                                              , _doodads(nullptr)
                                              , _doodad_count(0)
                                              , _map_objects(nullptr)
                                              , _map_obj_count(0)
{

}

adt::tile::~tile() {

  delete _doodads;
  delete _map_objects;

  std::cout << "destroyed tile" << std::endl;
}

bool adt::tile::load(file& f, ADT_FILETYPE type) {

  int magic = 0;
  int size = 0;
  char *buffer = 0;
  int version = 0;

  std::vector<std::string> mdxnames, wmonames;

  f.seek_from_beg(0);

  f.read(&magic, 4);
  f.read(&size, 4);
  f.read(&version, 4);

  if (magic != IFFC_VERSION || size != 0x4 || version != 0x12)
  {
    return false;
  }

  while (true)
  {
    if(!f.read(&magic, 4))
    {
      break;
    }

    f.read(&size, 4);

    switch (magic)
    {
      case IFF_A_MDXFILES:

        buffer = new char[size];
        f.read(buffer, size);

        utility::parse_strings(buffer, size, mdxnames);
        delete [] buffer;

        break;

      case IFF_A_WMOFILES:

        buffer = new char[size];
        f.read(buffer, size);

        utility::parse_strings(buffer, size, wmonames);
        delete [] buffer;

        break;

      case IFF_A_DOODDEF:

        _doodad_count = size / sizeof(SMODoodadDef);
        buffer = (char *)new SMODoodadDef[_doodad_count];
        f.read(buffer, size);
        _doodads = (SMODoodadDef *)buffer;

        break;

      case IFF_A_MAPOBJDEF:

        buffer = (char *)new SMOMapObjDef[_map_obj_count];
        f.read(buffer, size);
        _map_obj_count = size / sizeof(SMOMapObjDef);
        _map_objects = (SMOMapObjDef *)buffer;

        break;

      case IFF_A_CHUNK:

        for (int i = 0; i < 255; ++i)
        {
          _chunks.push_back(chunk(f, size, type));
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
  return true;
}

bool adt::tile::save(file &f, ADT_FILETYPE type)
{
  if(!f.is_open())
  {
    return false;
  }

  int magic = IFFC_VERSION;
  int size = 0x4;
  int version = 0x12;

  f.write((char *)&magic, 4);
  f.write((char *)&size, 4);
  f.write((char *)&version, 4);

  if(type == ADT_OBJ_FILE)
  {
    std::cerr << "saving object file not implemented" << std::endl;

    // write filenames
    // write id's
    // write entries

    return false;
  }

  if(type == ADT_BASE_FILE) {

    for (int i=0; i < 255; i++) {

      _chunks[i].save(f, ADT_BASE_FILE);
    }
    // todo: save flightbox
  }
  return false;
}

std::vector<adt::chunk>::iterator adt::tile::first_chunk()
{
  return _chunks.begin();
}

std::vector<adt::chunk>::iterator adt::tile::last_chunk()
{
  return _chunks.end();
}

std::vector<std::string> adt::tile::map_object_names()
{
  return _map_object_names;
}
