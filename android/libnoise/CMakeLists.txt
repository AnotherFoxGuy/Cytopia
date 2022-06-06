# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        libnoise
        GIT_REPOSITORY https://github.com/qknight/libnoise.git
)
FetchContent_MakeAvailable(libnoise)