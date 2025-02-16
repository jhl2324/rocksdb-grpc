cmake_minimum_required(VERSION 3.26)
project(l0_cache_test)

include(../cmake/general.cmake)

file(GLOB _LOCAL_TESTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "test_*.cpp")
list(LENGTH _LOCAL_TESTS _LOCAL_TEST_COUNT)
message("Found ${_LOCAL_TEST_COUNT} tests")

create_test_sourcelist(TESTS
        tests.cpp
        ${_LOCAL_TESTS}
)

add_executable(tests ${TESTS} ${CUSTOM_HEADERS})
target_link_libraries(tests ${LIBRARIES})
list(REMOVE_ITEM TESTS tests.cpp)

set_target_properties(tests
        PROPERTIES
        COMPILE_DEFINITIONS __UNITTEST__
)

foreach (test ${TESTS})
    get_filename_component(TName ${test} NAME_WE)
    message(" - Creating test ${test} -> ${TName}")
    add_test(${TName} tests ${TName})
endforeach (test)
