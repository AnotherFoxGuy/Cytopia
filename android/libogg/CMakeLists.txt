# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        ogg
        GIT_REPOSITORY https://github.com/xiph/ogg.git
        GIT_TAG        v1.3.5
)
FetchContent_MakeAvailable(ogg)