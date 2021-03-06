PROJECT (postWoman)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_VERBOSE_MAKEFILE on)
SET (APP_NAME postWoman)
SET(CMAKE_FIND_ROOT_PATH ${ROOTFS})

SET(SOURCES_DIR src)

SET(HEADERS_DIR include)

FILE(GLOB SOURCES "${SOURCES_DIR}/*.cpp")

FILE(GLOB HEADERS "${HEADERS_DIR}/*.h")

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra ")	
ELSEIF(COMPILER_SUPPORTS_CXX0X)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x  -Wall -Wextra ")
ELSE()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 flag support")
ENDIF()
    
IF (NOT CONFIGURED_ONCE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Flags used by the compiler by default" FORCE)
ENDIF()

IF(NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Setting DEBUG")
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type" FORCE)
ENDIF()

MESSAGE(STATUS "Build mode: ${CMAKE_BUILD_TYPE}")

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/lib)

ADD_EXECUTABLE (postWoman ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES (postWoman -pthread )

MESSAGE(STATUS "INSTALL DIR: ${CMAKE_INSTALL_PREFIX}")

INSTALL(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

