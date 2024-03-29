#ifndef _wowlib_file_file_h
#define _wowlib_file_file_h

#include <string>

// abstract class for file ops

class file {

protected:
  std::string _path;

public:
  virtual int read(char *dest, size_t size) = 0;
  virtual int write(char *src, size_t size) = 0;

  virtual void seek_from_beg(size_t) = 0;
  virtual void seek_from_current(size_t) = 0;
  virtual void seek_end() = 0;

  virtual bool is_open() = 0;
  virtual bool eof() = 0;

  virtual int position() = 0;

  virtual std::string path() { return _path; }
};

#endif
