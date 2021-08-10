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

#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")	

else()

	SET( COMMON_CXX_PARAMS " ${COMMON_CXX_PARAMS} -D__STDC_CONSTANT_MACROS -std=gnu++0x -I -Wall -Wextra")
   
	if (MINGW)
		MESSAGE ("-- Plataform: MINGW" )
		message("-- Mingw path: $ENV{MINGWDIR} ")
		
		set(CMAKE_LEGACY_MINGW_WIN32 0)
		set(CMAKE_PREFIX_PATH "$ENV{MINGWDIR}/local32/lib")

		SET( COMMON_CXX_PARAMS " ${COMMON_CXX_PARAMS} ")
  
    elseif(GNU)
    	MESSAGE ("-- Plataform: GNU" )
    else()
    	MESSAGE ("-- Plataform: Unknown" )
	endif()
	
	IF ( "${TARGET}" STREQUAL "debug")
	
		set(COMPILE_TARGET_FLAGS " -O0 -g ")
	
		IF( EXISTS ${PROJECT_SOURCE_DIR}/../../memmgr )
			message("-- Memmanager: ON")
			SET( COMMON_CXX_PARAMS " ${COMMON_CXX_PARAMS} -D__MEMMANAGER__")
			include_directories (
				${PROJECT_SOURCE_DIR}/../../memmgr
			)
		
	   		set(ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS} ${PROJECT_SOURCE_DIR}/../../memmgr/memmgr.cpp)
	   	else()
	   		message("-- Memmanager: OFF (../../memmgr not exist)")
	   	endif()
		
	ELSE()
		set(TARGET "release")
		set(COMPILE_TARGET_FLAGS " -O2")
		message("-- Memmanager: OFF")
	ENDIF()
	
	#Redefine output dir ...
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET})
	LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	

endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	# 64 bits
	MESSAGE ("-- Architecture: 64bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    MESSAGE ("-- Architecture: 32bit")
endif()



IF ( "${TARGET}" STREQUAL "")
   SET ( TARGET "release" )
ENDIF ()

set( POST_NAME "")
IF ( "${TARGET}" STREQUAL "debug")
	set( POST_NAME "_d")
ENDIF()
 
MESSAGE ("-- Target: " ${TARGET})

IF ( "${TARGET}" STREQUAL "debug")
	SET( COMMON_CXX_PARAMS " ${COMMON_CXX_PARAMS} -D__DEBUG__ ")
ENDIF()

SET(CMAKE_CXX_FLAGS   " ${COMPILE_TARGET_FLAGS} ${COMMON_CXX_PARAMS}  " )

#
# COMMON PARAMS
#
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# COMPILE PARAMS
#

# Library
set( ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS}

	
	util/zj_strutils.cpp
	util/zj_file.cpp
	util/zj_path.cpp
	jsonvar/JsonVar.cpp
	jsonvar/JsonVarObject.cpp	
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
add_library( zetjsoncpp${POST_NAME}  ${LIBRARY_TYPE_CREATION}  ${ZETJSONCPP_LIB_SRCS} )


#JSON TEST executable
set(JSON_TEST_SRCS ${PROJECT_SOURCE_DIR}/test/test.cpp)

#JSON TEST_FILE executable
set(JSON_TEST_FILE_SRCS ${PROJECT_SOURCE_DIR}/test/test_file.cpp)


if(MSVC)
	#only for msvc...
	set_target_properties(zetjsoncpp${POST_NAME} PROPERTIES COMPILE_DEFINITIONS ZETJSONCPP_EXPORTS)
endif()
	

SET(
	HS
	util/zj_strutils.h
	util/zj_file.h
	util/zj_path.h
	jsonvar/JsonVar.h
	jsonvar/JsonVarNamed.h
	
	jsonvar/JsonVarBoolean.h
	jsonvar/JsonVarNumber.h
	jsonvar/JsonVarObject.h
	jsonvar/JsonVarString.h
	
	jsonvar/JsonVarVector.h
	jsonvar/JsonVarVectorBoolean.h
	jsonvar/JsonVarVectorNumber.h
	jsonvar/JsonVarVectorObject.h
	jsonvar/JsonVarVectorString.h
	
	jsonvar/JsonVarMap.h	
	jsonvar/JsonVarMapBoolean.h
	jsonvar/JsonVarMapNumber.h
	jsonvar/JsonVarMapObject.h
	jsonvar/JsonVarMapString.h
		
	zetjsoncpp.h
	zetjsoncpp.tcc
	exception.h
)


INSTALL_HEADERS_WITH_DIRECTORY(HS)

#-----------------------------------------
# EXECUTABLES

# Test 
add_executable(test${POST_NAME}
	${JSON_TEST_SRCS}
)

target_link_libraries(test${POST_NAME} zetjsoncpp${POST_NAME})


# Test File
add_executable(test_file${POST_NAME}
	${JSON_TEST_FILE_SRCS}
)

target_link_libraries(test_file${POST_NAME} zetjsoncpp${POST_NAME})


INSTALL(TARGETS zetjsoncpp${POST_NAME}
		ARCHIVE DESTINATION  		${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION  		${CMAKE_INSTALL_PREFIX}/bin
    	LIBRARY DESTINATION 		${CMAKE_INSTALL_PREFIX}/lib
    	PUBLIC_HEADER DESTINATION	${CMAKE_INSTALL_PREFIX}/includes
)
