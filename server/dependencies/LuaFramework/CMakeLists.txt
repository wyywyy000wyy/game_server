file(GLOB_RECURSE AllFile *.*)


#add_dependencies(Learn zeromq)


file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(${RelativePath})
	
add_executable(${PROJECT_NAME} ${AllFile})

add_dependencies(${PROJECT_NAME} libzmq)

target_link_libraries(${PROJECT_NAME} libzmq)

include_directories(
${SolutionDir}/zeromq-4.2.1/include
${SolutionDir}/zeromq-4.2.1/src
)

AllFilesLoad(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})

set_target_properties( ${PROJECT_NAME} PROPERTIES
	FOLDER "Learn"
	ARCHIVE_OUTPUT_DIRECTORY ${LearnOutPutDir}
	RUNTIME_OUTPUT_DIRECTORY ${LearnOutPutDir}
	LIBRARY_OUTPUT_DIRECTORY ${LearnOutPutDir} )

#target_link_libraries(Test libprotobuf)


