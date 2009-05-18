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

#include "OSGFilePathAttachment.h"
#include <boost/filesystem/operations.hpp>

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

bool FilePathAttachment::loadFromFilePath(AttachmentContainerPtr  container)
{
	const Path* LoadFilePath = FilePathAttachment::getFilePath(container);
	try
	{
		if(LoadFilePath != NULL && boost::filesystem::exists(*LoadFilePath))
		{
			if(container->getType().isDerivedFrom(Image::getClassType()))
			{
			  ImagePtr TheImage = Image::Ptr::dcast(container);
				ImageFileHandler::the().read(TheImage,LoadFilePath->string().c_str());
                                container = TheImage;
			}
			else if(container->getType().isDerivedFrom(Node::getClassType()))
			{
				NodePtr TheNode = SceneFileHandler::the().read(LoadFilePath->string().c_str());

				beginEditCP(container);
					Node::Ptr::dcast(container)->setCore(TheNode->getCore());
					while(TheNode->getNChildren() > 0)
					{
						NodePtr ChildNode(TheNode->getChild(TheNode->getNChildren()-1));
						Node::Ptr::dcast(container)->addChild(ChildNode);
						//TheNode->subChild(TheNode->getNChildren()-1);
					}
				endEditCP(container);
				
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	catch(boost::filesystem::basic_filesystem_error<Path> &)
	{
		return false;
	}
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

