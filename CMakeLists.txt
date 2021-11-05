# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

cmake_minimum_required (VERSION 3.11)
project(asm-dom-cmake
  LANGUAGES CXX
  VERSION 0.1.0
)

# If needed, in release mode, use emscripten optimizations flags.
include(cmake/release-mode.cmake)

string(APPEND CMAKE_CXX_FLAGS " -s ASSERTIONS=1")

# Install gccx if needed. Defines the gccx(..) function to transpile cpx to cpp.
include(cmake/gccx.cmake)

include(cmake/postcss.cmake)

# Add the asm-dom library.
include(cmake/asm-dom.cmake)

postcss(src/style.css)

gccx(src/main.cpx)
add_executable(main src/main.cpp src/style.css)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_link_libraries(main PRIVATE asm-dom)
target_include_directories(main PRIVATE src)
add_dependencies(main style.css)

# Copy the index.html file into the build directory
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/index.html
  ${CMAKE_CURRENT_BINARY_DIR}/index.html
)