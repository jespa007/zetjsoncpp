cmake_minimum_required(VERSION 2.8)
 
project(zetjsoncpp)

#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#
# MACRO UTILS
#


IF (NOT  (("${LINK}" STREQUAL "SHARED") OR ("${LINK}" STREQUAL "STATIC")))
   SET ( LINK "SHARED" )
ENDIF()
 
message("link:" ${LINK})


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

message("dest dir:" ${CMAKE_INSTALL_PREFIX})

if(MSVC)
	MESSAGE ("********* MSVC ************" )
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -DZETJSONCPP_EXPORTS)

	#disable C4103 warning because is perfectly valid. Only MSVC complains about it
	add_definitions(/wd4103)
	add_definitions(/wd4800)
	add_definitions(/wd4244)

else()

	SET( COMMON_PARAMS " ${COMMON_PARAMS} -D__STDC_CONSTANT_MACROS -std=c++1y -I -Wall")
   
	if (MINGW)
		MESSAGE ("********* MINGW CONF ************" )
		message("mingw path: $ENV{MINGWDIR} ")
		
		set(CMAKE_LEGACY_MINGW_WIN32 0)
		set(CMAKE_PREFIX_PATH "$ENV{MINGWDIR}/local32/lib")

		MESSAGE ("include" ${include_directories})
 
		SET( COMMON_PARAMS " ${COMMON_PARAMS} ")
  
	endif()

	include_directories (
		$ENV{MINGWDIR}/local32/include
	)

	LINK_DIRECTORIES (
		$ENV{MINGWDIR}/local32/lib
	)


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
 

if(MSVC)


else()


	set(TARGET_FLAGS " -O2 ")
	set( POST_NAME "")

	# -D_GLIBCXX_DEBUG

	IF ( "${TARGET}" STREQUAL "debug")
		set( POST_NAME "_d")
		set(TARGET_FLAGS " -O0 ")
		set(TARGET_FLAGS " ${TARGET_FLAGS} -g -fomit-frame-pointer ")
	ENDIF ()

	SET(CMAKE_C_FLAGS " ")
	SET(CMAKE_CXX_FLAGS   " ${TARGET_FLAGS} ${COMMON_PARAMS}  " )
	
	
	MESSAGE ("Target : " ${TARGET})

	#Redefine output dir ...
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET})
	LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	
endif()


#
# RELEASE PARAMS
#
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# Select flags.



#----------------------------------------------------------------------------------------------------------------------------------------------------
#
# SOURCE UTILS
#

# Library

set( ZETJSONCPP_LIB_SRCS

	CFile.cpp
	CStringUtils.cpp
	
	CParserVar.cpp
	CParserBase.cpp
	CParserJson.cpp
	

)

# json2cpplib
add_library( zetjsoncpp${POST_NAME} ${LINK} ${ZETJSONCPP_LIB_SRCS} )
target_link_libraries(zetjsoncpp${POST_NAME} )

SET(
	HS
	zetjsoncpp.h
	CFile.h
	CParserBase.h
	CParserJson.h
	CParserVar.h
	CStringUtils.h
)


INSTALL_HEADERS_WITH_DIRECTORY(HS)


# register_functions
add_executable(json_test${POST_NAME}
	${PROJECT_SOURCE_DIR}/test/json_test.cpp
)	

target_link_libraries(json_test${POST_NAME} zetjsoncpp${POST_NAME})	




INSTALL(TARGETS zetjsoncpp${POST_NAME}
		ARCHIVE DESTINATION  	${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION  	${CMAKE_INSTALL_PREFIX}/bin
    	LIBRARY DESTINATION 	${CMAKE_INSTALL_PREFIX}/lib
    	PUBLIC_HEADER DESTINATION	${CMAKE_INSTALL_PREFIX}/includes
)
