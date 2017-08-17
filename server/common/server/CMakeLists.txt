
# add_subdirectory(mutitreadServer2)
#add_dependencies(Learn zeromq)
file(GLOB_RECURSE AllFile *.*)

file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(game_server_framework)
	
add_library(${PROJECT_NAME} STATIC ${AllFile})

AllFilesLoad(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})

set_target_properties( ${PROJECT_NAME} PROPERTIES
	FOLDER "Common"
	ARCHIVE_OUTPUT_DIRECTORY ${LearnOutPutDir}
	RUNTIME_OUTPUT_DIRECTORY ${LearnOutPutDir}
	LIBRARY_OUTPUT_DIRECTORY ${LearnOutPutDir} )

# foreach(var ${AllFile})
# if(IS_DIRECTORY ${var})
# file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR} ${var})
# add_subdirectory(${RelativePath})
# endif()
# endforeach()
