# UPNP
set(UPNPC_BUILD_STATIC ON CACHE BOOL "Build static library")
set(UPNPC_BUILD_SHARED OFF CACHE BOOL "Build shared library")
set(UPNPC_BUILD_TESTS OFF CACHE BOOL "Build upnpc tests")
add_subdirectory(miniupnpc)

# gtests
set(BUILD_GTESTS OFF CACHE BOOL "Build gtest")
if (BUILD_GTESTS)
   add_subdirectory(gtest)
   set_property(TARGET gtest gtest_main PROPERTY FOLDER "external")
endif()

if(MSVC)
    include_directories(../version)
    add_subdirectory(rocksdb EXCLUDE_FROM_ALL)
    set_property(TARGET upnpc-static rocksdb PROPERTY FOLDER "external")
elseif(NOT MSVC)
    add_subdirectory(rocksdb EXCLUDE_FROM_ALL)
    set_property(TARGET upnpc-static rocksdb PROPERTY FOLDER "external")
    set_target_properties(rocksdb PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/rocksdb/librocksdb.a)
endif()

if(MSVC)
  set_property(TARGET upnpc-static APPEND_STRING PROPERTY COMPILE_FLAGS " -wd4244 -wd4267")
elseif(NOT MSVC)
  set_property(TARGET upnpc-static APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-unused-result -Wno-unused-value")
endif()
