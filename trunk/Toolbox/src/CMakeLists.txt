

SET(HEADERS ./Types/OSGFieldContainerMapType.h
./Types/OSGStringMapType.h
./Types/OSGPathType.h
./FileIO/OSGBinFCFileType.h
./FileIO/OSGFCFileHandler.h
./FileIO/OSGFCFileType.h
./FileIO/OSGXMLFCFileType.h
./Attachments/OSGFilePathAttachmentBase.h
./Attachments/OSGFilePathAttachment.h
./Attachments/OSGFilePathAttachmentFields.h
./Util/OSGTextureUtils.h
./Util/OSGStringUtils.h
./Util/OSGIntrusivePtrImplBase.h
./Util/OSGRandomPoolManager.h
./Util/OSGFieldContainerUtils.h
./Util/OSGGLenumUtils.h
./Util/OSGCameraUtils.h
./Util/OSGMathUtils.h
./Util/OSGInterpolations.h
./Util/OSGQuatOperations.h
./OSGToolboxDef.h)

SET(SOURCES ./Types/OSGFieldContainerMapType.cpp
./Types/OSGStringMapType.cpp
./Types/OSGPathType.cpp
./FileIO/OSGFCFileHandler.cpp
./FileIO/OSGFCFileType.cpp
./FileIO/OSGXMLFCFileType.cpp
./FileIO/OSGBinFCFileType.cpp
./Attachments/OSGFilePathAttachmentBase.cpp
./Attachments/OSGFilePathAttachment.cpp
./Util/OSGStringUtils.cpp
./Util/OSGIntrusivePtrImplBase.cpp
./Util/OSGRandomPoolManager.cpp
./Util/OSGFieldContainerUtils.cpp
./Util/OSGGLenumUtils.cpp
./Util/OSGCameraUtils.cpp
./Util/OSGMathUtils.cpp
./Util/OSGTextureUtils.cpp)

SET(INLINES ./FileIO/OSGFCFileHandler.inl
./FileIO/OSGFCFileType.inl
./FileIO/OSGXMLFCFileType.inl
./FileIO/OSGBinFCFileType.inl
./Attachments/OSGFilePathAttachment.inl
./Attachments/OSGFilePathAttachmentBase.inl
./Util/OSGRandomPoolManager.inl
./Util/OSGIntrusivePtrImplBase.inl)

ADD_DEFINITIONS(-DOSG_COMPILETOOLBOXLIB)

SET(LIBRARY_NAME OSGToolbox)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OPENSG_INC_DIR} "./")
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${OPENSG_LIB_DIR})
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${HEADERS} ${SOURCES} ${INLINES})
ADD_LIBRARY(${LIBRARY_NAME}D SHARED ${HEADERS} ${SOURCES} ${INLINES})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_DEBUG "${OPENSG_CXX_FLAGS_DBG} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_RELEASE "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_MINSIZEREL "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS_RELWITHDEBINFO "${OPENSG_CXX_FLAGS_OPT} ${OPENSG_CXX_BUILDDLL_FLAGS}")
TARGET_LINK_LIBRARIES(${LIBRARY_NAME} RELEASE ${OPENSG_LIBS_DBG})
TARGET_LINK_LIBRARIES(${LIBRARY_NAME}D DEBUG ${OPENSG_LIBS_OPT})
