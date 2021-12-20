cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(visor-handler-example VERSION 3.4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Wall -pedantic -W -Wextra -Wno-unknown-pragmas)

include(conan)
conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}
        BUILD missing
        GENERATOR cmake
        SETTINGS ${settings}
        INSTALL_FOLDER ${CMAKE_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Corrade REQUIRED PluginManager)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_subdirectory(3rd)

corrade_add_plugin(VisorHandlerExample
        ${CMAKE_CURRENT_BINARY_DIR}
        ""
        VisorHandlerExample.conf
        ExampleHandlerModulePlugin.cpp
        ExampleStreamHandler.cpp)
add_library(Visor::Handler::Example ALIAS VisorHandlerExample)

target_include_directories(VisorHandlerExample
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
        #path to core headers
        ${CMAKE_CURRENT_SOURCE_DIR}/../../
        #path to input headers
        ${CMAKE_CURRENT_SOURCE_DIR}/../../inputs/mock
        )

target_link_libraries(VisorHandlerExample
        PUBLIC
        rng
        timer
        datasketches
        )
