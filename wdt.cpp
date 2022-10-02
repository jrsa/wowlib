#include <glog/logging.h>
#include <stdint.h>
#include "wdt.hpp"
#include "utility.hpp"

typedef struct _SMAreaInfo {
  uint32_t flags;
  uint32_t nobody;
} SMAreaInfo;

bool tile_present(SMAreaInfo &i) { return i.flags & 1; }

namespace wowlib {
wdt::wdt(file &f) {
  int magic = 0;
  int size = 0;
  int version = 0;

  f.seek_from_beg(0);
  while (true) {
    if (!f.read((char*)&magic, 4)) {
      break;
    }
    f.read((char*)&size, 4);

    LOG(INFO) << utility::cc_as_str(magic) << " found with size: " << size;

    switch (magic) {
    case 'MVER': {
      f.read((char*)&version, 4);
      if (version != 18) {
        LOG(FATAL) << "unsupported version " << version << "or invalid file";
      }
      break;
    }
    case IFF_WDTMAIN: {
      if (size != WDT_SIZE * sizeof(SMAreaInfo)) {
        LOG(FATAL) << "wdt has " << size / 4 << " entries instead of "
                   << WDT_SIZE;
      }
      SMAreaInfo *tiles = new SMAreaInfo[WDT_SIZE];
      f.read((char*)tiles, size);

      for (int i = 0; i <= 63; ++i) {
        for (int j = 0; j <= 63; ++j) {
          int tile_idx = (j * 64) + i;
          if (tile_present(tiles[tile_idx])) {
            tiles_present.push_back(std::make_pair(j, i));
          }
        }
      }

      break;
    }
    default: {
      f.seek_from_current(size);
      break;
    }
    }
  }
}

wdt::~wdt() {}

bool wdt::check_tile(int x, int y) {
    return std::find(tiles_present.begin(), tiles_present.end(), std::make_pair(x, y)) != tiles_present.end();
}

}
