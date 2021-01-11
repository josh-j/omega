cmake_minimum_required(VERSION 3.0.0)
project(omega_test VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "*.cc")

add_executable(omega_test ${SOURCES})
target_link_libraries(omega_test omega) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(omega_test PUBLIC . ../include/prelude)
#target_include_directories(omega_test PUBLIC
#                          "../${PROJECT_SOURCE_DIR}/include",
#                          "../${PROJECT_SOURCE_DIR}/include/prelude"
#                          )

