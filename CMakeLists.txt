cmake_minimum_required(VERSION 3.20)
project(PluginArchitecture)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The built binaries should be placed at bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# The build libraries should be placed at lib/ directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Load in yaml-cpp and if it does not exist in the system,
# automatially get it from the internet
# First try to find yaml-cpp on the system
find_package(yaml-cpp QUIET)

# Find libltdl
# Find libltdl directly
find_library(LTDL_LIBRARY NAMES ltdl)
find_path(LTDL_INCLUDE_DIR NAMES ltdl.h)
include_directories(${LTDL_INCLUDE_DIR})

if(NOT yaml-cpp_FOUND)
    message(STATUS "yaml-cpp not found on system, fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
    )
    FetchContent_MakeAvailable(yaml-cpp)
else()
    message(STATUS "Found yaml-cpp on system")
endif()


include_directories(include)
add_subdirectory(src)

