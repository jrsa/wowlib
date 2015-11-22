#include "local_file.h"

// todo: debug
#include <iostream>

local_file::local_file() {}

local_file::local_file(std::string fn) {

  _path = fn;
  _stripped = boost::filesystem::path(fn).filename().string();
  _f_stream = std::fstream(fn, std::ios_base::in | std::ios::out);

  if (this->is_open()) {

    std::cout << "[" <<_stripped << "] opened" << std::endl;
  }
  else if(std::ios::failbit) {
    std::cerr << "[" <<_stripped << "] couldnt be opened" << std::endl;
  }
}

local_file &local_file::local_file::operator=(const local_file &rhs) {

  _f_stream.copyfmt(rhs._f_stream);
  _f_stream.clear(rhs._f_stream.rdstate());
  _f_stream.basic_ios<char>::rdbuf(rhs._f_stream.rdbuf());

  return *this;
}

local_file::~local_file() {

  _f_stream.close();
  std::cout << "[" <<_stripped << "] closed" << std::endl;
}

int local_file::read(void *dest, size_t length) {

  if (_f_stream && _f_stream.is_open()) {

    if (_f_stream.eof()) {
      std::cerr << "[" <<_stripped << "] read past eof" << std::endl;
      return 0;
    }

    _f_stream.read((char *)dest, length);
    std::cout << "[" <<_stripped << "] reading " << length <<"b" << std::endl;
    return (int)length;
  }

  return 0;
}

int local_file::write(void *src, size_t size) {

  _f_stream.write((char *)src, size);

  return 0;
}

int local_file::position() { return (int)_f_stream.tellg(); }

void local_file::seek_from_current(size_t s) {

  std::cout << "[" <<_stripped << "] seek forward: " << s << std::endl;
  _f_stream.seekg(s, std::ios::cur);
}

void local_file::seek_from_beg(size_t s) {
  std::cout << "[" <<_stripped << "] seek from 0: " << s << std::endl;
  _f_stream.seekg(s, std::ios::beg);
}

bool local_file::eof() { return _f_stream.eof(); }

bool local_file::is_open() { return _f_stream.is_open(); }
