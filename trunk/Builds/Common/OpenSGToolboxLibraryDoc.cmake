MACRO(TOOLBOX_LIBRARY_DOCUMENTATION THE_DOXYTEN_EXECUTABLE
      DOCUMENTATION_REVISION LIBRARY_NAME ENABLE_USER_DOC ENABLE_DEV_DOC
      DOC_HEADERS DOC_INLINES DOC_SOURCES)

   IF(${ENABLE_USER_DOC} STREQUAL "ON")
      MESSAGE("Configuring ${LIBRARY_NAME} User Documentation")
      # The initial rm command gets rid of everything previously built by this
      # custom command.
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/user")
      
      ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html/index.html
      COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html
      COMMAND DOC_REVISION_NUMBER=${DOCUMENTATION_REVISION} DOC_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/doc/user ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.user
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.user
              ${DOC_HEADERS}
              ${DOC_INLINES}
              ${DOC_SOURCES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation
                        COMMENT "Building ${LIBRARY_NAME} User Documentation"
      )
      
      ADD_CUSTOM_TARGET(${LIBRARY_NAME}_user_doc
                        DEPENDS
                        ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html/index.html)

      ADD_DEPENDENCIES(user_doc ${LIBRARY_NAME}_user_doc)

      #Installing the documentation
      INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/user/html
              DESTINATION doc/user/${LIBRARY_NAME}
              COMPONENT userDoc)

   ENDIF(${ENABLE_USER_DOC} STREQUAL "ON")
    
    # The initial rm command gets rid of everything previously built by this
    # custom command.
    IF(${ENABLE_DEV_DOC} STREQUAL "ON")
      MESSAGE("Configuring ${LIBRARY_NAME} Developer Documentation")
      # The initial rm command gets rid of everything previously built by this
      # custom command.
      FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/developer")
      
      ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html/index.html
      COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html
      COMMAND DOC_REVISION_NUMBER=${DOCUMENTATION_REVISION}
      DOC_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/doc/developer
      ${THE_DOXYGEN_EXECUTABLEi} ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.developer
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile.developer
              ${DOC_HEADERS}
              ${DOC_INLINES}
              ${DOC_SOURCES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation
                        COMMENT "Building ${LIBRARY_NAME} Developer  Documentation"
      )
      
      ADD_CUSTOM_TARGET(${LIBRARY_NAME}_dev_doc
                        DEPENDS
                        ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html/index.html)

      ADD_DEPENDENCIES(dev_doc ${LIBRARY_NAME}_dev_doc)

      #Installing the documentation
      INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/developer/html
              DESTINATION doc/developer/${LIBRARY_NAME}
              COMPONENT devDoc)
    ENDIF(${ENABLE_DEV_DOC} STREQUAL "ON")
ENDMACRO(TOOLBOX_LIBRARY_DOCUMENTATION THE_DOXYTEN_EXECUTABLE
      DOCUMENTATION_REVISION LIBRARY_NAME ENABLE_USER_DOC ENABLE_DEV_DOC
      DOC_HEADERS DOC_INLINES DOC_SOURCES)
