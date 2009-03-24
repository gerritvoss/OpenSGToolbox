cmake_minimum_required(VERSION 2.4)
PROJECT(Sound)

IF(UNIX)
  IF(APPLE)
    SET(GUI "Cocoa")
  ELSE(APPLE)
    SET(GUI "Linux")
  ENDIF(APPLE)
ELSE(UNIX)
  IF(WIN32)
    SET(GUI "Win32")
  ELSE(WIN32)
    SET(GUI "Unknown")
  ENDIF(WIN32)
ENDIF(UNIX)
MESSAGE("GUI system is ${GUI}")

# Microsoft compiler 
IF(MSVC)
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )
ENDIF(MSVC)

# fmod inc dir
FIND_PATH(FMOD_INC_DIR NAMES fmod.h fmod_error.h PATH /usr/inlcude)
INCLUDE_DIRECTORIES(${FMOD_INC_DIR})
LINK_DIRECTORIES(${FMOD_INC_DIR}/../lib)

# fmod designer inc dir
FIND_PATH(FMOD_DESIGNER_INC_DIR NAMES fmod_event.h fmod_event.hpp)
INCLUDE_DIRECTORIES(${FMOD_DESIGNER_INC_DIR})
LINK_DIRECTORIES(${FMOD_DESIGNER_INC_DIR}/../lib)

# boost inc dir
FIND_PATH(BOOST_BASE_DIR NAMES boost/)
INCLUDE_DIRECTORIES(${BOOST_BASE_DIR})
LINK_DIRECTORIES(${BOOST_BASE_DIR}/lib)

# openSG inc dir
FIND_PATH(OPENSG_INC_DIR NAMES OpenSG/OSGAction.h)
INCLUDE_DIRECTORIES(${OPENSG_INC_DIR})

# openSGToolBox dir
FIND_PATH(OPENSGTOOLBOX_INC_DIR NAMES OpenSG/)
INCLUDE_DIRECTORIES(${OPENSGTOOLBOX_INC_DIR})
LINK_DIRECTORIES(${OPENSGTOOLBOX_INC_DIR}/lib)

INCLUDE_DIRECTORIES(Sound/Events)
INCLUDE_DIRECTORIES(.)


SET(LIBRARY_OUTPUT_PATH ../Build/Linux/dbg)

ADD_LIBRARY(sound SHARED ./FMod/OSGFModSoundChannel.cpp
./FMod/OSGFModSoundManager.cpp
./FMod/OSGFModSoundBase.cpp
./FMod/OSGFModSound.cpp
./FMod/OSGFModSoundChannelBase.cpp
./FMod/OSGFModSoundManagerBase.cpp
./Sound/Events/OSGSoundEvent.cpp
./Sound/OSGSound.cpp
./Sound/OSGDialogCoordinatorBase.cpp
./Sound/OSGSoundChannel.cpp
./Sound/OSGSoundEmitter.cpp
./Sound/OSGSoundBase.cpp
./Sound/OSGSoundManager.cpp
./Sound/OSGDialogCoordinator.cpp
./Sound/OSGSoundChannelBase.cpp
./Sound/OSGSoundEmitterBase.cpp
./Sound/OSGSoundManagerBase.cpp
./Stub/OSGStubSound.cpp
./Stub/OSGStubSoundChannelBase.cpp
./Stub/OSGStubSoundManagerBase.cpp
./Stub/OSGStubSoundChannel.cpp
./Stub/OSGStubSoundManager.cpp
./Stub/OSGStubSoundBase.cpp)

