#ifndef adt_filename_h
#define adt_filename_h

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <sstream>

#include "tile.hpp"

namespace wowlib {
namespace adt {

boost::filesystem::path filename(boost::filesystem::path dir, std::string name,
                                 int x, int y, ADT_FILETYPE type);
}
}

#endif