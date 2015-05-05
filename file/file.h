#ifndef _wowlib_file_file_h
#define _wowlib_file_file_h

#include <string>

// abstract class for file ops

class file {

protected:
  std::string path;

public:
  virtual int read(void* dest, size_t size) =0;
  virtual int write(void* src, size_t size) =0;

	virtual void seek_from_beg(size_t) =0;
	virtual void seek_from_current(size_t) =0;

  virtual bool is_open() =0;
  virtual bool eof() =0;

  virtual int position() =0;
};

#endif
