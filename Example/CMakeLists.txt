

corrade_add_plugin(VisorHandlerExample
        ${CMAKE_CURRENT_BINARY_DIR}
        ""
        Example/VisorHandlerExample.conf
        Example/ExampleHandlerModulePlugin.cpp
        Example/ExampleStreamHandler.cpp)
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