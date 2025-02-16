cmake_minimum_required(VERSION 3.26)
project(dtkrby)

include(cmake/general.cmake)

add_executable(krby-daemon src/daemon.cpp ${CUSTOM_HEADERS})
target_link_libraries(krby-daemon ${LIBRARIES})

add_subdirectory(benchmarks)

enable_testing()
add_subdirectory(tests)
