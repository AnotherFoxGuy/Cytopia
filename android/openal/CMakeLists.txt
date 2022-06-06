# ensure cmake features we need
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(build_wrapper)

if (ANDROID_ABI STREQUAL x86)
    set(ANDROID_ARM_NEON ON CACHE INTERNAL "" FORCE)
    set(ALSOFT_CPUEXT_NEON ON CACHE INTERNAL "" FORCE)
else ()
    set(ANDROID_ARM_NEON OFF CACHE INTERNAL "" FORCE)
    set(ALSOFT_CPUEXT_NEON OFF CACHE INTERNAL "" FORCE)
endif ()

include(FetchContent)
include(../BuildHelper.cmake)

FetchContent_Declare(
        openal
        GIT_REPOSITORY https://github.com/kcat/openal-soft.git
        GIT_TAG 1.22.0
)
FetchContent_MakeAvailable(openal)