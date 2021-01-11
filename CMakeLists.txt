cmake_minimum_required(VERSION 3.0.0)
project(omega VERSION 0.1.0)

include(CTest)
enable_testing()



set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "source/*.cc")

add_library(omega SHARED ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(omega PUBLIC
                          "${PROJECT_SOURCE_DIR}",
                          "${PROJECT_SOURCE_DIR}/include",
                          "${PROJECT_SOURCE_DIR}/source"
                          "${PROJECT_SOURCE_DIR}/include/prelude"
                          )

