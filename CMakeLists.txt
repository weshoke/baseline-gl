cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_VERBOSE_MAKEFILE on)
project(baseline-gl)

set(DEBUG_COMPILER_OPTIONS "-std=c++1z" "-g" "-Wno-missing-braces" "-Wmissing-field-initializers")
set(RELEASE_COMPILER_OPTIONS "-std=c++1z" "-O3" "-Wno-missing-braces" "-Wmissing-field-initializers")

set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")


# Dependencies
find_library(COCOA_LIBRARY Cocoa)
find_library(OPENGL_LIBRARY OpenGL)

add_subdirectory(vendor/glfw)

add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/deps/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/deps)

set(OPENGL_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
)
set(OPENGL_LIBS
    ${COCOA_LIBRARY}
    ${OPENGL_LIBRARY}
    glfw
    glad
)

set(BASIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/variant/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/filesystem
)

set(BASELINE_INCLUDES
    ${BASIC_INCLUDES}
    ${OPENGL_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Examples
add_subdirectory(examples)
