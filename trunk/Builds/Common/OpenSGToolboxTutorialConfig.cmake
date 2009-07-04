MACRO(TOOLBOX_TUTORIAL_CONFIG TUTORIAL_DIR LIBRARY_NAME)
   #Configure the cmake build of the tutorials
   MESSAGE("Configuring ${LIBRARY_NAME} Tutorials for build type ${CMAKE_BUILD_TYPE}")
   EXECUTE_PROCESS(COMMAND 
                   cmake 
                   -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
                   -D BOOST_ROOT=${BOOST_ROOT}
                   -D FMOD_BASE_DIR=${FMOD_BASE_DIR}
                   -D ODE_BASE_DIR=${ODE_BASE_DIR}
                   -D OPENSG_BASE_DIR=${OPENSG_BASE_DIR}
                   -D OPENSGTOOLBOX_BASE_DIR=${CMAKE_INSTALL_PREFIX}
                   .
                   WORKING_DIRECTORY ${TUTORIAL_DIR})

   #Add a custom target for making and cleaning these tutorials
   ADD_CUSTOM_TARGET(${LIBRARY_NAME}_tutorials
                        COMMENT "Building ${LIBRARY_NAME} Tutorials"
                        DEPENDS
                        )
   ADD_CUSTOM_COMMAND(
      TARGET ${LIBRARY_NAME}_tutorials
      COMMAND make -i 
      DEPENDS 
      WORKING_DIRECTORY ${TUTORIAL_DIR}
      )
   ADD_DEPENDENCIES(tutorials ${LIBRARY_NAME}_tutorials)

   #cleaning tutorials
   ADD_CUSTOM_TARGET(clean_${LIBRARY_NAME}_tutorials
                        COMMENT "Cleaning ${LIBRARY_NAME} Tutorials"
                        )  
   ADD_CUSTOM_COMMAND(
      TARGET clean_${LIBRARY_NAME}_tutorials
      COMMAND make -i clean
      DEPENDS 
      WORKING_DIRECTORY ${TUTORIAL_DIR}
      )
   ADD_DEPENDENCIES(clean_tutorials clean_${LIBRARY_NAME}_tutorials)
ENDMACRO(TOOLBOX_TUTORIAL_CONFIG TUTORIAL_DIR LIBRARY_NAME)
