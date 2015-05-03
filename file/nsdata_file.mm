#include "nsdata_file.h"

nsdata_file::nsdata_file():
_offset(0) {
  
}

nsdata_file::nsdata_file(NSData* d):
_offset(0) {

  long int len = [d length];
  
  char *file_data = (char*)malloc(len);
  memcpy(file_data, [d bytes], len);
  
  _data = bytevec(file_data, &file_data[[d length]]);
}

int nsdata_file::read(void* _dest, size_t size) {
  
  int read = 0;
  char* dest = (char*)_dest;
  
  if(!dest) {
    throw new std::runtime_error("tried to read to nowhere");
  }
  
  if((_offset + size) > _data.size()) {
    throw new std::runtime_error("tried to read out of bounds");
  }
  
  for (int i = 0; i < size; i++) {
    
    dest[i] = _data[_offset];
    _offset++; read++;
  }
  
  return read;
}

void nsdata_file::seek_from_beg(size_t size) { _offset = (int)size; }

void nsdata_file::seek_from_current(size_t size) { _offset += size; }

bool nsdata_file::is_open() {
  
  // lol stub, not real behavior until i rethink this API, not really needed
  // since the NSDocumentController takes care of file handling
  
  return(true);
}

bool nsdata_file::eof() {
  return(_offset >= _data.size());
}
