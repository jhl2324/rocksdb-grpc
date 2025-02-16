cmake_minimum_required(VERSION 3.26)
project(benchmarks)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_library(ROCKSDB_LIBRARY rocksdb)

set(PROTO_DIR ${CMAKE_SOURCE_DIR}/include/wise/api)
set(PROTO_SRCS ${CMAKE_BINARY_DIR}/grpc_service.pb.cc ${CMAKE_BINARY_DIR}/grpc_service.grpc.pb.cc)
set(PROTO_HDRS ${CMAKE_BINARY_DIR}/grpc_service.pb.h ${CMAKE_BINARY_DIR}/grpc_service.grpc.pb.h)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_DIR}/grpc_service.proto)

include(../cmake/general.cmake)

file(GLOB _BENCHMARKS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
list(LENGTH _BENCHMARKS _BENCHMARK_COUNT)
message("Found ${_BENCHMARK_COUNT} benchmarks")

foreach (_BENCH ${_BENCHMARKS})
    get_filename_component(BENCH_NAME ${_BENCH} NAME_WE)
    message(" - Creating benchmark ${_BENCH} -> ${BENCH_NAME}")
    add_executable(${BENCH_NAME} ${_BENCH} ${CUSTOM_HEADERS})
    target_link_libraries(${BENCH_NAME} ${LIBRARIES})
endforeach (_BENCH)

add_executable(grpc_server
    src/wise/protocol/grpc_server.cpp
    src/wise/storage/rocksdb_adapter.cpp
    ${PROTO_SRCS}
)
target_link_libraries(grpc_server protobuf::libprotobuf gRPC::grpc++ ${ROCKSDB_LIBRARY})

add_executable(grpc_client
    src/wise/protocol/grpc_client.cpp
    ${PROTO_SRCS}
)
target_link_libraries(grpc_client protobuf::libprotobuf gRPC::grpc++)

add_executable(grpc_server_test
    src/tests/grpc_server_test.cpp
    src/wise/protocol/grpc_server.cpp
    src/wise/storage/rocksdb_adapter.cpp
    ${PROTO_SRCS}
)
target_link_libraries(grpc_server_test protobuf::libprotobuf gRPC::grpc++ ${ROCKSDB_LIBRARY})

add_executable(grpc_client_test
    src/tests/grpc_client_test.cpp
    src/wise/protocol/grpc_client.cpp
    ${PROTO_SRCS}
)
target_link_libraries(grpc_client_test protobuf::libprotobuf gRPC::grpc++)
