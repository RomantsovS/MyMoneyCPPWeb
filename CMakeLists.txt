CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
Project(MyMoney)

FIND_PACKAGE(Wt REQUIRED Wt HTTP)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "CCACHE_FOUND ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

INCLUDE(CheckFunctionExists)
INCLUDE(CheckLibraryExists)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE _source_list LIST_DIRECTORIES false "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Code/*.h")

set(TARGET_NAME MyMoney.wt)
ADD_EXECUTABLE(${TARGET_NAME} "${_source_list}")
TARGET_LINK_LIBRARIES(${TARGET_NAME} Wt::Wt Wt::HTTP Wt::Dbo Wt::DboSqlite3)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Test whether crypt(3) is provided by libc. If it's not, check if
# libcrypt exists and if it provides crypt(3).
CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
IF(NOT CRYPT_EXISTS)
  CHECK_LIBRARY_EXISTS(crypt crypt "" CRYPT_LIB_EXISTS)
  IF(CRYPT_LIB_EXISTS)
    SET(CMAKE_REQUIRED_LIBRARIES "crypt")
    CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
  ENDIF(CRYPT_LIB_EXISTS)
ENDIF(NOT CRYPT_EXISTS)

IF(CRYPT_LIB_EXISTS)
  TARGET_LINK_LIBRARIES(${TARGET_NAME} crypt)
ENDIF(CRYPT_LIB_EXISTS)

INCLUDE_DIRECTORIES(${WT_SOURCE_DIR}/src)
