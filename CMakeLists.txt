cmake_minimum_required(VERSION 3.13)

project(visor-handler-example VERSION 1.0.0)

add_subdirectory(pktvisor)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/pktvisor/cmake")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Corrade REQUIRED PluginManager)

add_subdirectory(Example)
