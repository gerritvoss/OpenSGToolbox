# - Find fmod dom libraries
# Find the fmod dom libraries and headers
#
# This module specifies the following variables:
#  FMOD_INCLUDE_DIR
#  FMOD_LIBRARIES
#  FMOD_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  FMOD_LIBRARY_DEBUG        debug library
#  FMOD_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  FMOD_ROOT_DIR
#  FMOD_INCLUDE_DIR
#  FMOD_LIBRARY_DIR


#FIND_PATH(FMOD_BASE_DIR NAMES api/inc/fmod.h PATHS "")
# default include search paths
SET(__FMOD_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks/api/inc
    /Library/Frameworks/api/inc
    "/Developer/FMOD Programmers API MAC/api/inc"
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/include)

# default library search paths
SET(__FMOD_LIBRARY_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    "/Developer/FMOD Programmers API MAC/api/lib"
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /sw/lib
    /opt/local/lib64
    /opt/local/lib
    /opt/lib64
    /opt/lib)

# handle FMOD_ROOT_DIR input variable
IF(FMOD_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${FMOD_ROOT_DIR} FMOD_ROOT_DIR)

    SET(__FMOD_INCLUDE_SEARCH_DIRS "${FMOD_ROOT_DIR}/api/inc"
                                      "${__FMOD_INCLUDE_SEARCH_DIRS}")

    SET(__FMOD_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__FMOD_LIBDIR_SUFFIX_IN} __FMOD_LIBDIR_SUFFIX)

    SET(__FMOD_LIBRARY_SEARCH_DIRS "${FMOD_ROOT_DIR}/api/lib/${__FMOD_LIBDIR_SUFFIX}"
                                            "${__FMOD_LIBRARY_SEARCH_DIRS}")
ENDIF(FMOD_ROOT_DIR)


# handle FMOD_INCLUDE_DIR input variable
IF(FMOD_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${FMOD_INCLUDE_DIR} FMOD_INCLUDE_DIR)
    SET(__FMOD_INCLUDE_SEARCH_DIRS "${FMOD_INCLUDE_DIR}"
                                      "${__FMOD_INCLUDE_SEARCH_DIRS}")
ENDIF(FMOD_INCLUDE_DIR)

# handle FMOD_LIBRARY_DIR input variable
IF(FMOD_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${FMOD_LIBRARY_DIR} FMOD_LIBRARY_DIR)
    SET(__FMOD_LIBRARY_SEARCH_DIRS "${FMOD_LIBRARY_DIR}"
                                      "${__FMOD_LIBRARY_SEARCH_DIRS}")
ENDIF(FMOD_LIBRARY_DIR)


# locate headers
FIND_PATH(FMOD_INCLUDE_DIR fmod.h
    PATHS ${__FMOD_INCLUDE_SEARCH_DIRS})

IF(NOT EXISTS ${FMOD_INCLUDE_DIR})
    MESSAGE(SEND_ERROR "Could not find Fmod Include Dir from: ${__FMOD_INCLUDE_SEARCH_DIRS}.")
ENDIF(NOT EXISTS ${FMOD_INCLUDE_DIR})

# locate libraries
FIND_LIBRARY(FMOD_LIBRARY_RELEASE
    NAMES fmodex
    #NAMES fmodex${OSG_LIBDIR_SUFFIX}
    PATHS ${__FMOD_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(FMOD_LIBRARY_DEBUG
    NAMES fmodex
    #NAMES fmodex${OSG_LIBDIR_SUFFIX}
    PATHS ${__FMOD_LIBRARY_SEARCH_DIRS})

# handle the QUIETLY and REQUIRED arguments and set FMOD_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMOD DEFAULT_MSG 
                                          FMOD_LIBRARY_RELEASE
                                          FMOD_INCLUDE_DIR)

# set output variables
IF(FMOD_FOUND)
    LIST(APPEND FMOD_LIBRARIES "${FMOD_LIBRARY_RELEASE}")
ENDIF(FMOD_FOUND)

