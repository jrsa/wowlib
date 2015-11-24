cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)

set(GLOG_LIBRARY "/usr/local/opt/glog/lib/libglog.dylib")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
)

set(wmosrcs
  wmo/wmo.cpp
  wmo/group.cpp
)

set(adtsrcs
  adt/adt.cpp
  adt/chunk.cpp
  adt/filename.cc
)

add_executable(tiletest
  file/local_file.cpp
  utility.cpp
  ${adtsrcs}
  tiletest.cpp
  )

target_link_libraries(tiletest ${Boost_LIBRARIES} ${GLOG_LIBRARY})

add_executable(wmotest
  file/local_file.cpp
  utility.cpp
  ${wmosrcs}
  wmotest.cc
  )

target_link_libraries(wmotest ${Boost_LIBRARIES} ${GLOG_LIBRARY})