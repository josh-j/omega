cmake_minimum_required(VERSION 3.0.0)
project(omega_test VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated-declarations")

file(GLOB SOURCES "*.cc")

link_directories("~/Projects/omega/build")
add_executable(omega_test ${SOURCES})
target_link_libraries(omega_test omega "-framework OpenGL") 


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#include_directories(omega_teset PUBLIC "~/Projects/omega/include/")
target_include_directories(omega_test PUBLIC "~/Projects/omega/include/" "~/Projects/omega/build")
#target_include_directories(omega_test PUBLIC
#                          "../${PROJECT_SOURCE_DIR}/include",
#                          "../${PROJECT_SOURCE_DIR}/include/prelude"
#                          )

