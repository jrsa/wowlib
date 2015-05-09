#include "local_file.h"

// todo: debug
#include <iostream>

local_file::local_file() {

}

local_file::local_file(std::string fn) {

  _path = fn;
  _f_stream = std::fstream(fn, std::ios_base::in | std::ios::out);
}

local_file::local_file(const local_file& other) {

  std::cerr << "why is a file object being copy-constructed?" << std::endl;

}

local_file& local_file::local_file::operator=(const local_file &rhs) {

  _f_stream.copyfmt(rhs._f_stream);
  _f_stream.clear(rhs._f_stream.rdstate());
  _f_stream.basic_ios<char>::rdbuf(rhs._f_stream.rdbuf());

  return *this;
}

local_file::~local_file() {

  _f_stream.close();
  std::cout << "closed/destroyed file: " << _path << std::endl;
}

int local_file::read(void *dest, size_t length) {

  if(_f_stream && _f_stream.is_open()) {

    if (_f_stream.eof()) {

      return 0;
    }

    _f_stream.read((char*)dest, length);
    return (int)length;
  }

  return 0;
}

int local_file::write(void *src, size_t size) {

  _f_stream.write((char*)src, size);


  return 0;
}

int local_file::position() {

  return (int)_f_stream.tellg();
}

void local_file::seek_from_current(size_t s) {

  _f_stream.seekg(s, std::ios::cur);
}

void local_file::seek_from_beg(size_t s) {

  _f_stream.seekg(s, std::ios::beg);
}

bool local_file::eof() {

  return _f_stream.eof();
}

bool local_file::is_open() {

  return _f_stream.is_open();
}
