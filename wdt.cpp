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
    if (!f.read(&magic, 4)) {
      break;
    }
    f.read(&size, 4);

    LOG(INFO) << utility::cc_as_str(magic) << " found with size: " << size;

    switch (magic) {
    case 'MVER': {
      f.read(&version, 4);
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
      f.read(tiles, size);

      for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 64; ++j) {
          int tile_idx = (i * 64) + j;
          if (tile_present(tiles[tile_idx])) {
            tiles_present.push_back(std::make_pair(i, j));
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
}