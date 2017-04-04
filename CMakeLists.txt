cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_VERBOSE_MAKEFILE on)
project(baseline-gl)

set(DEBUG_COMPILER_OPTIONS "-std=c++1z" "-g" "-Wno-missing-braces" "-Wmissing-field-initializers")
set(RELEASE_COMPILER_OPTIONS "-std=c++1z" "-O3" "-Wno-missing-braces" "-Wmissing-field-initializers")

set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")


# Dependencies
# add_subdirectory(vendor/glfw)


# Examples
add_subdirectory(examples)
