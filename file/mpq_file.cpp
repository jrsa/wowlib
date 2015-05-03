#include <iostream>

#include "mpq_file.h"

mpq_file::mpq_file(mpq& archive, std::string fn, HANDLE handle)
:_archive(archive), _handle(handle), _eof_bit(false) {
  
  _size = SFileGetFileSize(_handle, 0);
}

mpq_file::~mpq_file() {
  
  SFileCloseFile(_handle);
}

int mpq_file::read(void* dest, size_t size) {
  
  DWORD read = 0, error = 0;
  
	bool did_read = SFileReadFile(_handle, dest, (DWORD)size, &read, NULL);
  
  if((read != size) || !did_read) {
    
    error = GetLastError();
    if(error == ERROR_HANDLE_EOF) {
      
      _eof_bit = true;
    }
    else {
      
      std::cerr << "an error occured reading file: " << error;
      std::cerr << std::endl;
    }
  }
  
  return read;
}

int mpq_file::write(void *src, size_t size) {
  
  int written = 0;
  
  
  
  return written;
}

void mpq_file::seek_from_beg(size_t size) {
  
  SFileSetFilePointer(_handle, (int)size, 0, FILE_BEGIN);
}

void mpq_file::seek_from_current(size_t size) {
  
  SFileSetFilePointer(_handle, (int)size, 0, FILE_CURRENT);
}

std::string mpq_file::filename() {
  
  if(_name) {
    
    _name = new char[MAX_PATH];
    SFileGetFileName(_handle, _name);
  }
  
  return std::string(_name);
}

bool mpq_file::is_open() {
  
  return _handle != NULL;
}

bool mpq_file::eof() {
  
  return _eof_bit;
}
