#ifndef _wowlib_wmo_group_h
#define _wowlib_wmo_group_h

#include <stdint.h>

#include <vector>
#include <string>

#include "format.hpp"

class file;

class group {

private:
  poly_flags *_polygon_flags;
  float *_geometry;

  float _bounds0[3];
  float _bounds1[3];


  uint32_t _mogi_flags,
      _name_idx /* name idx is only needed in loading should not be state */;

  std::string _name;

  bool _loaded;

public:
  group();
  group(group_info &);

  ~group();

  void load(file &);

  std::string name() const;
  void setName(std::string);

  uint32_t flags() const;
};

#endif /* defined(__wmotool__group__) */
