# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(build_wrapper)

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.0.22
)
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.0.5
)

FetchContent_Declare(
        SDL_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.0.18
)
FetchContent_MakeAvailable(SDL SDL_image SDL_ttf)