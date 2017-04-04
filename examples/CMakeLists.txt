# baseline01-glfw example
add_executable(baseline01-glfw baseline01-glfw.cpp)
target_include_directories(baseline01-glfw PRIVATE ${BASELINE_INCLUDES})
target_link_libraries(baseline01-glfw ${OPENGL_LIBS})
