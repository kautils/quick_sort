


cmake_minimum_required(VERSION 3.20)
project(KautilAlgorithSort
        LANGUAGES C CXX
        VERSION 0.0.0.0
        )

set(CMAKE_CXX_STANDARD 17)


set(__t kautil_quick_sort_shared_export)
add_library(${__t} SHARED)
file(GLOB_RECURSE srcs_extern ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
target_sources(${__t} PRIVATE ${srcs} ${srcs_extern})

target_compile_definitions(${__t} PRIVATE BUILD_KAUTIL_QUICK_SOIRT_SHARED=1)
target_compile_definitions(${__t} INTERFACE BUILD_KAUTIL_QUICK_SOIRT_SHARED=0)

string(APPEND extern_prefix extern)
string(APPEND extern_prefix " ")
string(APPEND extern_prefix \"C\")
string(APPEND extern_prefix " ")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
string(APPEND extern_import ${extern_prefix}__declspec\(dllimport\))
string(APPEND extern_export ${extern_prefix}__declspec\(dllexport\))
endif()

target_compile_definitions(${__t} PRIVATE -DKAUTIL_QUICK_SORRT_PREFIX=${extern_export})
target_compile_definitions(${__t} INTERFACE -DKAUTIL_QUICK_SORRT_PREFIX=${extern_import})
target_include_directories(${__t} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${__t} INTERFACE KAUTIL_QUICK_SORT_SHARED="$<TARGET_FILE:kautil_quick_sort_shared_export>")
add_library(kautil::quick_sort::shared::export ALIAS ${__t})


set(__t kautil_quick_sort_static)
add_library(${__t} STATIC)
file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
target_sources(${__t} PRIVATE ${srcs} )
target_include_directories(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${__t} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${__t} PRIVATE -DKAUTIL_QUICK_SORRT_PREFIX=)
target_compile_definitions(${__t} INTERFACE -DKAUTIL_QUICK_SORRT_PREFIX=)
add_library(kautil::quick_sort::static ALIAS ${__t})


set(__t example_kautil_quick_sort_static)
add_executable(${__t})
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/examples/quick_sort.cc )
target_link_libraries(${__t} PRIVATE kautil::quick_sort::static)
#target_compile_options(${__t} PRIVATE -O2)


# utility for dlopen (LoadLibrary)
add_subdirectory(third_party/kautil_sharedlib)
set(__t example_kautil_quick_sort_dlopen)
add_executable(${__t})
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/examples/example_extern.cc )
target_link_libraries(${__t} PRIVATE kautil::quick_sort::shared::export kautil::sharedlib::nolink::partial)
target_include_directories(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern/include)
