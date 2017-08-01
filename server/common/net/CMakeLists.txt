
# add_subdirectory(mutitreadServer2)
#add_dependencies(Learn zeromq)
file(GLOB_RECURSE AllFile *.*)

file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(game_net)
	
add_library(${PROJECT_NAME} STATIC ${AllFile})

# add_dependencies(${PROJECT_NAME} libzmq enet)

# if(WIN32)
# target_link_libraries(${PROJECT_NAME} Winmm)
# endif()
# target_link_libraries(${PROJECT_NAME} libzmq enet)

include_directories(
# ${SolutionDir}/zeromq-4.2.1/include
# ${SolutionDir}/zeromq-4.2.1/src
${SolutionDir}/dependencies/asio/include
)

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
