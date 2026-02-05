# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/cop290_raj_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/cop290_raj_autogen.dir/ParseCache.txt"
  "cop290_raj_autogen"
  )
endif()
