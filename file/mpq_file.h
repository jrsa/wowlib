#ifndef __ballin_wallhack__mpq_file__
#define __ballin_wallhack__mpq_file__

#include "file.h"
#include "mpq.h"

class mpq_file : public file {

  mpq _archive;
  HANDLE _handle;

  size_t _size;

  char *_name;

  bool _eof_bit;

public:
  mpq_file(mpq &, std::string, HANDLE);
  ~mpq_file();

  int read(void *, size_t);
  int write(void *, size_t);
  int position();

  void seek_from_beg(size_t);
  void seek_from_current(size_t);

  bool eof();
  bool is_open();

  std::string filename();
};

#endif