
# add_subdirectory(mutitreadServer2)
#add_dependencies(Learn zeromq)
file(GLOB_RECURSE AllFile *.*)

file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(game_map)
	
add_library(${PROJECT_NAME} ${AllFile})

add_dependencies(${PROJECT_NAME} game_core)

# if(WIN32)
# target_link_libraries(${PROJECT_NAME} Winmm)
# endif()
# target_link_libraries(${PROJECT_NAME} libzmq enet)

include_directories(
${SolutionDir}/common/
# ${SolutionDir}/zeromq-4.2.1/src
# ${SolutionDir}/enet/include
)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	FOLDER "Common"
	ARCHIVE_OUTPUT_DIRECTORY ${LearnOutPutDir}
	RUNTIME_OUTPUT_DIRECTORY ${LearnOutPutDir}
	LIBRARY_OUTPUT_DIRECTORY ${LearnOutPutDir} )

AllFilesLoad(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})

