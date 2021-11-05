# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

# gccx target is completed whenever the "gccx" command is available.
if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/node_modules/.bin/gccx)
  if(CMAKE_HOST_WIN32)
    execute_process(COMMAND cmd /c "npm install ${CMAKE_SOURCE_DIR}/lib/gccx")
  else()
    execute_process(COMMAND npm install ${CMAKE_SOURCE_DIR}/lib/gccx)
  endif()
endif()

# Function
#   gccx(<file.cx>)
#
# Description:
#   Add command to produce <file.cpp> from <file.cpx>.
#
# Notes:
#   The gccx file path must be relative to ${CMAKE_CURRENT_SOURCE_DIR}
#
# Example:
#   gccx(main.cpx)
function(gccx source)
  get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR}/${source} NAME_WE)
  get_filename_component(src_dir  ${CMAKE_CURRENT_SOURCE_DIR}/${source} DIRECTORY)
  get_filename_component(gen_dir  ${CMAKE_CURRENT_BINARY_DIR}/${source} DIRECTORY)

  if(NOT EXISTS ${gen_dir})
    file(MAKE_DIRECTORY ${gen_dir})
  endif()

  add_custom_command(
    OUTPUT
      ${gen_dir}/${name}.cpp
    COMMAND
      ${CMAKE_CURRENT_BINARY_DIR}/node_modules/.bin/gccx
    ARGS
      ${src_dir}/${name}.cpx
      -o ${gen_dir}/${name}.cpp
    MAIN_DEPENDENCY
      ${src_dir}/${name}.cpx
    )
endfunction()
