CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

INCLUDE(${CMAKE_SOURCE_DIR}/../../Builds/Common/OpenSGToolboxTutorialMacro.cmake)

PROJECT("Game Tutorials")

OPENSG_TOOLBOX_TUTORIALS(1 1 "OSGToolbox;OSGInput;OSGDynamics;OSGUserInterface;OSGPhysics;OSGSound;OSGGame")


