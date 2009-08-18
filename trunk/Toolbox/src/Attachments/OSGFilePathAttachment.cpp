/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILETOOLBOXLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGProxyGroup.h>
#include "FileIO/OSGFCFileHandler.h"

#include "OSGFilePathAttachment.h"
#include <boost/filesystem/operations.hpp>
#include "FileIO/OSGFCFileHandler.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FilePathAttachment
A UI Component Interface. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FilePathAttachment::initMethod (void)
{
}

const Path* FilePathAttachment::getFilePath(      AttachmentContainerPtr  container)
{
    if(container == NullFC)
        return NULL;
   
    // Get attachment pointer
    AttachmentPtr att = 
        container->findAttachment(FilePathAttachment::getClassType().getGroupId());

    if(att == NullFC)
        return NULL;
   
    // Cast to name pointer                           

    FilePathAttachmentPtr PathAttachment = FilePathAttachmentPtr::dcast(att);

    if(PathAttachment == NullFC)
        return NULL;
   
    return &(PathAttachment->getPath());
}

void   FilePathAttachment::setFilePath(      AttachmentContainerPtr  container, 
                         const Path            &ThePath     )
{
    if(container == NullFC)
    {
        FFATAL(("setName: no container?!?\n"));
        return;
    }
   
    // Get attachment pointer

    FilePathAttachmentPtr PathAttachment = NullFC;
    AttachmentPtr att  = 
        container->findAttachment(FilePathAttachment::getClassType().getGroupId());
    
    if(att == NullFC)
    {
        PathAttachment = FilePathAttachment::create();
        beginEditCP(container, AttachmentContainer::AttachmentsFieldMask);
        {
            container->addAttachment(PathAttachment);
        }
        endEditCP(container, AttachmentContainer::AttachmentsFieldMask);
    }
    else
    {   
        PathAttachment = FilePathAttachmentPtr::dcast(att);

        if(PathAttachment == NullFC)
        {
            FFATAL(("setFilePath: FilePath Attachment is not castable to FilePath?!?\n"));
            return;
        }
    }
    
  
    beginEditCP(PathAttachment, FilePathAttachment::PathFieldMask);
    {
        PathAttachment->setPath(ThePath);   
    }
    endEditCP(PathAttachment, FilePathAttachment::PathFieldMask);
}

NodePtr  LoadXML(std::string FilePath)
{
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path(FilePath));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {

        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            return Node::Ptr::dcast(*Itor);
        }
    }
    return NullFC;
}

bool isFileXML(std::string FilePath)
{
    std::string::size_type LastDotPos = FilePath.find_last_of(".");
    ++LastDotPos;
    std::string Extension(FilePath.substr(LastDotPos, FilePath.length() - LastDotPos));

    return Extension.compare("xml") == 0;
}

FieldContainerPtr FilePathAttachment::loadFromFilePath(Path &LoadFilePath, const FieldContainerType &FCType)
{
	//const Path* LoadFilePath = FilePathAttachment::getFilePath(container);
    FieldContainerPtr Result(NullFC);
	try
	{
		if(boost::filesystem::exists(LoadFilePath))
		{
            //Image
			if(FCType.isDerivedFrom(Image::getClassType()))
			{
			    ImagePtr TheImage = ImageFileHandler::the().read(LoadFilePath.string().c_str());
                Result = TheImage;
			}
            //Model Node
			else if(FCType.isDerivedFrom(Node::getClassType()))
			{
                NodePtr TheNode;
                if(isFileXML(LoadFilePath.string()))
                {
                    TheNode = LoadXML(LoadFilePath.string());
                }
                else
                {
                    TheNode = SceneFileHandler::the().read(LoadFilePath.string().c_str(),NULL);
                }

                Result = TheNode;
			}
            //ProxyGourp Core
			else if(FCType.isDerivedFrom(ProxyGroup::getClassType()))
			{
                ProxyGroupPtr TheProxyGroup = ProxyGroup::create();
                beginEditCP(TheProxyGroup, ProxyGroup::UrlFieldMask | ProxyGroup::EnabledFieldMask | ProxyGroup::ConcurrentLoadFieldMask);
                    TheProxyGroup->setUrl(LoadFilePath.string().c_str());
                    TheProxyGroup->setEnabled(true);
                    TheProxyGroup->setConcurrentLoad(true);
                endEditCP(TheProxyGroup, ProxyGroup::UrlFieldMask | ProxyGroup::EnabledFieldMask | ProxyGroup::ConcurrentLoadFieldMask);

                Result = TheProxyGroup;
			}
            if(Result == NullFC)  //Other
            {
	            FCFileType::FCPtrStore NewContainers;
	            NewContainers = FCFileHandler::the()->read(LoadFilePath);
                
                FCFileType::FCPtrStore::iterator Itor;
                for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
                {

                    if( (*Itor)->getType() == FCType)
                    {
                        Result = (*Itor);
                        break;
                    }
                }
            }
		}
	}
	catch(boost::filesystem::basic_filesystem_error<Path> &)
	{
        return NullFC;
	}

    return Result;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FilePathAttachment::FilePathAttachment(void) :
    Inherited()
{
}

FilePathAttachment::FilePathAttachment(const FilePathAttachment &source) :
    Inherited(source)
{
}

FilePathAttachment::~FilePathAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FilePathAttachment::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FilePathAttachment::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FilePathAttachment NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFILEPATHATTACHMENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFILEPATHATTACHMENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFILEPATHATTACHMENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

