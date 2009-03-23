cmake_minimum_required(VERSION 2.4)
PROJECT(Sound)

# fmod inc dir
FIND_PATH(FMOD_INC_DIR NAMES fmod.h fmod_error.h PATH /usr/inlcude)
INCLUDE_DIRECTORIES(${FMOD_INC_DIR})

# fmod designer inc dir
FIND_PATH(FMOD_DESIGNER_INC_DIR NAMES fmod_event.h fmod_event.hpp)
INCLUDE_DIRECTORIES(${FMOD_DESIGNER_INC_DIR})

# boost inc dir
FIND_PATH(BOOST_INC_DIR NAMES boost/)
INCLUDE_DIRECTORIES(${BOOST_INC_DIR})

# openSG inc dir
FIND_PATH(OPENSG_INC_DIR NAMES OpenSG/OSGAction.h)
INCLUDE_DIRECTORIES(${OPENSG_INC_DIR})

# openSGToolBox dir
FIND_PATH(OPENSGTOOLBOX_INC_DIR NAMES OpenSG/)
INCLUDE_DIRECTORIES(${OPENSGTOOLBOX_INC_DIR})
INCLUDE_DIRECTORIES(Sound/Events)

INCLUDE_DIRECTORIES(.)

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

