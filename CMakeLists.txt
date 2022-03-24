cmake_minimum_required(VERSION 3.13)

project(visor-handler-example VERSION 1.0.0)

#build pktvisor project first
add_subdirectory(pktvisor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Wall -pedantic -W -Wextra -Wno-unknown-pragmas)

# Conan Module setup
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/pktvisor/cmake")
include(conan)
conan_cmake_autodetect(CONAN_SETTINGS)
message(STATUS "Detected conan settings: ${CONAN_SETTINGS}")

set(PKTVISOR_CONAN_INIT ON CACHE BOOL "Create new Conan environment for the build.")
set(PKTVISOR_CONAN_BUILD "missing" CACHE STRING "Specify conan packages to build from source. Values are separated by semicolon.")
set(PKTVISOR_CONAN_BUILD_PROFILE "" CACHE STRING "Profile for the build environment.")
set(PKTVISOR_CONAN_HOST_PROFILE "" CACHE STRING "Profile for the host environment.")

if(PKTVISOR_CONAN_INIT)
    message(STATUS "Using new Conan environment")
    set(ENV{CONAN_USER_HOME} ${CMAKE_BINARY_DIR}/conan_home)
    set(ENV{CONAN_REVISIONS_ENABLED} 1)
endif()

conan_cmake_install(
        PATH_OR_REFERENCE ${PROJECT_SOURCE_DIR}
        BUILD ${PKTVISOR_CONAN_BUILD}
        PROFILE_BUILD ${PKTVISOR_CONAN_BUILD_PROFILE}
        PROFILE_HOST ${PKTVISOR_CONAN_HOST_PROFILE}
        GENERATOR cmake
        SETTINGS ${CONAN_SETTINGS}
        INSTALL_FOLDER ${CMAKE_BINARY_DIR}/module) #generate another folder with new module conan files

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)#add pktvisor dependencies
include(${CMAKE_BINARY_DIR}/module/conanbuildinfo.cmake)# add module conan dependencies

conan_basic_setup()

enable_testing()

find_package(Corrade REQUIRED PluginManager)

#Should add new custom pktvisor modules here
add_subdirectory(Example)
