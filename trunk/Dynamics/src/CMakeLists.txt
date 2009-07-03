SET(LIBRARY_SHORT_NAME Dynamics)
SET(LIBRARY_NAME OSG${LIBRARY_SHORT_NAME})

IF(NOT BUILD_INPUT)
   MESSAGE(SEND_ERROR "Could not configure ${LIBRARY_SHORT_NAME} because the Input library is not included in this build.  Set BUILD_INPUT to ON")
ELSE(NOT BUILD_INPUT)
   MESSAGE("Configuring ${LIBRARY_SHORT_NAME} Library")
ENDIF(NOT BUILD_INPUT)

#Get a listing of the Header, source, and inline files
FILE(GLOB_RECURSE HEADERS *.h)
FILE(GLOB_RECURSE SOURCES *.cpp)
FILE(GLOB_RECURSE INLINES *.inl)

#Definition required when building the library
ADD_DEFINITIONS(-DOSG_COMPILEDYNAMICSLIB)

#Include Boost and OpenSG
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OPENSG_INC_DIR} "./" "${OPENSG_TOOLBOX_BUILD_DIR}/include" "${OPENSG_INPUT_BUILD_DIR}/include")

#Link to bost and OpenSG
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${OPENSG_LIB_DIR} "${OPENSG_TOOLBOX_BUILD_DIR}" "${OPENSG_INPUT_BUILD_DIR}")

#Configure shared library creation
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${HEADERS} ${SOURCES} ${INLINES})
ADD_DEPENDENCIES(${LIBRARY_NAME} OSGToolbox OSGInput)

#Header files build
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include")
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/OpenSG")
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/OpenSG/${LIBRARY_SHORT_NAME}")
ADD_CUSTOM_TARGET(${LIBRARY_NAME}_headers
                  ALL
                  COMMAND ${CMAKE_SOURCE_DIR}/Builds/Common/CopyIncludes.sh
                  ${CMAKE_SOURCE_DIR}/Builds/Common/
                  ${CMAKE_CURRENT_SOURCE_DIR}
                  ${CMAKE_CURRENT_BINARY_DIR}/include/OpenSG/${LIBRARY_SHORT_NAME}
                  DEPENDS ${HEADERS} ${INLINES})

#Attach all of the Compile flags
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_DEBUG "${OPENSG_CXX_FLAGS_DBG} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_RELEASE "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_MINSIZEREL "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_RELWITHDEBINFO "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES LINK_FLAGS_DEBUG "${OPENSG_LIBS_DBG}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES LINK_FLAGS ${OPENSG_LIBS_OPT})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "${OPENSG_LIBS_OPT}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "${OPENSG_LIBS_OPT}")

#Attach all of the linker libraries
TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${Boost_LIBRARIES} optimized OSGToolbox optimized OSGInput debug OSGToolboxD debug OSGInputD)


#Installing instructions
INSTALL(CODE "MESSAGE(\"Installing ${LIBRARY_NAME}\")")

#Install the headers
INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/OpenSG/${LIBRARY_SHORT_NAME}
        DESTINATION include/OpenSG
        COMPONENT headers)

#install the libraries
INSTALL(TARGETS ${LIBRARY_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        COMPONENT optLibs)

#Doxygen documentation
# Generating documentation with doxygen
#
if(DOXYGEN_EXECUTABLE)
    
    IF(ENABLE_USER_DOCUMENTATION)
      # The initial rm command gets rid of everything previously built by this
      # custom command.
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc")
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/user")
      
      ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html/index.html
      COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html
      COMMAND DOC_REVISION_NUMBER=${Project_WC_REVISION} DOC_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/doc/user ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.user
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.user
              ${HEADERS}
              ${INLINES}
              ${SOURCES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation
      )
      
      ADD_CUSTOM_TARGET(${LIBRARY_SHORT_NAME}_user_doc
                        COMMENT "Building ${LIBRARY_SHORT_NAME} User Documentation"
                        DEPENDS
                        ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html/index.html)

      ADD_DEPENDENCIES(user_doc ${LIBRARY_SHORT_NAME}_user_doc)

      #Installing the documentation
      INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html
              DESTINATION doc/user/${LIBRARY_SHORT_NAME}
              COMPONENT userDoc)

    ENDIF(ENABLE_USER_DOCUMENTATION)
    
    # The initial rm command gets rid of everything previously built by this
    # custom command.
    IF(ENABLE_DEVELOPER_DOCUMENTATION)
      # The initial rm command gets rid of everything previously built by this
      # custom command.
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc")
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/developer")
      
      ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html/index.html
      COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html
      COMMAND DOC_REVISION_NUMBER=${Project_WC_REVISION} DOC_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/doc/developer ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.developer
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.developer
              ${HEADERS}
              ${INLINES}
              ${SOURCES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation
      )
      
      ADD_CUSTOM_TARGET(${LIBRARY_SHORT_NAME}_dev_doc
                        COMMENT "Building ${LIBRARY_SHORT_NAME} Developer  Documentation"
                        DEPENDS
                        ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html/index.html)

      ADD_DEPENDENCIES(dev_doc ${LIBRARY_SHORT_NAME}_dev_doc)

      #Installing the documentation
      INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html
              DESTINATION doc/developer/${LIBRARY_SHORT_NAME}
              COMPONENT devDoc)
    ENDIF(ENABLE_DEVELOPER_DOCUMENTATION)
    
endif(DOXYGEN_EXECUTABLE)
IF(CONFIGURE_TUTORIALS)
   #Configure the cmake build of the tutorials
   MESSAGE("Configuring ${LIBRARY_SHORT_NAME} Tutorials for build type ${CMAKE_BUILD_TYPE}")
   EXECUTE_PROCESS(COMMAND 
                   cmake 
                   -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
                   -D BOOST_ROOT=${BOOST_ROOT} 
                   -D OPENSG_BASE_DIR=${OPENSG_BASE_DIR}
                   -D OPENSGTOOLBOX_BASE_DIR=${CMAKE_INSTALL_PREFIX}
                   .
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Tutorials)

   #Add a custom target for making and cleaning these tutorials
   ADD_CUSTOM_TARGET(${LIBRARY_SHORT_NAME}_tutorials
                        COMMENT "Building ${LIBRARY_SHORT_NAME} Tutorials"
                        DEPENDS
                        )
   ADD_CUSTOM_COMMAND(
      TARGET ${LIBRARY_SHORT_NAME}_tutorials
      COMMAND make -i 
      DEPENDS 
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Tutorials
      )
   ADD_DEPENDENCIES(tutorials ${LIBRARY_SHORT_NAME}_tutorials)

   #cleaning tutorials
   ADD_CUSTOM_TARGET(clean_${LIBRARY_SHORT_NAME}_tutorials
                        COMMENT "Cleaning ${LIBRARY_SHORT_NAME} Tutorials"
                        )  
   ADD_CUSTOM_COMMAND(
      TARGET clean_${LIBRARY_SHORT_NAME}_tutorials
      COMMAND make -i clean
      DEPENDS 
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Tutorials
      )
   ADD_DEPENDENCIES(clean_tutorials clean_${LIBRARY_SHORT_NAME}_tutorials)
ENDIF(CONFIGURE_TUTORIALS)
