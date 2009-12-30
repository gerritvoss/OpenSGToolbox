CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
#SET (CMAKE_VERBOSE_MAKEFILE TRUE)

FIND_PATH(TUTORIAL_MACRO_FILE OpenSGToolboxTutorialMacro.cmake "${CMAKE_SOURCE_DIR}/../../Builds/Common" "${CMAKE_SOURCE_DIR}/../build")

INCLUDE("${TUTORIAL_MACRO_FILE}/OpenSGToolboxTutorialMacro.cmake")

PROJECT("Lua Tutorials")

OPENSG_TOOLBOX_TUTORIALS(1 0 1 "OSGToolbox;OSGInput;OSGLua;OSGUserInterface;OSGParticleSystem;OSGAnimation;OSGSound;OSGToolboxLuaBindings")

