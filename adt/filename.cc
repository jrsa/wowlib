#include "filename.h"

namespace wowlib {
namespace adt {
  boost::filesystem::path filename(boost::filesystem::path dir, std::string name,
                                 int x, int y, ADT_FILETYPE type) {
  std::string typetoken;
  switch (type) {
  case ADT_NONE:
    break;
  case ADT_BASE_FILE:
    break;
  case ADT_OBJ_FILE:
    typetoken = std::string("_obj0");
    break;
  case ADT_TEX_FILE:
    typetoken = std::string("_tex0");
    break;
  }

  std::stringstream fn;
  fn << name << "_" << x << "_" << y << typetoken << ".adt";

  boost::filesystem::path result;
  result /= dir /= name;
  result /= boost::filesystem::path(fn.str());
  return result;
}
}
}