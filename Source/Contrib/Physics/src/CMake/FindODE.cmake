# - Find fmod dom libraries
# Find the fmod dom libraries and headers
#
# This module specifies the following variables:
#  ODE_INCLUDE_DIR
#  ODE_LIBRARIES
#  ODE_LIBRARY_DIRS
#
# Additionally the following more specialized variables are defined:
#  ODE_LIBRARY_DEBUG        debug library
#  ODE_LIBRARY_RELEASE      release library
#
#  You can control where this module attempts to locate libraries and headers:
#  ODE_ROOT_DIR
#  ODE_INCLUDE_DIR
#  ODE_LIBRARY_DIR


#FIND_PATH(ODE_BASE_DIR NAMES api/inc/fmod.h PATHS "")
# default include search paths
SET(__ODE_INCLUDE_SEARCH_DIRS
    ~/Library/Frameworks/
    /Library/Frameworks/
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/include)

# default library search paths
SET(__ODE_LIBRARY_SEARCH_DIRS
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

# handle ODE_ROOT_DIR input variable
IF(ODE_ROOT_DIR)
    FILE(TO_CMAKE_PATH ${ODE_ROOT_DIR} ODE_ROOT_DIR)

    SET(__ODE_INCLUDE_SEARCH_DIRS "${ODE_ROOT_DIR}/include"
                                      "${__ODE_INCLUDE_SEARCH_DIRS}")

    SET(__ODE_LIBDIR_SUFFIX_IN "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

    STRING(TOLOWER ${__ODE_LIBDIR_SUFFIX_IN} __ODE_LIBDIR_SUFFIX)

    SET(__ODE_LIBRARY_SEARCH_DIRS "${ODE_ROOT_DIR}/lib/${__ODE_LIBDIR_SUFFIX}"
                                            "${__ODE_LIBRARY_SEARCH_DIRS}")
ENDIF(ODE_ROOT_DIR)


# handle ODE_INCLUDE_DIR input variable
IF(ODE_INCLUDE_DIR)
    FILE(TO_CMAKE_PATH ${ODE_INCLUDE_DIR} ODE_INCLUDE_DIR)
    SET(__ODE_INCLUDE_SEARCH_DIRS "${ODE_INCLUDE_DIR}"
                                      "${__ODE_INCLUDE_SEARCH_DIRS}")
ENDIF(ODE_INCLUDE_DIR)

# handle ODE_LIBRARY_DIR input variable
IF(ODE_LIBRARY_DIR)
    FILE(TO_CMAKE_PATH ${ODE_LIBRARY_DIR} ODE_LIBRARY_DIR)
    SET(__ODE_LIBRARY_SEARCH_DIRS "${ODE_LIBRARY_DIR}"
                                      "${__ODE_LIBRARY_SEARCH_DIRS}")
ENDIF(ODE_LIBRARY_DIR)


# locate headers
FIND_PATH(ODE_INCLUDE_DIR ode/ode.h
    PATHS ${__ODE_INCLUDE_SEARCH_DIRS})

IF(NOT EXISTS ${ODE_INCLUDE_DIR})
    MESSAGE(SEND_ERROR "Could not find ODE Include Dir from: ${__ODE_INCLUDE_SEARCH_DIRS}.")
ENDIF(NOT EXISTS ${ODE_INCLUDE_DIR})

# locate libraries
FIND_LIBRARY(ODE_LIBRARY_RELEASE
    NAMES ode
    #NAMES ode${OSG_LIBDIR_SUFFIX}
    PATHS ${__ODE_LIBRARY_SEARCH_DIRS})

FIND_LIBRARY(ODE_LIBRARY_DEBUG
    NAMES ode
    #NAMES ode${OSG_LIBDIR_SUFFIX}
    PATHS ${__ODE_LIBRARY_SEARCH_DIRS})

# handle the QUIETLY and REQUIRED arguments and set ODE_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ODE DEFAULT_MSG 
                                          ODE_LIBRARY_RELEASE
                                          ODE_INCLUDE_DIR)

# set output variables
IF(ODE_FOUND)
    LIST(APPEND ODE_LIBRARIES "${ODE_LIBRARY_RELEASE}")
ENDIF(ODE_FOUND)

