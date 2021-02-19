# cmake_minimum_required(VERSION 3.0.0)
# project(omega_test VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 17)
# #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated-declarations")

# file(GLOB SOURCES "*.cc")


# if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#     set(MACOSX TRUE)
# endif()

# link_directories("~/Projects/omega/build")
# add_executable(omega_test ${SOURCES})

# if (MACOSX)
#    target_link_libraries(omega_test omega_lib "-framework OpenGL -framework GLUT")
# else()
#    target_link_libraries(omega_test omega_lib -lGL -lGLU -lglut)
# endif()
# #include_directories(omega_teset PUBLIC "~/Projects/omega/include/")
# target_include_directories(omega_test PUBLIC "~/Projects/omega/include/" "~/Projects/omega/build")
# #target_include_directories(omega_test PUBLIC
# #                          "../${PROJECT_SOURCE_DIR}/include",
# #                          "../${PROJECT_SOURCE_DIR}/include/prelude"
# #                          )

add_executable(omega_test main.cc renderer_ogl.cc client.cc renderer_ogl.h client.h)
target_compile_features(omega_test PUBLIC cxx_std_17)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

target_include_directories(omega_test PUBLIC ${FREETYPE_INCLUDE_DIRS})

#if (MACOSX) # TODO: find better way
#   target_link_libraries(omega_test PUBLIC omega_lib "-framework OpenGL -framework GLUT")
#else()
   target_link_libraries(omega_test PUBLIC omega_lib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${FREETYPE_LIBRARIES})
#endif()
