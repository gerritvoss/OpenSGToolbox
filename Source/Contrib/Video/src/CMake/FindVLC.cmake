# Find the VLC libraries and headers
#
# This module specifies the following variables:
#  VLC_INCLUDE_DIR
#  VLC_LIBRARIES
#  VLC_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  VLC_LIBRARY_DEBUG        debug library
#  VLC_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  VLC_ROOT_DIR
#  VLC_INCLUDE_DIR
#  VLC_LIBRARY_DIR


# default include search paths
SET(__VLC_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks/api/inc
    /Library/Frameworks/api/inc
    /Applications/VLC.app/Contents/MacOS/include
    /usr/local/include
    /usr/include
    /opt/local/include
    /opt/include)

# default library search paths
SET(__VLC_LIBRARY_SEARCH_DIRS
    ~/Library/Frameworks
    /Library/Frameworks
    /Applications/VLC.app/Contents/MacOS/lib
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /opt/local/lib64
    /opt/local/lib
    /opt/lib64
    /opt/lib)

# handle VLC_ROOT_DIR input variable
IF(VLC_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${VLC_ROOT_DIR} VLC_ROOT_DIR)

    SET(__VLC_INCLUDE_SEARCH_DIRS "${VLC_ROOT_DIR}/include"
                                      "${__VLC_INCLUDE_SEARCH_DIRS}")

    SET(__VLC_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__VLC_LIBDIR_SUFFIX_IN} __VLC_LIBDIR_SUFFIX)

    SET(__VLC_LIBRARY_SEARCH_DIRS "${VLC_ROOT_DIR}/lib"
                                            "${__VLC_LIBRARY_SEARCH_DIRS}")
ENDIF(VLC_ROOT_DIR)


# handle VLC_INCLUDE_DIR input variable
IF(VLC_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${VLC_INCLUDE_DIR} VLC_INCLUDE_DIR)
    SET(__VLC_INCLUDE_SEARCH_DIRS "${VLC_INCLUDE_DIR}"
                                      "${__VLC_INCLUDE_SEARCH_DIRS}")
ENDIF(VLC_INCLUDE_DIR)

# handle VLC_LIBRARY_DIR input variable
IF(VLC_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${VLC_LIBRARY_DIR} VLC_LIBRARY_DIR)
    SET(__VLC_LIBRARY_SEARCH_DIRS "${VLC_LIBRARY_DIR}"
                                      "${__VLC_LIBRARY_SEARCH_DIRS}")
ENDIF(VLC_LIBRARY_DIR)


# locate headers
FIND_PATH(VLC_INCLUDE_DIR vlc/vlc.h
    PATHS ${__VLC_INCLUDE_SEARCH_DIRS})

IF(NOT EXISTS ${VLC_INCLUDE_DIR})
    MESSAGE(SEND_ERROR "Could not find VLC Include Dir from: ${__VLC_INCLUDE_SEARCH_DIRS}.")
ENDIF(NOT EXISTS ${VLC_INCLUDE_DIR})

# locate libraries
FIND_LIBRARY(VLC_LIBRARY_RELEASE
    NAMES vlc
    PATHS ${__VLC_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(VLC_LIBRARY_DEBUG
    NAMES vlc
    PATHS ${__VLC_LIBRARY_SEARCH_DIRS})

# handle the QUIETLY and REQUIRED arguments and set VLC_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VLC DEFAULT_MSG 
                                          VLC_LIBRARY_RELEASE
                                          VLC_INCLUDE_DIR)

# set output variables
IF(VLC_FOUND)
    LIST(APPEND VLC_LIBRARIES "${VLC_LIBRARY_RELEASE}")
ENDIF(VLC_FOUND)

