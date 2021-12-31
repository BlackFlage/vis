CMAKE_MINIMUM_REQUIRED(VERSION 3.19)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(LOGGER_ACTIVE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components/engine)

IF(WIN32)
    add_compile_definitions(main PRIVATE WIN32)
ENDIF()