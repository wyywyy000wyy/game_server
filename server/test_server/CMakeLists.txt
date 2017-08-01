
# add_subdirectory(mutitreadServer2)
#add_dependencies(Learn zeromq)
file(GLOB_RECURSE AllFile *.*)

file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR})

project(${RelativePath})
	
add_executable(${PROJECT_NAME} ${AllFile})

# add_dependencies(${PROJECT_NAME} libzmq enet)
add_dependencies(${PROJECT_NAME} PocoNet PocoData game_async)

#target_link_libraries(${PROJECT_NAME} cpp_redis game_data game_net libprotobuf g3log game_core PocoNet)
target_link_libraries(${PROJECT_NAME} PocoNet PocoData game_async)

# if(WIN32)
# target_link_libraries(${PROJECT_NAME} Winmm)
# endif()
# target_link_libraries(${PROJECT_NAME} libzmq enet)

include_directories(
${SolutionDir}/common/

${SolutionDir}/dependencies/poco-develop
# ${SolutionDir}/zeromq-4.2.1/include
# ${SolutionDir}/zeromq-4.2.1/src
# ${SolutionDir}/enet/include
)

# SET(CMAKE_BINARY_DIR ${LearnOutPutDir})

AllFilesLoad(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})

set_target_properties( ${PROJECT_NAME} PROPERTIES
	FOLDER "Test"
	ARCHIVE_OUTPUT_DIRECTORY ${LearnOutPutDir}
	RUNTIME_OUTPUT_DIRECTORY ${LearnOutPutDir}
	LIBRARY_OUTPUT_DIRECTORY ${LearnOutPutDir} )

# foreach(var ${AllFile})
# if(IS_DIRECTORY ${var})
# file(RELATIVE_PATH RelativePath ${CMAKE_CURRENT_SOURCE_DIR} ${var})
# add_subdirectory(${RelativePath})
# endif()
# endforeach()
