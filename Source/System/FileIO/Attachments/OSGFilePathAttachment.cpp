/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFilePathAttachment.h"
#include "OSGImageFileHandler.h"
#include "OSGSceneFileHandler.h"
//#include "OSGProxyGroup.h"
#include "OSGFCFileHandler.h"

#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFilePathAttachmentBase.cpp file.
// To modify it, please change the .fcd file (OSGFilePathAttachment.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

FilePathAttachment::FileAttachmentHandlerMap FilePathAttachment::_HandlerMap = FilePathAttachment::FileAttachmentHandlerMap();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FilePathAttachment::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


const BoostPath* FilePathAttachment::getFilePath(      const AttachmentContainer*  container)
{
    if(container == NULL)
        return NULL;

    // Get attachment pointer
    AttachmentUnrecPtr att = 
        container->findAttachment(FilePathAttachment::getClassType().getGroupId());

    if(att == NULL)
        return NULL;

    // Cast to name pointer                           

    FilePathAttachmentUnrecPtr PathAttachment = dynamic_pointer_cast<FilePathAttachment>(att);

    if(PathAttachment == NULL)
        return NULL;

    return &(PathAttachment->getPath());
}

void   FilePathAttachment::setFilePath(      AttachmentContainer*  container, 
                                             const BoostPath            &ThePath     )
{
    if(container == NULL)
    {
        FFATAL(("setFilePath: no container?!?\n"));
        return;
    }

    // Get attachment pointer

    FilePathAttachmentUnrecPtr PathAttachment = NULL;
    AttachmentUnrecPtr att  = 
        container->findAttachment(FilePathAttachment::getClassType().getGroupId());

    if(att != NULL)
    {
        container->subAttachment(att);
    }

    PathAttachment = FilePathAttachment::create();
    PathAttachment->setPath(ThePath);   

    container->addAttachment(PathAttachment);

}

NodeUnrecPtr  LoadXML(std::string FilePath)
{
    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(BoostPath(FilePath));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {

        if( (*Itor)->getType() == Node::getClassType() &&
                dynamic_pointer_cast<Node>(*Itor)->getParent() == NULL)
        {
            return dynamic_pointer_cast<Node>(*Itor);
        }
    }
    return NULL;
}

bool isFileXML(std::string FilePath)
{
    std::string::size_type LastDotPos = FilePath.find_last_of(".");
    ++LastDotPos;
    std::string Extension(FilePath.substr(LastDotPos, FilePath.length() - LastDotPos));

    return Extension.compare("xml") == 0;
}

bool FilePathAttachment::shouldUseOnlyFileHandler(const FieldContainerType &FCType)
{
    //Check Handler first
    if(_HandlerMap.find(FCType.getCName()) != _HandlerMap.end())
    {
        return (_HandlerMap.find(FCType.getCName())->second.second);
    }

    return true;
}

FieldContainerUnrecPtr FilePathAttachment::loadFromFilePath(BoostPath &LoadFilePath, const FieldContainerType &FCType)
{
    FieldContainerUnrecPtr Result(NULL);
    try
    {
        if(boost::filesystem::exists(LoadFilePath))
        {
            //Check Handler first
            if(_HandlerMap.find(FCType.getCName()) != _HandlerMap.end())
            {
                Result = (_HandlerMap.find(FCType.getCName())->second.first)(LoadFilePath);
            }

            //Image
            else if(FCType.isDerivedFrom(Image::getClassType()))
            {
                ImageUnrecPtr TheImage = ImageFileHandler::the()->read(LoadFilePath.string().c_str());
                Result = TheImage;
            }
            //Model Node
            else if(FCType.isDerivedFrom(Node::getClassType()))
            {
                NodeUnrecPtr TheNode;
                if(isFileXML(LoadFilePath.string()))
                {
                    TheNode = LoadXML(LoadFilePath.string());
                }
                else
                {
                    TheNode = SceneFileHandler::the()->read(LoadFilePath.string().c_str(),NULL);
                }

                Result = TheNode;
            }
            //ProxyGroup Core
            /*else if(FCType.isDerivedFrom(ProxyGroup::getClassType()))
            {
                ProxyGroupUnrecPtr TheProxyGroup = ProxyGroup::create();
                TheProxyGroup->setUrl(LoadFilePath.string().c_str());
                TheProxyGroup->setEnabled(true);
                TheProxyGroup->setConcurrentLoad(true);

                Result = TheProxyGroup;
            }*/

            //If not loaded, try loading as a generic FC file
            if(Result == NULL && isFileXML(LoadFilePath.string()))  //Other
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
    catch(boost::filesystem::basic_filesystem_error<BoostPath> &)
    {
        return NULL;
    }

    if(Result != NULL &&
       Result->getType().isDerivedFrom(AttachmentContainer::getClassType()))
    {
        setFilePath(dynamic_pointer_cast<AttachmentContainer>(Result), LoadFilePath);
    }

    return Result;
}

bool FilePathAttachment::registerHandler(const FieldContainerType& TheType,
                                 FileAttachmentHandler TheHandler,
                                 bool UseOnlyFileHandler)
{
    if(_HandlerMap.find(TheType.getCName()) != _HandlerMap.end())
    {
        SWARNING << "FilePathAttachment: Could not register File Path Attachment Handler for Type " << TheType.getCName() << " because a handler for that type is already registered."  << std::endl;
        return false;
    }
    else
    {
        _HandlerMap[TheType.getCName()] = HandlerPair(TheHandler,UseOnlyFileHandler);
        return true;
    }
}

bool FilePathAttachment::unregisterHandler(const FieldContainerType& TheType)
{
    if(_HandlerMap.find(TheType.getCName()) != _HandlerMap.end())
    {
        _HandlerMap.erase(_HandlerMap.find(TheType.getCName()));
        return true;
    }
    else
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

void FilePathAttachment::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FilePathAttachment::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FilePathAttachment NI" << std::endl;
}

OSG_END_NAMESPACE
