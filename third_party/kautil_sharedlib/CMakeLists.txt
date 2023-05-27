
# from
# VERSIO INFO
# checksum : 86e8a045bae3c36bbc047f81d8b34cc2a8922fd6
# repo     : https://source.developers.google.com/p/just-a-training/r/example/gumbo


cmake_minimum_required(VERSION 3.20)
project(Kautil
        LANGUAGES C CXX
        VERSION 0.0.0.0
        )
set(CMAKE_CXX_STANDARD 17)




set(__t kautil_sharedlib)
add_library(${__t} STATIC)
target_sources(${__t} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/sharedlib.cc
        )
target_compile_definitions(${__t} PRIVATE KAUTIL_NOLINK_STATIC)
target_include_directories(${__t} PRIVATE include)
target_include_directories(${__t} INTERFACE include)
add_library(kautil::sharedlib ALIAS ${__t})

set(__t kautil_nolink)
add_library(${__t} STATIC)
target_sources(${__t} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/nolink.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/sharedlib.cc
        )
target_compile_definitions(${__t} PRIVATE KAUTIL_NOLINK_STATIC)
target_include_directories(${__t} PRIVATE include)
target_include_directories(${__t} INTERFACE include)
add_library(kautil::nolink ALIAS ${__t})

### @brief
###        kautil_nolink_shared          => ordinal library
###        kautil_nolink_nolink_pure     => all should be initialzed manually (may improve 50ms~100ms at compilation time )
###        kautil_nolink_nolink_partial  => For simplicity. partially includes statically linked symbol
###        kautil_nolink_protocol        => For implementation. think this of like a inheritance

set(kautil_nolink_shared_version 0 )
set(__t kautil_nolink_shared)
add_library(${__t} SHARED)
target_compile_definitions(${__t} PRIVATE KAUTIL_NOLINK_SHARED)
add_library(kautil::sharedlib::nolink::shared ALIAS ${__t})
target_sources(${__t} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/nolink.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/sharedlib.cc
        )
target_include_directories(${__t} PRIVATE include)
target_include_directories(${__t} INTERFACE include)
target_compile_definitions(${__t} PRIVATE -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version})
target_compile_definitions(${__t} INTERFACE -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version})


set(__t kautil_nolink_nolink_pure)
add_library(${__t} INTERFACE)
target_include_directories(${__t} INTERFACE include)
target_compile_definitions(${__t} INTERFACE -DKAUTIL_NOLINK_SO="$<TARGET_FILE:kautil::sharedlib::nolink::shared>" )
target_compile_definitions(${__t} INTERFACE -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version})
add_library(kautil::sharedlib::nolink::pure ALIAS ${__t})


set(__t kautil_nolink_partial)
add_library(${__t} STATIC)
target_compile_definitions(${__t} PRIVATE KAUTIL_NOLINK_SHARED)
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/sharedlib.cc)
target_include_directories(${__t} PRIVATE include)
target_include_directories(${__t} INTERFACE include)
target_compile_definitions(${__t} PRIVATE KAUTIL_SHAREDLIB_BUILD_STAGE=1)
target_compile_definitions(${__t} PRIVATE
        -DKAUTIL_NOLINK_SO="$<TARGET_FILE:kautil::sharedlib::nolink::shared>"
        -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version}
        )
target_compile_definitions(${__t} INTERFACE
        -DKAUTIL_NOLINK_SO="$<TARGET_FILE:kautil::sharedlib::nolink::shared>"
        -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version}
        )
add_library(kautil::sharedlib::nolink::partial ALIAS ${__t})

set(__t kautil_nolink_version_table_shared)
add_library(${__t} SHARED)
target_compile_definitions(${__t} PRIVATE KAUTIL_NOLINK_SHARED)
target_compile_definitions(${__t} PRIVATE KAUTIL_SHAREDLIB_BUILD_STAGE=1)
target_include_directories(${__t} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${__t} INTERFACE include)
target_sources(${__t} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/version_table.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kautil/sharedlib/sharedlib.cc
        )
target_compile_definitions(${__t} PRIVATE
        -DKAUTIL_VERSION_TABLE_VERSION=${kautil_nolink_shared_version}
        )
target_compile_definitions(${__t} INTERFACE
        -DKAUTIL_VERSION_TABLE_VERSION=${kautil_nolink_shared_version}
        )
add_library(kautil::version_table::shared ALIAS ${__t})


set(__t kautil_nolink_version_table_nolink)
add_library(${__t} INTERFACE)
target_include_directories(${__t} INTERFACE include)
target_compile_definitions(${__t} INTERFACE
        -DKAUTIL_VERSION_TABLE_VERSION=${kautil_nolink_shared_version}
        -DKAUTIL_VERSION_TABLE_SO="$<TARGET_FILE:kautil::version_table::shared>"
        )
add_library(kautil::version_table::nolink ALIAS ${__t})


set(__t kautil_nolink_protocol)
add_library(${__t} INTERFACE)
target_include_directories(${__t} INTERFACE include)
target_compile_definitions(${__t} INTERFACE
        -DKAUTIL_NOLINK_SO="$<TARGET_FILE:kautil::sharedlib::nolink::shared>"
        -DKAUTIL_NOLINK_SHARED_VERSION=${kautil_nolink_shared_version}
        )
add_library(kautil::sharedlib::nolink::protocol ALIAS ${__t} )

