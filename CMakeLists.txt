cmake_minimum_required (VERSION 3.0)
project(wowlib)

set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++")

FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)

set(GLOG_LIBRARY "/usr/local/opt/glog/lib/libglog.dylib")

add_compile_definitions(GOOGLE_STRIP_LOG=1)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
)

set(wmosrcs
  wmo/wmo.cpp
  wmo/group.cpp
)

set(adtsrcs
  adt/tile.cpp
  adt/chunk.cpp
  adt/filename.cc
)

add_executable(tiletest
  file/local_file.cpp
  utility.cpp
  ${adtsrcs}
  wdt.cpp
  tiletest.mm
  )

add_executable(tiletest2
  file/local_file.cpp
  utility.cpp
  ${adtsrcs}
  wdt.cpp
  tiletest2.cpp
  )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
target_link_libraries(tiletest ${Boost_LIBRARIES} ${GLOG_LIBRARY})
target_link_libraries(tiletest2 ${Boost_LIBRARIES} ${GLOG_LIBRARY})

add_library(wowstatic
        STATIC
        ${wmosrcs}
        ${adtsrcs}
        utility.cpp
        wdt.cpp)

add_library(wow
        MODULE
        ${wmosrcs}
        ${adtsrcs}
        utility.cpp
        wdt.cpp
        )
target_link_libraries(wow ${Boost_LIBRARIES} ${GLOG_LIBRARY})


add_executable(wmotest
  file/local_file.cpp
  utility.cpp
  ${wmosrcs}
  wmotest.cc
  )

target_link_libraries(wmotest ${Boost_LIBRARIES} ${GLOG_LIBRARY})
