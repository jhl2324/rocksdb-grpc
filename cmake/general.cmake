if (__SET_ARCH__)
else ()
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm|^aarch")
        set(CMAKE_C_FLAGS "-arch arm64 ${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "-arch arm64 ${CMAKE_CXX_FLAGS}")
    endif ()
endif ()
set(__SET_ARCH__ TRUE)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------
# Find dependencies
if (NOT DEFINED LIBRARIES)
    set(LIBRARIES "")
    include("${CMAKE_SOURCE_DIR}/cmake/find-dependencies.cmake")
endif ()

# ------------------------------
# Local Headers
set(CUSTOM_HEADERS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories(${CUSTOM_HEADERS_INCLUDE_DIR})

set(CUSTOM_HEADERS "")
file(GLOB_RECURSE CUSTOM_HEADERS
        "${CUSTOM_HEADERS_INCLUDE_DIR}/*.cpp"
        "${CUSTOM_HEADERS_INCLUDE_DIR}/*.h"
)
