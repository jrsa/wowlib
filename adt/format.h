#ifndef _wowlib_adt_format_h
#define _wowlib_adt_format_h

#include <cstdint>

#define IFFC_VERSION 'MVER' // 0x4D564552

// CMapArea (*.adt files)

#define IFF_A_CHUNK 'MCNK'     // 0x4D434E4B
#define IFF_A_MDXFILES 'MMDX'  // 0x4D4D4458
#define IFF_A_WMOFILES 'MWMO'  // 0x4D574D4F
#define IFF_A_DOODDEF 'MDDF'   // 0x4D444446
#define IFF_A_MAPOBJDEF 'MODF' // 0x4D4F4446
#define IFF_A_FLIGHTBOX 'MFBO' // 0x4D46424F

// CMapChunk (inside MCNK Section)

#define IFF_C_LAYERS 'MCLY' // 0x4D434C59
#define IFF_C_REF 'MCRF'    // 0x4D435246
#define IFF_C_WREF 'MCRW'   // 0x4D435257
#define IFF_C_DREF 'MCRD'   // 0x4D435244
#define IFF_C_VERTS 'MCVT'  // 0x4D435654
#define IFF_C_NORMs 'MCNR'  // 0x4D434E52
#define IFF_C_SOUNDEMIT 'MCSE'

// Data Structures in ADT Files

#define C_VERT_COUNT 145

typedef enum flags {
  CHUNK_MCSH = 0x1,
  CHUNK_WALL = 0x2,
  CHUNK_RIVER = 0x4,
  CHUNK_OCEAN = 0x8,
  CHUNK_LAVA = 0x10,
  CHUNK_SLIME = 0x20,
  CHUNK_MCCV = 0x40,
  CHUNK_UNK = 0x8000
} SMChunkFlags;

typedef struct {
  SMChunkFlags flags;
  uint32_t idx_x;
  uint32_t idx_y;
  uint32_t layer_count; // need to preserve
  uint32_t n_drefs;     // zero/not used
  uint32_t ofs_mcvt;    // write at time of save
  uint32_t ofs_mcnr;    // write at time of save
  uint32_t ofs_mcly;    // write at time of save
  uint32_t ofs_mcrf;
  uint32_t ofs_mcal;    // write at time of save
  uint32_t alpha_size;  // write at time of save
  uint32_t mcsh;        // write at time of save
  uint32_t shadow_size; // write at time of save
  uint32_t area_id;     // need to preserve
  uint32_t n_wrefs;
  uint32_t holes; // need to preserve
  uint32_t tex[4];
  uint32_t pred_tex;
  uint32_t n_doodad_fx;
  uint32_t ofs_mcse;   // write at time of save
  uint32_t count_mcse; // write at time of save
  uint32_t ofs_mclq;   // zero/not used
  uint32_t size_mclq;
  float x, y, z;
  uint32_t ofs_mccv;
  uint32_t ofs_mclv;
  uint32_t unk1;

} SMChunkHeader;

typedef struct {
  uint32_t fn_idx;
  uint32_t unique_id;
  float pos[3];
  float rot[3];
  uint16_t scale;
  uint16_t flags;

} SMODoodadDef;

typedef struct {
  uint32_t fn_idx;
  uint32_t unique_id;
  float pos[3];
  float rot[3];
  float lo[3];
  float hi[3];
  uint16_t flags;
  uint16_t doodad_set;
  uint16_t nameset;
  uint16_t unk;

} SMOMapObjDef;

// not present in the files themselves

typedef enum {
  ADT_NONE = 0x0,
  ADT_BASE_FILE = 0x1,
  ADT_OBJ_FILE = 0x2,
  ADT_TEX_FILE = 0x4
} ADT_FILETYPE;

#endif
