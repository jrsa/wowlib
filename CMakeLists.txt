cmake_minimum_required (VERSION 2.8)

set(target wltest01)

set(adt_hdrs
  adt/adt.h
  adt/chunk.h
  adt/format.h
)

set(adt_srcs
  adt/adt.cpp
  adt/chunk.cpp
)

set(wmo_hdrs
  wmo/format.h
  wmo/group.h
  wmo/wmo.h
)

set(wmo_srcs
  wmo/wmo.cpp
  wmo/group.cpp
)

set(file_hdrs
  file/file.h
  file/local_file.h
)

set(file_srcs
  file/local_file.cpp
)

set(util_hdrs
  utility.h
)

set(util_srcs
  utility.cpp
)

set(srcs
  ${adt_hdrs}
  ${adt_srcs}
  ${wmo_hdrs}
  ${wmo_srcs}
  ${file_hdrs}
  ${file_srcs}
  ${util_hdrs}
  ${util_srcs}
  testmain.cpp
)

add_executable(${target} ${srcs})
