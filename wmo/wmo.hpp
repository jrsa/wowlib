#ifndef _wowlib_wmo_h
#define _wowlib_wmo_h

#include <string>
#include <vector>

#include "../file/file.hpp"
#include "format.hpp"
#include "group.hpp"

typedef std::vector<group>::iterator group_itr;

class material {
private:
public:
  material();
  material(material_entry);
};

class wmo {
  int version, area_id;

  std::vector<group> _groups;
  std::vector<material> _materials;

  std::vector<std::string> groupnames, texture_filenames;

  // file* _file;
  // std::ostream _log;

public:
  wmo();
  wmo(file &);

  void load(file &);

  group &load_group(int index, file &);

  group_itr first_group();
  group_itr last_group();

  std::string _base_name;

  // helper to get filenames for each group
  std::string group_filename(int g);

  static void process_filenames(std::string name, std::string &base,
                                std::string &path);
};

#endif /* defined(__wmotool__wmo__) */
