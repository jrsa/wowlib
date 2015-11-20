#include "mpq.h"
#include "mpq_file.h"

#include <iostream>

mpq::mpq(std::string fn) : _archive_handle(nullptr) {

  if (!SFileOpenArchive(fn.c_str(), 0, 0, &_archive_handle)) {

    std::cerr << fn << "could not be opened.";
    std::cerr << "error: " << GetLastError();
    std::cerr << std::endl;
  }
}

mpq::~mpq() {

  if (_archive_handle)
    SFileCloseArchive(_archive_handle);
}

mpq_file mpq::open_file(std::string fn) {

  HANDLE file;

  SFileOpenFileEx(_archive_handle, fn.c_str(), 0, &file);

  return mpq_file(*this, fn, file);
}

bool mpq::alive() { return !!_archive_handle; }

void mpq::search(std::string file, std::vector<std::string> &result) {

  HANDLE find_handle = nullptr;
  SFILE_FIND_DATA *f = new SFILE_FIND_DATA;

  if ((find_handle = SFileFindFirstFile(_archive_handle, file.c_str(), f, 0))) {

    result.push_back(f->cFileName);
  }

  while (SFileFindNextFile(find_handle, f)) {

    result.push_back(f->cFileName);
  }

  SFileFindClose(find_handle);

  delete f;
}

void mpq::extract_to_disk(std::string filename, std::string disk_file) {

  if (!SFileExtractFile(_archive_handle, filename.c_str(), disk_file.c_str(),
                        SFILE_OPEN_FROM_MPQ)) {

    std::cerr << filename << " could not be extracted to " << disk_file
              << std::endl;
    std::cerr << "error: " << GetLastError() << std::endl;
  }
}
