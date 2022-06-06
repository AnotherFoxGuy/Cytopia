# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.0.22
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_SUBMODULES_RECURSE OFF
        GIT_TAG candidate-2.5.1
)
FetchContent_MakeAvailable(SDL2_image)

FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.0.18
)
FetchContent_MakeAvailable(SDL2_ttf)