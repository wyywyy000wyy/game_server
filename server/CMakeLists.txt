set_property(GLOBAL PROPERTY USE_FOLDERS On)

option(BUILD_TOOLS_ONLY "help string describing option")

cmake_minimum_required(VERSION 3.1)
macro(remove_file arg_list file_remove)
	file(GLOB RemoveItems_Cpp ${file_remove})
	list(REMOVE_ITEM ${arg_list} ${RemoveItems_Cpp})
endmacro(remove_file)

macro(link_NFSDK projName)
if(UNIX)
	add_dependencies(${projName} GFCore)
	target_link_libraries(${projName} GFCore)
else()
	add_dependencies(${projName} GFCore)
	target_link_libraries(${projName} GFCore)
endif()
endmacro(link_NFSDK)

macro(add_post_cmd_win strProjectName destDir ext dbgSuffix)
	
endmacro()

macro(add_post_cmd_linux strProjectName destDir ext dbgSuffix dllPrefix)
	
endmacro()

		

project(server)

set(SolutionDir ${PROJECT_SOURCE_DIR})
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		set(LearnOutPutDir ${PROJECT_BINARY_DIR}/_Out/Debug)
	else()
		set(LearnOutPutDir ${PROJECT_BINARY_DIR}/_Out/Release)
	endif()
else()
	set(LearnOutPutDir ${PROJECT_BINARY_DIR}/_Out/)
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(MSVC)
	ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
ELSE(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
ENDIF(MSVC)

ADD_DEFINITIONS(-DASIO_STANDALONE=1 
				-DASIO_HAS_STD_ADDRESSOF
				-DASIO_HAS_STD_ARRAY
			    	-DASIO_HAS_STD_ATOMIC
				-DASIO_HAS_CSTDINT
				-DASIO_HAS_STD_TYPE_TRAITS
				-DASIO_HAS_STD_SHARED_PTR)

# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# message(STATUS "SolutionDir=" ${SolutionDir})
include_directories(
${SolutionDir} 
${SolutionDir}/dependencies/asio/include
${SolutionDir}/dependencies/protobuf/src
${SolutionDir}/dependencies/g3log
${SolutionDir}/dependencies/spdlog
${SolutionDir}/dependencies/boost
)

#message("Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})
message("UNIT=" ${UNIX})
if(UNIX)
	if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -Wall -g -ggdb -DDEBUG -fPIC")
	else()
		set(CMAKE_BUILD_TYPE "Release")
		set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fPIC -std=c++11 -O3 -Wall")
	endif()
	set(LDFLAGS "$ENV{LDFLAGS} -stdlib=libc++")
	add_definitions(-std=c++11)
else()
	SET ( CMAKE_CXX_FLAGS "-D_WINDOWS /EHsc" )
endif()

function(AllFilesLoad CurPath CurGroup)
file(GLOB Cur_Files ${CurPath}/*.*)
source_group(${CurGroup}  FILES ${Cur_Files})
file(GLOB files ${CurPath}/*)	
foreach(var ${files})
if(IS_DIRECTORY ${var})
file(RELATIVE_PATH RelativePath ${CurPath} ${var})
set(childGroup ${CurGroup}\\${RelativePath})
AllFilesLoad(${var} ${childGroup})
endif()
endforeach()	
endfunction(AllFilesLoad)

message("Build All")

add_subdirectory(test_server)
add_subdirectory(test_client)
add_subdirectory(world_server)
add_subdirectory(common)
add_subdirectory(dependencies/cpp_redis)
add_subdirectory(dependencies/protobuf/cmake)
add_subdirectory(dependencies/g3log)
add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/zeromq)
# add_subdirectory(dependencies/poco-develop)
# add_subdirectory(zmqpp-develop)



