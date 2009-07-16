
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT("Animation Tutorials")

SET (CMAKE_VERBOSE_MAKEFILE TRUE)

######### Revision number
Option(UseSVN "check if svn should be used")
FIND_PACKAGE(Subversion)
IF(Subversion_FOUND AND UseSVN)
   Subversion_WC_INFO(${CMAKE_HOME_DIRECTORY} Project)
   MESSAGE("Current revision is ${Project_WC_REVISION}")
ENDIF(Subversion_FOUND AND UseSVN)

######### FMod
FIND_PATH(FMOD_BASE_DIR NAMES api/inc/fmod.h PATHS "/Developer/FMOD Programmers API")
SET(FMOD_INC_DIR ${FMOD_BASE_DIR}/api/inc)
SET(FMOD_LIB_DIR ${FMOD_BASE_DIR}/api/lib)


######### OpenSG
IF(WIN32)
   SET(OPENSG_BASE_DIR $ENV{OPENSG}/..)
ENDIF(WIN32)

FIND_PATH(OPENSG_BASE_DIR include/OpenSG/OSGConfig.h)
SET(OPENSG_INC_DIR ${OPENSG_BASE_DIR}/include)
SET(OPENSG_LIB_DIR ${OPENSG_BASE_DIR}/lib)

IF (UNIX)
   FIND_PROGRAM(OSG_CONFIG osg-config ${OPENSG_BASE_DIR}/bin)
   #IF (${OSG_CONFIG})
     IF(APPLE)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --cflags Base System OUTPUT_VARIABLE OPENSG_CXX_FLAGS_DBG)
       STRING(STRIP ${OPENSG_CXX_FLAGS_DBG}  OPENSG_CXX_FLAGS_DBG)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --cflags Base System OUTPUT_VARIABLE OPENSG_CXX_FLAGS_OPT)
       STRING(STRIP ${OPENSG_CXX_FLAGS_OPT}  OPENSG_CXX_FLAGS_OPT)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --lflags Base System OUTPUT_VARIABLE OPENSG_LD_FLAGS_DBG)
       STRING(STRIP ${OPENSG_LD_FLAGS_DBG}  OPENSG_LD_FLAGS_DBG)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --lflags Base System OUTPUT_VARIABLE OPENSG_LD_FLAGS_OPT)
       STRING(STRIP ${OPENSG_LD_FLAGS_OPT}  OPENSG_LD_FLAGS_OPT)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --libs Base System OUTPUT_VARIABLE OPENSG_LIBS_OPT)
       STRING(STRIP ${OPENSG_LIBS_OPT}  OPENSG_LIBS_OPT)
       SET(OPENSG_LIBS_OPT "${OPENSG_LIBS_OPT} -framework Carbon -framework AGL -lOSGWindowCarbon")
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --libs Base System OUTPUT_VARIABLE OPENSG_LIBS_DBG)
       STRING(STRIP ${OPENSG_LIBS_DBG}  OPENSG_LIBS_DBG)
       SET(OPENSG_LIBS_DBG "${OPENSG_LIBS_DBG} -framework Carbon -framework AGL -lOSGWindowCarbon")
     ELSE(APPLE)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --cflags Base System X OUTPUT_VARIABLE OPENSG_CXX_FLAGS_DBG)
       STRING(STRIP ${OPENSG_CXX_FLAGS_DBG}  OPENSG_CXX_FLAGS_DBG)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --cflags Base System X OUTPUT_VARIABLE OPENSG_CXX_FLAGS_OPT)
       STRING(STRIP ${OPENSG_CXX_FLAGS_OPT}  OPENSG_CXX_FLAGS_OPT)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --lflags Base System X OUTPUT_VARIABLE OPENSG_LD_FLAGS_DBG)
       STRING(STRIP ${OPENSG_LD_FLAGS_DBG}  OPENSG_LD_FLAGS_DBG)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --lflags Base System X OUTPUT_VARIABLE OPENSG_LD_FLAGS_OPT)
       STRING(STRIP ${OPENSG_LD_FLAGS_OPT}  OPENSG_LD_FLAGS_OPT)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --opt --libs Base System X OUTPUT_VARIABLE OPENSG_LIBS_OPT)
       STRING(STRIP ${OPENSG_LIBS_OPT}  OPENSG_LIBS_OPT)
       EXECUTE_PROCESS(COMMAND ${OSG_CONFIG} --dbg --libs Base System X OUTPUT_VARIABLE OPENSG_LIBS_DBG)
       STRING(STRIP ${OPENSG_CXX_FLAGS_OPT}  OPENSG_LIBS_DBG)
     ENDIF(APPLE)
     #ELSE(${OSG_CONFIG})
     #   MESSAGE("osg-config not found")
     #ENDIF (${OSG_CONFIG})
ENDIF(UNIX)

IF(WIN32)
   SET(OPENSG_CXX_FLAGS_DBG "-D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -DOSG_WITH_GLUT -DOSG_WITH_GIF -DOSG_WITH_TIF -DOSG_WITH_JPG -D_DEBUG /MP")
   SET(OPENSG_CXX_FLAGS_OPT "-D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -DOSG_WITH_GLUT -DOSG_WITH_GIF -DOSG_WITH_TIF -DOSG_WITH_JPG /MP")
   SET(OPENSG_LD_FLAGS_DBG "")
   SET(OPENSG_LD_FLAGS_OPT "")
   SET(OPENSG_LIBS_DBG OSGBaseD OSGSystemD)
   SET(OPENSG_LIBS_OPT OSGBase OSGSystem)
   SET(OPENSG_WINDOW_LIBS debug OSGWindowWIN32D optimized OSGWindowWIN32)                
ENDIF(WIN32)

######## BOOST
FIND_PACKAGE(Boost REQUIRED COMPONENTS system filesystem)

######### ODE

######### OpenSGToolbox
FIND_PATH(OPENSGTOOLBOX_BASE_DIR include/OpenSG/Toolbox/OSGToolboxdef.h)
SET(OPENSGTOOLBOX_INC_DIR ${OPENSGTOOLBOX_BASE_DIR}/include)
SET(OPENSGTOOLBOX_LIB_DIR ${OPENSGTOOLBOX_BASE_DIR}/lib)
INCLUDE(${OPENSGTOOLBOX_BASE_DIR}/lib/export/OpenSGToolboxExport.cmake
   OPTIONAL
   RESULT_VARIABLE FOUND_OPENSGTOOLBOX_EXPORTS)

IF(${FOUND_OPENSGTOOLBOX_EXPORTS} STREQUAL NOTFOUND)
   MESSAGE("Did NOT find OpenSG Toolbox Exports: ${FOUND_OPENSGTOOLBOX_EXPORTS}")
ELSE(${FOUND_OPENSGTOOLBOX_EXPORTS} STREQUAL NOTFOUND)
   MESSAGE("FOUND OpenSG Toolbox Exports")
ENDIF(${FOUND_OPENSGTOOLBOX_EXPORTS} STREQUAL NOTFOUND)

#Include Boost and OpenSG
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OPENSG_INC_DIR} ${OPENSGTOOLBOX_INC_DIR})

#Link to bost and OpenSG
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${OPENSGTOOLBOX_LIB_DIR})

######## Tutorial executables
SET(TUTORIAL_LIST 01Animation 02BlendGeometry 03MFieldAnimation
   04ShaderAnimation 05TextureAnimation 10SkeletonDrawer 11BoneAnimation
   12SkeletonAnimation 13MeshBlending 14SkeletonLoader 15LoadXMLAnimation
   16LoadXMLSkeleton 17LoadXMLSkeletonAnimation 20LoadXMLBlendedGeometry
   21LoadXMLSceneFromMaya 22SkeletonBlendedAnimation 23BlendXMLAnimations 24AnimationAction)
FOREACH(TUTORIAL ${TUTORIAL_LIST})
   MESSAGE("Configurint Tutorial: ${TUTORIAL}")

   ADD_EXECUTABLE(${TUTORIAL} ${TUTORIAL}.cpp)
   
   #Attach all of the Compile flags
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES COMPILE_FLAGS_DEBUG "${OPENSG_CXX_FLAGS_DBG}")
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES COMPILE_FLAGS_RELEASE "${OPENSG_CXX_FLAGS_OPT}")
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES COMPILE_FLAGS_MINSIZEREL "${OPENSG_CXX_FLAGS_OPT}")
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES COMPILE_FLAGS_RELWITHDEBINFO "${OPENSG_CXX_FLAGS_OPT}")

   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES LINK_FLAGS_DEBUG "${OPENSG_LIBS_DBG}")
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES LINK_FLAGS ${OPENSG_LIBS_OPT})
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES LINK_FLAGS_MINSIZEREL "${OPENSG_LIBS_OPT}")
   SET_TARGET_PROPERTIES(${TUTORIAL} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "${OPENSG_LIBS_OPT}")
ENDFOREACH(TUTORIAL ${TUTORIAL_LIST})

#Attach all of the linker librarie
TARGET_LINK_LIBRARIES(01Animation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(02BlendGeometry optimized OSGToolbox  optimized OSGInput
   optimized OSGAnimation optimized OSGDynamics optimized OSGUserInterface
                                  debug     OSGToolboxD debug     OSGInputD
                                  debug     OSGAnimationD debug OSGDynamicsD
                                  debug OSGUserInterfaceD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(03MFieldAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(04ShaderAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(05TextureAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(10SkeletonDrawer optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(11BoneAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(12SkeletonAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(13MeshBlending optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(14SkeletonLoader optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(15LoadXMLAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(16LoadXMLSkeleton optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(17LoadXMLSkeletonAnimation optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(20LoadXMLBlendedGeometry optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(21LoadXMLSceneFromMaya optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(22SkeletonBlendedAnimation optimized OSGToolbox
   optimized OSGInput  optimized OSGAnimation optimized OSGDynamics optimized OSGUserInterface
                                  debug     OSGToolboxD debug     OSGInputD
                                  debug     OSGAnimationD debug OSGDynamicsD
                                  debug OSGUserInterfaceD
                                     ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(23BlendXMLAnimations optimized OSGToolbox
   optimized OSGInput  optimized OSGAnimation optimized OSGDynamics optimized OSGUserInterface
                                  debug     OSGToolboxD debug     OSGInputD
                                  debug     OSGAnimationD debug OSGDynamicsD
                                  debug OSGUserInterfaceD
                                     ${Boost_LIBRARIES})


TARGET_LINK_LIBRARIES(24AnimationAction optimized OSGToolbox  optimized OSGInput  optimized OSGAnimation optimized OSGUserInterface optimized OSGDynamics
                                  debug     OSGToolboxD debug     OSGInputD debug     OSGAnimationD debug OSGUserInterfaceD debug OSGDynamicsD
                                     ${Boost_LIBRARIES})