cmake_minimum_required(VERSION 3.5.1)

project(FlatbuffersZmqTutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(Red         "${Esc}[31m")

find_program(FLATBUFFERS_COMPILER flatc)
if (NOT FLATBUFFERS_COMPILER)
    message(FATAL_ERROR "${Red}Flatc not found${ColourReset}")
endif()

set(schema_path "schema.fbs")
get_filename_component(fb_path ${schema_path} ABSOLUTE)

if(NOT EXISTS ${fb_path})
  message(FATAL_ERROR "${Red}Schema ${schema_path} not found${ColourReset}")
endif()

set(schema_build_path "${CMAKE_CURRENT_BINARY_DIR}/schema")
set(schema "${schema_build_path}/schema_generated.h")
add_custom_command(
  OUTPUT "${schema}"
  COMMAND ${FLATBUFFERS_COMPILER}
  ARGS  -o ${schema_build_path}  
    -c 
    ${fb_path}
  COMMENT "Creating ${schema}"
  DEPENDS ${fb_path}
)

foreach(_target echo reader writer)
   add_executable(${_target} "${_target}.cpp" ${schema})
   target_include_directories(${_target} PRIVATE  ${schema_build_path})
   target_link_libraries(${_target} zmq)
endforeach()