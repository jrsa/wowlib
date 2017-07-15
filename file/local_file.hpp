#ifndef __ballin_wallhack__local_file__
#define __ballin_wallhack__local_file__

#include <fstream>


#include "file.hpp"

class local_file : public file {

  std::fstream _f_stream;
  std::string _stripped;
public:
  local_file();
  local_file(std::string);
  local_file(const local_file &other);

  ~local_file();

  local_file &operator=(const local_file &rhs);

  int read(void *dest, size_t);
  int write(void *src, size_t);
  int position();

  void seek_from_beg(size_t);
  void seek_from_current(size_t);

  std::string path() { return _stripped; }

  bool eof();
  bool is_open();
};

#endif /* defined(__ballin_wallhack__local_file__) */
