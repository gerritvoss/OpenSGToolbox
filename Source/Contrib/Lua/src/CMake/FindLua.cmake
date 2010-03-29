# - Find fmod dom libraries
# Find the fmod dom libraries and headers
#
# This module specifies the following variables:
#  LUA_INCLUDE_DIR
#  LUA_LIBRARIES
#  LUA_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  LUA_LIBRARY_DEBUG        debug library
#  LUA_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  LUA_ROOT_DIR
#  LUA_INCLUDE_DIR
#  LUA_LIBRARY_DIR


#FIND_PATH(LUA_BASE_DIR NAMES api/inc/fmod.h PATHS "")
# default include search paths
SET(__LUA_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks/
    /Library/Frameworks/
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/include)

# default library search paths
SET(__LUA_LIBRARY_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /sw/lib
    /opt/local/lib64
    /opt/local/lib
    /opt/lib64
    /opt/lib)

# handle LUA_ROOT_DIR input variable
IF(LUA_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${LUA_ROOT_DIR} LUA_ROOT_DIR)

    SET(__LUA_INCLUDE_SEARCH_DIRS "${LUA_ROOT_DIR}/include"
                                      "${__LUA_INCLUDE_SEARCH_DIRS}")

    SET(__LUA_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__LUA_LIBDIR_SUFFIX_IN} __LUA_LIBDIR_SUFFIX)

    SET(__LUA_LIBRARY_SEARCH_DIRS "${LUA_ROOT_DIR}/lib/${__LUA_LIBDIR_SUFFIX}"
                                            "${__LUA_LIBRARY_SEARCH_DIRS}")
ENDIF(LUA_ROOT_DIR)


# handle LUA_INCLUDE_DIR input variable
IF(LUA_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${LUA_INCLUDE_DIR} LUA_INCLUDE_DIR)
    SET(__LUA_INCLUDE_SEARCH_DIRS "${LUA_INCLUDE_DIR}"
                                  "${__LUA_INCLUDE_SEARCH_DIRS}")
ENDIF(LUA_INCLUDE_DIR)

# handle LUA_LIBRARY_DIR input variable
IF(LUA_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${LUA_LIBRARY_DIR} LUA_LIBRARY_DIR)
    SET(__LUA_LIBRARY_SEARCH_DIRS "${LUA_LIBRARY_DIR}"
                                  "${__LUA_LIBRARY_SEARCH_DIRS}")
ENDIF(LUA_LIBRARY_DIR)


# locate headers
FIND_PATH(LUA_INCLUDE_DIR lua.h
    PATHS ${__LUA_INCLUDE_SEARCH_DIRS})

IF(NOT EXISTS ${LUA_INCLUDE_DIR})
    MESSAGE(STATUS "Could not find LUA Include Dir from: ${__LUA_INCLUDE_SEARCH_DIRS}.")
ENDIF(NOT EXISTS ${LUA_INCLUDE_DIR})

# locate libraries
FIND_LIBRARY(LUA_LIBRARY_RELEASE
    NAMES lua5.1.a lua-5.1 lua
    #NAMES lua${OSG_LIBDIR_SUFFIX}
    PATHS ${__LUA_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(LUA_LIBRARY_DEBUG
    NAMES lua5.1.a lua-5.1 lua
    #NAMES lua${OSG_LIBDIR_SUFFIX}
    PATHS ${__LUA_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(LUA_LIBRARY_STATIC
    NAMES lua5.1 lua-5.1 lua
    #NAMES lua${OSG_LIBDIR_SUFFIX}
    PATHS ${__LUA_LIBRARY_SEARCH_DIRS})

# handle the QUIETLY and REQUIRED arguments and set LUA_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LUA DEFAULT_MSG 
                                  LUA_LIBRARY_RELEASE
                                  LUA_INCLUDE_DIR)

# set output variables
IF(LUA_FOUND)
    LIST(APPEND LUA_LIBRARIES "${LUA_LIBRARY_RELEASE}")
ENDIF(LUA_FOUND)

