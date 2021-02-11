cmake_minimum_required(VERSION 2.8)
 
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

message("-- Dest.dir: " ${CMAKE_INSTALL_PREFIX})

set(ZETJSONCPP_LIB_SRCS "")


if(MSVC)
	MESSAGE ("-- Plataform: MSVC" )
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	
	#disable C4103 warning because is perfectly valid. Only MSVC complains about it
	add_definitions(/wd4103)
	add_definitions(/wd4800)
	add_definitions(/wd4244)

else()

	SET( COMMON_PARAMS " ${COMMON_PARAMS} -D__STDC_CONSTANT_MACROS -std=gnu++0x -I -Wall -Wextra")
   
	if (MINGW)
		MESSAGE ("-- Plataform: MINGW" )
		message("-- Mingw path: $ENV{MINGWDIR} ")
		
		set(CMAKE_LEGACY_MINGW_WIN32 0)
		set(CMAKE_PREFIX_PATH "$ENV{MINGWDIR}/local32/lib")

		SET( COMMON_PARAMS " ${COMMON_PARAMS} ")
  
    elseif(GNU)
    	MESSAGE ("-- Plataform: GNU" )
    else()
    	MESSAGE ("-- Plataform: Unknown" )
	endif()
	
	IF (MEMMANAGER)
		message("-- Memmanager: ON (Warning execution time could be slow)")
		SET( COMMON_PARAMS " ${COMMON_PARAMS} -D__MEMMANAGER__")
		include_directories (
			../memmgr
		)
		
	   	set(ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS} ../memmgr/memmgr.cpp)
		
	ELSE()
		message("-- Memmanager: OFF")
	ENDIF()
	

endif()


#
# COMMON PARAMS
#
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# RELEASE PARAMS
#


IF ( "${TARGET}" STREQUAL "")
   SET ( TARGET "release" )
ENDIF ()
 
 
set( POST_NAME "")
IF ( "${TARGET}" STREQUAL "debug")
	set( POST_NAME "_d")
ENDIF()
 
MESSAGE ("-- Target : " ${TARGET})

IF ( "${TARGET}" STREQUAL "debug")
	SET( COMMON_PARAMS " ${COMMON_PARAMS} -D__DEBUG__")
ENDIF()


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

	MESSAGE ("-- Toolchain : GNU")

	set(TARGET_FLAGS " -O2 ")
	IF ( "${TARGET}" STREQUAL "debug")
		set(TARGET_FLAGS " -O0 ")
		set(TARGET_FLAGS " ${TARGET_FLAGS} -g -fomit-frame-pointer ")
	ENDIF ()

	SET(CMAKE_C_FLAGS " ")
	SET(CMAKE_CXX_FLAGS   " ${TARGET_FLAGS} ${COMMON_PARAMS}  " )
	

	#Redefine output dir ...
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${TARGET})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${TARGET})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${TARGET})
	LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	
endif()


#
# RELEASE PARAMS
#
#----------------------------------------------------------------------------------------------------------------------------------------------------
#
# SOURCE UTILS
#

# Library
set( ZETJSONCPP_LIB_SRCS ${ZETJSONCPP_LIB_SRCS}

	
	util/zj_strutils.cpp
	util/zj_file.cpp
	util/zj_path.cpp
	jsonvar/JsonVar.cpp
	jsonvar/JsonVarObject.cpp	
	zetjsoncpp.cpp
)

#JSON TEST executable
set(JSON_TEST_SRCS ${PROJECT_SOURCE_DIR}/test/test.cpp)

#JSON TEST_FILE executable
set(JSON_TEST_FILE_SRCS ${PROJECT_SOURCE_DIR}/test/test_file.cpp)

# json2cpplib
add_library( zetjsoncpp${POST_NAME} STATIC ${ZETJSONCPP_LIB_SRCS} )


if(MSVC)
	#only for msvc...
	set_target_properties(zetjsoncpp${POST_NAME} PROPERTIES COMPILE_DEFINITIONS ZETJSONCPP_EXPORTS)
endif()
	

SET(
	HS
	util/zj_strutils.h
	util/zj_file.h
	util/zj_path.h
	jsonvar/JsonVarVector.h
	jsonvar/JsonVar.h
	jsonvar/JsonVarVectorBoolean.h
	jsonvar/JsonVarVectorNumber.h
	jsonvar/JsonVarVectorObject.h
	jsonvar/JsonVarVectorString.h
	jsonvar/JsonVarBoolean.h
	jsonvar/JsonVarNamed.h
	jsonvar/JsonVarNumber.h
	jsonvar/JsonVarObject.h
	jsonvar/JsonVarString.h
		
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
