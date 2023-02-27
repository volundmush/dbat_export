cmake_minimum_required(VERSION 3.22)

set(CPM_DOWNLOAD_VERSION 0.35.5)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

project(dbate)

CPMAddPackage("gh:nlohmann/json@3.11.2")
find_package(Boost REQUIRED)
find_library(LIBBSD NAMES bsd libbsd REQUIRED)

include_directories(PUBLIC
        include
        ${Boost_INCLUDE_DIRS}
        ${nlohmann_json_SOURCE_DIR}/include,
        )

file(GLOB_RECURSE DBATE_INCLUDE include/*.h)
file(GLOB_RECURSE DBATE_SRC src/*.cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "-fpermissive -w")

add_compile_definitions(HAVE_LIBBSD)

set(BUILD_TESTING OFF)

# this is the core library we're making.
add_library(dbate ${DBATE_INCLUDE} ${DBATE_SRC})
# everything we make will link to it.
link_libraries(dbate bsd)

# the various binaries
add_executable(circle apps/circle.cpp)

target_compile_definitions(dbate PUBLIC USING_CMAKE=1 DBATE_UNIX=1 POSIX=1)

SET(dbate_link ${CMAKE_INSTALL_PREFIX}/bin/)