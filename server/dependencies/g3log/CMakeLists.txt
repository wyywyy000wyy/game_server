INCLUDE_DIRECTORIES(".")

IF(MSVC)
SET(LIB_SRC_LIST ${LIB_SRC_LIST} 	
	stacktrace_windows.cpp
	crashhandler_windows.cpp
)
ELSE(MSVC)
SET(LIB_SRC_LIST ${LIB_SRC_LIST} 	
	crashhandler_unix.cpp
)
ENDIF(MSVC)

ADD_LIBRARY(g3log STATIC ${LIB_SRC_LIST})

