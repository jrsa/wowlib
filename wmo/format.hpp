#ifndef _wowlib_wmo_format_h
#define _wowlib_wmo_format_h

#include <stdint.h>

#pragma mark Root File Section Codes

#define WMO_HEADER 'MOHD'
#define WMO_TEXFILES 'MOTX'
#define WMO_MATERIALS 'MOMT'
#define WMO_GROUPNAME 'MOGN'
#define WMO_GROUPINFO 'MOGI'
#define WMO_SKYBOX 'MOSB'
#define WMO_PORTAL_VERTICES 'MOPV'
#define WMO_PORTAL_INDICES 'MOPT'
#define WMO_PORTAL2GROUP 'MOPR'
#define WMO_VISIBLE_VERTS 'MOVV'
#define WMO_VISIBLE_BLOCKS 'MOVB'
#define WMO_LIGHTS 'MOLT'
#define WMO_DOODADSETS 'MODS'
#define WMO_DSET_NAMES 'MODN'
#define WMO_DOODADDEFS 'MODD'
#define WMO_FOG 'MFOG'

#pragma mark Group File Section Codes

#define WMO_GROUP 'MOGP'
#define GRP_MATINFO 'MOPY'
#define GRP_VERTEX_INDICES 'MOVI'
#define GRP_VERTICES 'MOVT'
#define GRP_VERTEX_NORMALS 'MONR'
#define GRP_TEXCOORDS 'MOTV'
#define GRP_RENDERBATCHES 'MOBA'
#define GRP_LIGHT_REFS 'MOLR'
#define GRP_DOODADREFS 'MODR'
#define GRP_BSP_NODES 'MOBN'
#define GRP_BSP_FACES 'MOBR'
#define GRP_VERTEX_COLORS 'MOCV'
#define GRP_LIQUIDS 'MLIQ'

#pragma mark Flags

enum mopy_flags {

  NO_CAM_COLLIDE = 0x2,
  DETAIL_FACE = 0x4,
  COLLISION_FACE = 0x8,

};

enum mogp_flags {

  BSP = 0x1,
  VERTEX_COLORS = 0x4,
  OUTDOORS = 0x8,
  LIGHTS = 0x200,
  DOODADS = 0x800,
  WATER = 0x1000,
  INDOORS = 0x2000,
  SHOW_SKYBOX = 0x40000,

};

#pragma mark Root File Structures

typedef struct {

  uint32_t mat_count;
  uint32_t group_count;
  uint32_t portal_count;
  uint32_t light_count;
  uint32_t model_count;
  uint32_t doodad_count;
  uint32_t set_count;
  uint32_t amb_color;
  uint32_t id;
  float bb0[3];
  float bb1[3];
  uint32_t liquid_type;

} wmo_header;

typedef struct {

  /*000h*/ uint32_t flags1;
  /*004h*/ uint32_t shader;
  /*008h*/ uint32_t blendMode;
  /*00Ch*/ uint32_t texture_1;
  /*010h*/ uint32_t color_1;
  /*014h*/ uint32_t flags_1;
  /*018h*/ uint32_t texture_2;
  /*01Ch*/ uint32_t color_2;
  /*020h*/ uint32_t flags_2;
  /*024h*/ uint32_t texture_3;
  /*028h*/ uint32_t color_3;
  /*02Ch*/ uint32_t unk[3];
  /*030h*/
  /*034h*/
  /*038h*/ uint32_t runTimeData[2];
  /*03Ch*/
  /*040h*/

} material_entry;

typedef struct {

  uint32_t flags;
  float bb0[3];
  float bb1[3];
  int32_t name_idx;

} group_info;

// portals

typedef struct {

  float a[3];
  float b[3];
  float c[3];
  float d[3];

} portal_geo;

typedef struct {

  uint16_t vert_idx;
  uint16_t vert_count;
  float unk[4];

} portal_info;

#pragma mark Group File Structures

typedef struct {

  uint32_t name_idx;
  uint32_t desc_idx;
  uint32_t flags;
  float bb0[3];
  float bb1[3];
  uint16_t mopr_idx;
  uint16_t mopr_count;

} group_header;

typedef struct {

  uint8_t flags;
  uint8_t material;

} poly_flags;

#endif
