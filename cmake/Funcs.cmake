function(INCLUDE_SUBDIRS ROOT)
  file(GLOB children RELATIVE ${ROOT} ${ROOT}/*)
  set(sub_dirs "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND sub_dirs ${child})
    endif()
  endforeach()
  include_directories(${ROOT} ${sub_dirs})
endfunction()