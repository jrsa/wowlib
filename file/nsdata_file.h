#ifndef _wowlib_file_nsdatafile_h
#define _wowlib_file_nsdatafile_h

// 

#include "file.h"
#include <Foundation/Foundation.h>
#include <vector>

typedef char byte;
typedef std::vector<byte> bytevec;

class nsdata_file : public file {
  
  unsigned int _offset;
  bytevec      _data;
  
public:
  
  nsdata_file();
  nsdata_file(NSData* d);
    
  int read(void* dest, size_t size);
	
	void seek_from_beg(size_t);
	void seek_from_current(size_t);
  
  bool is_open();
  bool eof();

};

#endif