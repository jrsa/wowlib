#include "wmo.h"
#include "group.h"
#include "../utility.h"

#include <iomanip>
#include <sstream>

#include <boost/algorithm/string.hpp>

#define ARCHIVE_PATH_SEP "\\"

material::material(material_entry m) {}

material::material() {}

wmo::wmo() : version(0x11), area_id(0), _base_name("New Group") {}

void wmo::load(file &f) {

  int size = 0, token = 0;
  wmo_header *hdr = nullptr;

  std::string skybox_filename;

  //_file = &f;

  f.seek_from_beg(0);

  f.read(&token, 4);
  f.read(&size, 4);
  f.read(&version, 4);

  // version check
  if (token != 'MVER') {
    std::cerr << "found token " << std::hex << token;
    std::cerr << " instead of " << 'MVER' << " (MVER)" << std::endl;
    std::cerr << "do not pass go, do not collect $200" << std::endl;

    return;
  }

  else if (version != 0x11) {
    std::cerr << "invalid file version " << version;
    std::cerr << ", expected 17 (0x11)" << std::endl;

    return;
  }

  // read data sections
  while (!f.eof()) {
    f.read(&token, 4);
    f.read(&size, 4);

    switch (token) {
    case WMO_HEADER: {
      if (size != sizeof(wmo_header)) {
        std::cout << "invalid header, size is " << size;
        std::cout << " should be " << sizeof(wmo_header);
        std::cout << std::endl;
      }

      hdr = new wmo_header;
      f.read(hdr, sizeof(wmo_header));

      std::cerr << hdr->group_count << " groups" << std::endl;
      std::cerr << hdr->mat_count << " materials" << std::endl;
      std::cerr << hdr->portal_count << " portals" << std::endl;

      // groups.resize(hdr->group_count);
      // materials.resize(hdr->mat_count);

      break;
    }
    case WMO_SKYBOX: {
      if (size) {
        char *name = new char[size];

        f.read(name, size);
        skybox_filename = std::string(name);

        delete[] name;
      }
    }
    case WMO_GROUPNAME: {
      char *data = new char[size];
      f.read(data, size);

      utility::parse_strings(data, size, groupnames);

      delete[] data;

      break;
    }
    case WMO_TEXFILES: {
      char *data = new char[size];
      f.read(data, size);

      utility::parse_strings(data, size, texture_filenames);

      delete[] data;

      break;
    }
    case WMO_MATERIALS: {
      if (!hdr) {
        std::cerr << "header should be before materials section" << std::endl;
        return;
      }

      if (hdr->mat_count != (size / sizeof(material_entry))) {
        std::cerr << "header indicates " << hdr->mat_count
                  << " materials but the materials section has "
                  << size / sizeof(material_entry) << std::endl;
      }

      material_entry *data = new material_entry[hdr->mat_count];
      f.read(data, size);

      for (int i = 0; i < hdr->mat_count; i++) {
        _materials.push_back(material(data[i]));
      }

      delete[] data;
      break;
    }
    case WMO_GROUPINFO: {
      if (!hdr) {
        std::cerr << "header should be before group info" << std::endl;
        return;
      }

      if (hdr->group_count != (size / sizeof(group_info))) {
        std::cerr << "header indicates " << hdr->group_count;
        std::cerr << " groups but the group info section has ";
        std::cerr << size / sizeof(groupnames);
        std::cerr << std::endl;
      }

      group_info *data = new group_info[hdr->group_count];
      f.read(data, size);

      for (int i = 0; i < hdr->group_count; i++) {
        group_info gi = data[i];

        group g(gi);
        //          g.setName(groupnames[gi.name_idx]);
        _groups.push_back(g);
      }

      break;
    }
    default: {
      f.seek_from_current(size);
      break;
    }
    }
  }
  delete hdr;
}

std::string wmo::group_filename(int g) {

  std::stringstream ss;
  ss << _base_name << "_" << std::setw(3) << std::setfill('0') << g << ".wmo";

  return ss.str();
}

group &wmo::load_group(int index, file &f) {

  if (index > _groups.size()) {

    throw new std::logic_error("out of bounds access in load_group");
  }

  _groups[index].load(f);

  // dont think this is really correct..
  _groups[index].setName(groupnames[index]);

  return _groups[index];
}

group_itr wmo::first_group() { return _groups.begin(); }

group_itr wmo::last_group() { return _groups.end(); }

void wmo::process_filenames(std::string name, std::string &base,
                            std::string &path) {
  // hold the split result
  std::vector<std::string> path_parts;

  boost::split(path_parts, name, boost::is_any_of(ARCHIVE_PATH_SEP));

  // the name with the extension
  std::string trimmed_name = path_parts.back();
  path_parts.pop_back();

  path = boost::join(path_parts, "\\");

  path_parts.clear();
  boost::split(path_parts, trimmed_name, boost::is_any_of("._"));

  base = path_parts.front();
}
