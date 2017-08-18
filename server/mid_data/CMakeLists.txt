
file(GLOB AllFile *)

foreach(var ${AllFile})
if(IS_DIRECTORY ${var})
file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR} ${var})
add_subdirectory(${RelativePath})
endif()
endforeach()
