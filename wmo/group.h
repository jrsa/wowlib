#ifndef _wowlib_wmo_group_h
#define _wowlib_wmo_group_h

#include <stdint.h>

#include <vector>
#include <string>

#include "format.h"

class file;

class group {

private:
  float *_geometry;

  float _bounds0[3];
  float _bounds1[3];

  poly_flags *_polygon_flags;

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
};

#endif /* defined(__wmotool__group__) */
