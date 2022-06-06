# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        libpng
        GIT_REPOSITORY https://github.com/glennrp/libpng.git
        GIT_TAG v1.6.37
)
FetchContent_MakeAvailable(libpng)