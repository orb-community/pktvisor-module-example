
## TEST SUITE
add_executable(unit-tests-handler-example
        main.cpp
        test_example.cpp
        )

target_link_libraries(unit-tests-handler-example
        PRIVATE
        ${CONAN_LIBS_JSON-SCHEMA-VALIDATOR}
        Visor::Handler::Example
        )

add_test(NAME unit-tests-handler-example
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
        COMMAND unit-tests-handler-example
        )
