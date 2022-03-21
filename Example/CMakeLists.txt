message(STATUS "Handler Module: Example (dynamic)")

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

#creates static module to allow unit testing easily
corrade_add_static_plugin(VisorHandlerExample
        ${CMAKE_CURRENT_BINARY_DIR}
        VisorHandlerExample.conf
        ExampleHandlerModulePlugin.cpp
        ExampleStreamHandler.cpp
        )
add_library(Visor::Handler::Example ALIAS VisorHandlerExample)

target_include_directories(VisorHandlerExample
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

target_link_libraries(VisorHandlerExample
        PUBLIC
        Visor::Input::Pcap
        Visor::Input::Mock
        Visor::Input::Dnstap
        )

#Then creates the dynamic module linking the static module
corrade_add_plugin(VisorHandlerExampleDyn
        ${CMAKE_CURRENT_BINARY_DIR}
        ""
        VisorHandlerExample.conf
        ExampleHandlerModulePlugin.cpp
        )
add_library(Visor::Handler::Example::Dynamic ALIAS VisorHandlerExampleDyn)

target_link_libraries(VisorHandlerExampleDyn
        VisorHandlerExample
        )

#add_subdirectory(tests)