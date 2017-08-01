file(GLOB_RECURSE AllFile *.*)


#add_dependencies(Learn zeromq)


file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(${RelativePath})
	
add_library(${PROJECT_NAME} STATIC ${AllFile})
#add_executable(${PROJECT_NAME} ${AllFile})

AllFilesLoad(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})

set_target_properties( ${PROJECT_NAME} PROPERTIES
	FOLDER "Lua"
	ARCHIVE_OUTPUT_DIRECTORY ${LearnOutPutDir}
	RUNTIME_OUTPUT_DIRECTORY ${LearnOutPutDir}
	LIBRARY_OUTPUT_DIRECTORY ${LearnOutPutDir} )

#target_link_libraries(Test libprotobuf)


