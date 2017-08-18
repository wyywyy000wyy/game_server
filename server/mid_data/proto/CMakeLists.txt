
if(WIN32)
file(GLOB out_files ${OUT_PUT_PROTO_FILE}/*.cc ${OUT_PUT_PROTO_FILE}/*.h)
foreach(iFile ${out_files})
message(${iFile})
file(REMOVE ${iFile})
endforeach()

file(GLOB proto_files *.proto)
set(proto_tool ${SolutionDir}/tool/protoc.exe)

foreach(iFile ${proto_files})
file(RELATIVE_PATH protoFile ${CMAKE_CURRENT_SOURCE_DIR} ${iFile})
execute_process(COMMAND  ${proto_tool} -I=. --cpp_out=. --proto_path=${CMAKE_CURRENT_SOURCE_DIR} ${protoFile} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE rv)
endforeach()

file(GLOB out_files *.cc *.h)
foreach(iFile ${out_files})
file(RELATIVE_PATH protoFile ${CMAKE_CURRENT_SOURCE_DIR} ${iFile})
file(RENAME ${iFile} ${OUT_PUT_PROTO_FILE}/${protoFile})
endforeach()
endif()