cmake_minimum_required(VERSION 3.10)

project(hash_drag_race)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)


find_package(OpenSSL REQUIRED)

find_path(ISAL_INCLUDE_DIR NAMES isa-l.h)
find_library(ISAL_LIBRARY NAMES isal)

add_library(isal::isal UNKNOWN IMPORTED)
set_target_properties(isal::isal PROPERTIES
    IMPORTED_LOCATION "${ISAL_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ISAL_INCLUDE_DIR}"
)


find_path(XXHASH_INCLUDE_DIR NAMES xxhash.h)
find_library(XXHASH_LIBRARY NAMES xxhash)

add_library(xxhash::xxhash UNKNOWN IMPORTED)
set_target_properties(xxhash::xxhash PROPERTIES
    IMPORTED_LOCATION "${XXHASH_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${XXHASH_INCLUDE_DIR}"
)

add_executable(hash_drag_race
    src/hardware_sha256.hpp
    src/byte_ranges.hpp
    src/djb2.hpp
    src/standard.hpp
    src/crc32_isal.hpp
    src/main.cpp
)

if(ipo_supported)
    set_property(TARGET hash_drag_race PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO/LTO not supported: ${ipo_error}")
endif()

target_link_libraries(hash_drag_race PRIVATE OpenSSL::SSL OpenSSL::Crypto isal::isal xxhash::xxhash)
