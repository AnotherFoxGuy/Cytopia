# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(libogg REQUIRED CONFIG)
add_library(Ogg::ogg ALIAS libogg::ogg)

set(OGG_FOUND TRUE)
get_target_property(OGG_INCLUDE_DIR Ogg::ogg INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(OGG_LIBRARY Ogg::ogg IMPORTED_LOCATION)

FetchContent_Declare(
        libvorbis
        GIT_REPOSITORY https://github.com/xiph/vorbis.git
        GIT_TAG v1.3.7
)
FetchContent_MakeAvailable(libvorbis)