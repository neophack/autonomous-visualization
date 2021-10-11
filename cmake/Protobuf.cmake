# Locate and configure the Google Protocol Buffers library.
#
# Defines the following variables:
#
#   PROTOBUF_FOUND - Found the Google Protocol Buffers library (libprotobuf & header files)
#   PROTOBUF_ROOT - Then root directory for protocol buffers
#   PROTOBUF_LIBRARY_DIR - The library directory for protocol buffers
#   PROTOBUF_INCLUDE_DIR - The include directory for protocol buffers
#   PROTOBUF_PROTOC_EXECUTABLE - The protoc compiler
#   PROTOC - The protoc compiler
#
#  ====================================================================
set(PROTOBUF_FOUND 1 CACHE INTERNAL "PROTOBUF_FOUND")
set(PROTOBUF_ROOT ${GEARS_ARCH} CACHE INTERNAL "PROTOBUF_ROOT")
set(PROTOBUF_LIBRARY_DIR ${PROTOBUF_ROOT}/lib CACHE INTERNAL "PROTOBUF_LIBRARY_DIR")
set(PROTOBUF_INCLUDE_DIR ${PROTOBUF_ROOT}/include CACHE INTERNAL "PROTOBUF_INCLUDE_DIR")
file(GLOB LIBRARIES "${PROTOBUF_LIBRARY_DIR}/*protobuf*.so")
set(PROTOBUF_LIBRARIES ${LIBRARIES} CACHE INTERNAL "PROTOBUF_LIBRARIES")
set(PROTOBUF_PROTOC_EXECUTABLE ${PROTOBUF_ROOT}/bin/protoc CACHE INTERNAL "PROTOBUF_PROTOC_EXECUTABLE")
set(PROTOC ${PROTOBUF_PROTOC_EXECUTABLE} CACHE INTERNAL "PROTOC")
set(WORK_ROOT ${CMAKE_SOURCE_DIR}/.. CACHE INTERNAL "WORK_ROOT")
include_directories(${PROTOBUF_INCLUDE_DIR})
link_directories(${PROTOBUF_LIBRARY_DIR})

#  ====================================================================
#
# PROTOBUF_GENERATE_CPP (public function)
#   SRCS = Variable to define with autogenerated
#          source files
#   HDRS = Variable to define with autogenerated
#          header files
#   ARGN = proto files
#
#  ====================================================================
function(PROTOBUF_GENERATE_CPP SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: PROTOBUF_GENERATE_CPP() called without any proto files")
    return()
  endif(NOT ARGN)

  if(PROTOBUF_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(ABS_PATH ${ABS_FIL} PATH)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
        list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  else()
    set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(DIR ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
        list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  endif()

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
    list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc"
             "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h"
      COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --cpp_out  ${CMAKE_CURRENT_BINARY_DIR} ${_protobuf_include_path} ${ABS_FIL}
      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ protocol buffer compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

#  ====================================================================
#
# PROTOBUF_GENERATE_CPP_EXTRA_OUT_SOURCE_DIR (public function)
#     SRCS = Variable to define with autogenerated
#            source files
#     HDRS = Variable to define with autogenerated
#            header files
# OUT_PATH = Variable to define with cpp_extra out
#            dir, relative with current source dir.
#     ARGN = proto files
#
#  ====================================================================
function(PROTOBUF_GENERATE_CPP_EXTRA_OUT_SOURCE_DIR SRCS HDRS OUT_PATH)
  if(NOT ARGN)
    message(SEND_ERROR "Error: PROTOBUF_GENERATE_CPP() called without any proto files")
    return()
  endif(NOT ARGN)

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
    list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

    add_custom_command(
        #OUTPUT "${ABS_FIL_PRE}.pb.cc"
        #"${ABS_FIL_PRE}.pb.h"
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc"
               "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h"
      COMMAND  ${PROTOC}
      ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR}
           --cpp_out ${CMAKE_CURRENT_SOURCE_DIR}/${OUT_PATH}
           --proto_path ${CMAKE_CURRENT_SOURCE_DIR}
           ${ABS_FIL}

      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ protocol buffer compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

# By default have PROTOBUF_GENERATE_CPP macro pass -I to protoc
# for each directory where a proto file is referenced.
if(NOT DEFINED PROTOBUF_GENERATE_CPP_APPEND_PATH)
  set(PROTOBUF_GENERATE_CPP_APPEND_PATH TRUE)
endif()