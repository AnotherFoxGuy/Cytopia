# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.2.12
)
FetchContent_MakeAvailable(zlib)