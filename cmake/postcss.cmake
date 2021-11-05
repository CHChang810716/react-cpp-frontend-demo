if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/node_modules/.bin/postcss)
  if(CMAKE_HOST_WIN32)
    execute_process(COMMAND cmd /c "npm i -D postcss postcss-cli")
    execute_process(COMMAND cmd /c "npm install postcss-modules")
  else()
    execute_process(COMMAND npm i -D postcss postcss-cli)
    execute_process(COMMAND npm install postcss-modules)
  endif()
endif()
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/postcss.config.js
  ${CMAKE_CURRENT_BINARY_DIR}/postcss.config.js
)

# Function
#   postcss(<file.css>)
#
# Description:
#   Add command to produce <file.css> from <file.css>.
#
# Notes:
#   The postcss file path must be relative to ${CMAKE_CURRENT_SOURCE_DIR}
#
# Example:
#   postcss(style.css)
function(postcss source)
  get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR}/${source} NAME_WE)
  get_filename_component(src_dir  ${CMAKE_CURRENT_SOURCE_DIR}/${source} DIRECTORY)
  set(gen_dir ${CMAKE_CURRENT_BINARY_DIR})

  if(NOT EXISTS ${gen_dir})
    file(MAKE_DIRECTORY ${gen_dir})
  endif()
  add_custom_target(
    ${name}.css
    COMMAND
      ${CMAKE_CURRENT_BINARY_DIR}/node_modules/.bin/postcss
      ${src_dir}/${name}.css
      -o ${gen_dir}/${name}.css
      --config .
  )
endfunction()
