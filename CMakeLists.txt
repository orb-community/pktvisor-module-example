cmake_minimum_required(VERSION 3.13)

project(visor-handler-example VERSION 1.0.0)

add_subdirectory(pktvisor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Wall -pedantic -W -Wextra -Wno-unknown-pragmas)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/pktvisor/cmake")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Corrade REQUIRED PluginManager)

add_subdirectory(Example)

enable_testing()

