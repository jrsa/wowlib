#ifndef __ballin_wallhack__mpq__
#define __ballin_wallhack__mpq__

#include <StormLib.h>
#include <string>
#include <vector>

class mpq_file;

class mpq {

  HANDLE _archive_handle;

public:
  mpq(std::string);
  ~mpq();

  mpq_file open_file(std::string);

  bool alive();
  void search(std::string, std::vector<std::string> &);

  void extract_to_disk(std::string filename, std::string disk_file);
};

#endif /* defined(__ballin_wallhack__mpq__) */
