#include "wmo.hpp"
#include "group.hpp"
#include "../utility.hpp"

#include <glog/logging.h>

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
    LOG(FATAL) << "found token " << utility::cc_as_str(token)
               << " instead of (MVER)";
  }

  else if (version != 0x11) {
    LOG(FATAL) << "invalid file version " << version << ", expected 17 (0x11)";
  }

  // read data sections
  while (!f.eof()) {
    f.read(&token, 4);
    f.read(&size, 4);

    switch (token) {
    case WMO_HEADER: {
      if (size != sizeof(wmo_header)) {
        LOG(ERROR) << "invalid header, size is " << size;
        LOG(ERROR) << " should be " << sizeof(wmo_header);
      }

      hdr = new wmo_header;
      f.read(hdr, sizeof(wmo_header));

      LOG(INFO) << hdr->group_count << " groups";
      LOG(INFO) << hdr->mat_count << " materials";
      LOG(INFO) << hdr->portal_count << " portals";

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
        LOG(FATAL) << "header must be loaded before materials section";
      }

      if (hdr->mat_count != (size / sizeof(material_entry))) {
        LOG(ERROR) << "header indicates " << hdr->mat_count
                   << " materials but the materials section has "
                   << size / sizeof(material_entry);
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
        LOG(ERROR) << "header should be before group info";
        return;
      }

      if (hdr->group_count != (size / sizeof(group_info))) {
        LOG(ERROR) << "header indicates " << hdr->group_count
                   << " groups but the group info section has "
                   << size / sizeof(groupnames);
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

    LOG(FATAL) << "out of bounds access in load_group";
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
