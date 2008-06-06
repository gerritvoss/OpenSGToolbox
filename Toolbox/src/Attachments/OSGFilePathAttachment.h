#ifndef _OSG_TOOLBOX_FILE_PATH_ATTACHMENT_H_
#define _OSG_TOOLBOX_FILE_PATH_ATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include "Types/OSGPathType.h"

OSG_BEGIN_NAMESPACE

struct FilePathAttachmentDesc
{
    static  FieldDescription *_desc[];

    typedef SFPath           FieldTypeT;

    static const Char8         *getTypeName  (void) 
    {
        return "FilePath";          
    }

    static const Char8         *getFieldName (void) 
    {
        return "filePath";          
    }

    static const Char8         *getGroupName (void) 
    { 
        return "filePath";          
    }

    static const Char8         *getParentTypeName(void) 
    {
        return "Attachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;  }

    static FieldDescription **getDesc      (void) { return _desc; }
};

typedef SimpleAttachment<FilePathAttachmentDesc  > FilePath;

typedef FCPtr           <AttachmentPtr,  FilePath> FilePathPtr;


class AttachmentContainerPtr;

OSG_TOOLBOXLIB_DLLMAPPING
const Path getFilePath(      AttachmentContainerPtr  container);

OSG_TOOLBOXLIB_DLLMAPPING
      void   setFilePath(      AttachmentContainerPtr  container, 
                     const Path            &ThePath     );
 

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEFILEPATHATTACHMENTINST
OSG_FC_DLLEXPORT_DECL(SimpleAttachment, 
                      FilePathAttachmentDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */


OSG_END_NAMESPACE


#endif /* _OSG_TOOLBOX_FILE_PATH_ATTACHMENT_H_ */
