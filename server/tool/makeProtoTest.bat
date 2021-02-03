protoc --cpp_out=. NetPackDefine.proto
move NetPackDefine.pb.cc ..\common\net
move NetPackDefine.pb.h ..\common\net
pause