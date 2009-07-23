CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

INCLUDE(${CMAKE_SOURCE_DIR}/../../Builds/Common/OpenSGToolboxTutorialMacro.cmake)

PROJECT("Physics Tutorials")

OPENSG_TOOLBOX_TUTORIALS(0 1 "OSGToolbox;OSGInput;OSGPhysics")

