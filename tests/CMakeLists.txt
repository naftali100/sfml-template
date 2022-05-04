set(TEST_NAME test_unit)

file(GLOB_RECURSE test_sources "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_executable(${TEST_NAME} ${test_sources})

target_link_libraries(${TEST_NAME} PRIVATE ${SOURCES_LIB} doctest)
set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME ${SOURCES_LIB}.${TEST_NAME}
    COMMAND ${TEST_NAME}
)
