
// Source file for new Field type

// This define is only set in this source file. It switches the
// Windows-specific declarations in the header for compiling the Field, 
// not for using it.
#define OSG_COMPILEFILEPATHATTACHMENTINST

// You need this in every OpenSG file
#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

// The new field type include
#include <OpenSG/OSGAttachmentContainer.h>
#include "OSGFilePathAttachment.h"

OSG_USING_NAMESPACE

FieldDescription *FilePathAttachmentDesc::_desc[] =
{
    new FieldDescription(
        FieldTypeT::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(
            SimpleAttachment<FilePathAttachmentDesc>::SimpleField),
        false,
        (FieldAccessMethod) &SimpleAttachment<
                                  FilePathAttachmentDesc>::getFieldPtr)
};

OSG_BEGIN_NAMESPACE

OSG_FC_DLLEXPORT_DEF(SimpleAttachment,
                     FilePathAttachmentDesc,
                     OSG_TOOLBOXLIB_DLLTMPLMAPPING);


const Path getFilePath(AttachmentContainerPtr container)
{
    if(container == NullFC)
        return NULL;
   
    // Get attachment pointer
    AttachmentPtr att = 
        container->findAttachment(FilePath::getClassType().getGroupId());

    if(att == NullFC)
        return NULL;
   
    // Cast to name pointer                           

    FilePathPtr PathAttachment = FilePathPtr::dcast(att);

    if(PathAttachment == NullFC)
        return NULL;
   
    return PathAttachment->getFieldPtr()->getValue();
}

void setFilePath(      AttachmentContainerPtr  container, 
             const Path            &ThePath)
{
    if(container == NullFC)
    {
        FFATAL(("setName: no container?!?\n"));
        return;
    }
   
    // Get attachment pointer

    FilePathPtr PathAttachment = NullFC;
    AttachmentPtr att  = 
        container->findAttachment(FilePath::getClassType().getGroupId());
    
    if(att == NullFC)
    {
        PathAttachment = FilePath::create();
        beginEditCP(container, AttachmentContainer::AttachmentsFieldMask);
        {
            container->addAttachment(PathAttachment);
        }
        endEditCP(container, AttachmentContainer::AttachmentsFieldMask);
    }
    else
    {   
        PathAttachment = FilePathPtr::dcast(att);

        if(PathAttachment == NullFC)
        {
            FFATAL(("setFilePath: FilePath Attachment is not castable to FilePath?!?\n"));
            return;
        }
    }
    
  
    beginEditCP(PathAttachment);
    {
        PathAttachment->getFieldPtr()->setValue(ThePath);   
    }
    endEditCP(PathAttachment);
}

OSG_END_NAMESPACE
