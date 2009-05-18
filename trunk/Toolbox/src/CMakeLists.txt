
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
./Util/OSGColorOperations.h
./Util/OSGStringUtils.h
./Util/OSGIntrusivePtrImplBase.h
./Util/OSGRandomPoolManager.h
./Util/OSGPntOperations.h
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

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OPENSG_INC_DIR} "./")
ADD_LIBRARY(OSGToolBox SHARED ${HEADERS} ${SOURCES} ${INLINES})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
TARGET_LINK_LIBRARIES(OSGToolbox ${OPENSG_LIBS})
