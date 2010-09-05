MACRO(OSG_CONFIGURE_VLC)
    
    IF(OSG_ENABLE_VIDEO_VLC)
    
        IF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)
    
            IF(EXISTS ${OSG_SUPPORT_ROOT}/include/vlc/vlc.h)
                SET(VLC_INCLUDE_DIR ${OSG_SUPPORT_ROOT}/include CACHE PATH "" FORCE)
            ENDIF()
    
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osgvlc.lib)
                SET(VLC_LIBRARY_RELEASE ${OSG_SUPPORT_ROOT}/lib/osgvlc.lib)
            ENDIF()
            IF(EXISTS ${OSG_SUPPORT_ROOT}/lib/osggdalD.lib)
                SET(VLC_LIBRARY_DEBUG ${OSG_SUPPORT_ROOT}/lib/osgvlcD.lib)
            ENDIF()
    
            IF(VLC_INCLUDE_DIR)
              IF(VLC_LIBRARY_DEBUG OR VLC_LIBRARY_RELEASE)
                SET(VLC_FOUND TRUE)
              ENDIF()
            ENDIF()
    
            IF(VLC_FOUND)
              OSG_ADD_IMPORT_LIB(OSG_VLC_TARGETS VLC_LIBRARY)
              SET(VLC_LIBRARIES ${OSG_VLC_TARGETS} CACHE STRING "" FORCE)
            ENDIF(VLC_FOUND)
    
        ENDIF(OSG_USE_OSGSUPPORT_LIBS AND WIN32)
    
        IF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT VLC_FOUND)
            OSG_FIND_PACKAGE(VLC)
        ENDIF(NOT OSG_USE_OSGSUPPORT_LIBS OR NOT VLC_FOUND)
    
        IF(VLC_FOUND)
            OSG_SET(OSG_WITH_VLC 1)
        ENDIF(VLC_FOUND)
        
    ELSE(OSG_ENABLE_VIDEO_VLC)
        OSG_SET(OSG_WITH_VLC 0)
    ENDIF(OSG_ENABLE_VIDEO_VLC)
ENDMACRO(OSG_CONFIGURE_VLC)

