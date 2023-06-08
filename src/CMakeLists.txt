# CMakeLists.txt
#
# Copyright 2021 by
# Jordi Espada
#
# Say
#
#   cmake CMakeLists.txt
#
# to create a Makefile that builds a static version of the library.  For a
# dynamic library, use
#
#   cmake CMakeLists.txt -DBUILD_SHARED_LIBS:BOOL=true
#
# instead.  Please refer to the cmake manual for further options, in
# particular, how to modify compilation and linking parameters.
#

cmake_minimum_required(VERSION 3.15)
 
project(zetjsoncpp)

IF( NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE Release )
ENDIF()

set(POST_NAME "")
set(IS_DEBUG FALSE)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(IS_DEBUG TRUE)
	SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__DEBUG__ ")
	set( POST_NAME "_d")
endif()

MESSAGE ("-- Target: " ${CMAKE_BUILD_TYPE})

file(READ "zetjsoncpp.h" zetjsoncpp_h)

string(REGEX MATCH "ZETJSONCPP_VERSION_MAJOR ([0-9]*)" _ ${zetjsoncpp_h})
set(ZETJSONCPP_VERSION_MAJOR ${CMAKE_MATCH_1})

string(REGEX MATCH "ZETJSONCPP_VERSION_MINOR ([0-9]*)" _ ${zetjsoncpp_h})
set(ZETJSONCPP_VERSION_MINOR ${CMAKE_MATCH_1})

string(REGEX MATCH "ZETJSONCPP_VERSION_PATCH ([0-9]*)" _ ${zetjsoncpp_h})
set(ZETJSONCPP_VERSION_PATCH ${CMAKE_MATCH_1})


MESSAGE("-- zetjsoncpp version ${ZETJSONCPP_VERSION_MAJOR}.${ZETJSONCPP_VERSION_MINOR}.${ZETJSONCPP_VERSION_PATCH}" )

set(ZETJSONCPP_LIB_NAME "zetjsoncpp-${ZETJSONCPP_VERSION_MAJOR}-${ZETJSONCPP_VERSION_MINOR}-${ZETJSONCPP_VERSION_PATCH}")



#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# MACRO UTILS
#

MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)

    FOREACH(HEADER ${${HEADER_LIST}})
        get_filename_component(DIR ${HEADER} DIRECTORY)
        INSTALL(FILES ${HEADER} DESTINATION include/zetjsoncpp/${DIR})
    ENDFOREACH(HEADER)

ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

#--------------
#
# COMMON PARAMS
#

include_directories (
	${PROJECT_SOURCE_DIR}
)

message("-- Install drectory: " ${CMAKE_INSTALL_PREFIX})

set(ZETJSONCPP_LIB_SRCS "")

if(MSVC)
	MESSAGE ("-- Plataform: MSVC" )
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	
	#disable C4103 warning because is perfectly valid. Only MSVC complains about it
	add_definitions(/wd4103)
	add_definitions(/wd4800)
	add_definitions(/wd4244)
	
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")	

else()

	SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS -std=gnu++0x -I -Wall -Wextra -pedantic ")
   
	if (MINGW)
		MESSAGE("-- Plataform: MINGW" )
	else()
		SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fPIC ")
		if(UNIX)
			MESSAGE ("-- Plataform: Unix" )
			file(READ "/etc/issue" ETC_ISSUE )
			string(REGEX MATCH "Debian|Ubuntu|Alpine" DIST ${ETC_ISSUE})
			MESSAGE ("-- Dist: " ${DIST} )
		else()
			MESSAGE ("-- Plataform: Unknown" )
		endif()
	endif()
	
	IF ( IS_DEBUG)
	
		set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0 -g -D__DEBUG__ ")
		
		IF( EXISTS ${PROJECT_SOURCE_DIR}/../../memmgr )
			message("-- Memmanager: ON")
			SET( CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -D__MEMMANAGER__")
			include_directories (
				${PROJECT_SOURCE_DIR}/../../memmgr
			)
	   		set(ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS} ${PROJECT_SOURCE_DIR}/../../memmgr/memmgr.cpp)
	   	else()
			if(UNIX)
				if( NOT "${DIST}" STREQUAL "Alpine")
					set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fsanitize=address ")
					message("-- Memmanager: -fsanitize=address")
				else()
					message("-- Memmanager: -fsanitize NOT supported")
				endif()
			else()
				message("-- Memmanager: OFF ($ENV{EIPM_DEVELOP_LIBS_CPP}/memmgr not exist)")
			endif()
	   	endif()
		
	ELSE()
		message("-- Memmanager: OFF")
		set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O2 ")
	ENDIF()
	
	#Redefine output dir ...
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/gcc/${CMAKE_BUILD_TYPE})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/gcc/${CMAKE_BUILD_TYPE})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/gcc/${CMAKE_BUILD_TYPE})
	LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	

endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	# 64 bits
	MESSAGE ("-- Architecture: 64bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    MESSAGE ("-- Architecture: 32bit")
endif()


#
# COMMON PARAMS
#
#---------------
#
# COMPILE PARAMS
#

# Library
set( ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS}

	
	utils/string_utils.cpp
	utils/file_utils.cpp
	utils/path_utils.cpp
	jsonvar/JsonVar.cpp
	jsonvar/ObjectJsonVar.cpp	
	zetjsoncpp_deserializer.cpp
	zetjsoncpp_serializer.cpp
)

#-------------------------------------------------------------------------------------------------------------------------------------
# LINKING PARAMS

set( LIBRARY_TYPE_CREATION "STATIC" )
if(BUILD_SHARED_LIBS)
	set( LIBRARY_TYPE_CREATION "SHARED" )
endif()

message("-- Library type: " ${LIBRARY_TYPE_CREATION})

# json2cpplib
add_library( ${ZETJSONCPP_LIB_NAME}${POST_NAME}  ${LIBRARY_TYPE_CREATION}  ${ZETJSONCPP_LIB_SRCS} )

#JSON TEST executable
set(JSON_TEST_SRCS ${PROJECT_SOURCE_DIR}/../test/test.cpp)

#JSON TEST_FILE executable
set(JSON_TEST_FILE_SRCS ${PROJECT_SOURCE_DIR}/../test/test_file.cpp)

if(MSVC)
	#only for msvc...
	set_target_properties(${ZETJSONCPP_LIB_NAME}${POST_NAME} PROPERTIES COMPILE_DEFINITIONS ZETJSONCPP_EXPORTS)
endif()
	
SET(
	HS
	utils/string_utils.h
	utils/file_utils.h
	utils/path_utils.h
	jsonvar/JsonVar.h
	jsonvar/NamedJsonVar.h
	
	jsonvar/BooleanJsonVar.h
	jsonvar/NumberJsonVar.h
	jsonvar/ObjectJsonVar.h
	jsonvar/StringJsonVar.h
	
	jsonvar/ArrayJsonVar.h
	jsonvar/ArrayBooleanJsonVar.h
	jsonvar/ArrayNumberJsonVar.h
	jsonvar/ArrayObjectJsonVar.h
	jsonvar/ArrayStringJsonVar.h
	
	jsonvar/MapJsonVar.h	
	jsonvar/MapBooleanJsonVar.h
	jsonvar/MapNumberJsonVar.h
	jsonvar/MapObjectJsonVar.h
	jsonvar/MapStringJsonVar.h
		
	zetjsoncpp.h
	zetjsoncpp.tcc
	deserialize_exception.h
)


INSTALL_HEADERS_WITH_DIRECTORY(HS)

#-----------------------------------------
# EXECUTABLES

# Test 
add_executable(test${POST_NAME}
	${JSON_TEST_SRCS}
)

target_link_libraries(test${POST_NAME} ${ZETJSONCPP_LIB_NAME}${POST_NAME})


# Test file_utils
add_executable(test_file${POST_NAME}
	${JSON_TEST_FILE_SRCS}
)

target_link_libraries(test_file${POST_NAME} ${ZETJSONCPP_LIB_NAME}${POST_NAME})


INSTALL(TARGETS ${ZETJSONCPP_LIB_NAME}${POST_NAME}
		ARCHIVE DESTINATION  		${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION  		${CMAKE_INSTALL_PREFIX}/bin
    	LIBRARY DESTINATION 		${CMAKE_INSTALL_PREFIX}/lib
    	PUBLIC_HEADER DESTINATION	${CMAKE_INSTALL_PREFIX}/includes
)
