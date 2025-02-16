if (EXISTS "$ENV{MONGOCXX_DRIVER_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{MONGOCXX_DRIVER_PATH}")
endif ()
if (EXISTS "$ENV{ROCKSDB_DRIVER_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{ROCKSDB_DRIVER_PATH}")
endif ()
if (EXISTS "$ENV{ZLIB_PATH}")
    set(ZLIB_LIBRARY "$ENV{ZLIB_PATH}/lib")
    set(ZLIB_INCLUDE_DIR "$ENV{ZLIB_PATH}/include")
endif ()

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
find_package(RocksDB REQUIRED)

get_target_property(MONGOCXX_PATH mongo::mongocxx_shared IMPORTED_LOCATION_RELEASE)
get_target_property(BSONCXX_PATH mongo::bsoncxx_shared IMPORTED_LOCATION_RELEASE)
get_target_property(ROCKSDB_PATH RocksDB::rocksdb-shared IMPORTED_LOCATION_RELEASE)

if (NOT DEFINED MONGOCXX_PATH)
    message(FATAL_ERROR "Cannot found mongocxx")
endif ()
if (NOT DEFINED BSONCXX_PATH)
    message(FATAL_ERROR "Cannot found bsoncxx")
endif ()
if (NOT DEFINED ROCKSDB_PATH)
    message(FATAL_ERROR "Cannot found RocksDB")
endif ()

list(APPEND LIBRARIES
        "mongo::mongocxx_shared"
        "mongo::bsoncxx_shared"
        "RocksDB::rocksdb"
)
