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

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGField.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerFields.h"
#include "OSGAttachmentContainer.h"
#include "OSGNameAttachment.h"
#include "OSGFilePathAttachment.h"

#include "OSGXMLFCFileType.h"
#include "OSGNode.h"
#include "OSGContainerGatherUtils.h"
#include "OSGContainerUtils.h"

#include "OSGStringUtils.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
#include <sstream>
#include <utility>
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XMLFCFileType
A XMLFCFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

XMLFCFileType*  XMLFCFileType::_the(new XMLFCFileType());

std::string XMLFCFileType::NameAttachmentXMLToken = "nameAttachment";
std::string XMLFCFileType::FileAttachmentXMLToken = "filePathAttachment";
std::string XMLFCFileType::FieldContainerIDXMLToken = "fieldcontainerid";
std::string XMLFCFileType::AttachmentsXMLToken = "attachments";
std::string XMLFCFileType::RootFCXMLToken = "OSGFieldContainers";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

XMLFCFileType *XMLFCFileType::the(void)
{
	return _the;
}

void XMLFCFileType::printXMLParseError(const rapidxml::parse_error& Error,
                                  const std::string&           StreamText,
	                     const std::string& FileNameOrExtension)
{
    Int32 LineNum;
    Int32 LineStartPos;
    getLine(StreamText, Error.where<char>() - &StreamText[0],LineNum,LineStartPos);
    
	// print out where the error occured
    SWARNING << FileNameOrExtension << ": Parse error on line: " << LineNum << std::endl
             << "    " << Error.what() << "." << std::endl
	         << std::endl;
    
}

void XMLFCFileType::printXMLSemanticError(const std::string& ErrorDesc,
                                  const std::string& StreamText,
                                  Int32 ErrorPos,
                                  const std::string& FileNameOrExtension)
{
    Int32 LineNum;
    Int32 LineStartPos;
    getLine(StreamText, ErrorPos,LineNum,LineStartPos);
    
	// print out where the error occured
    SWARNING << FileNameOrExtension << ": Error on line: " << LineNum << std::endl
             << "    " << ErrorDesc << "." << std::endl
	         << std::endl;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string XMLFCFileType::getName(void) const
{
	return std::string("XMLFCFileType");
}

XMLFCFileType::FCPtrStore XMLFCFileType::read(std::istream &InputStream,
	                     const std::string& FileNameOrExtension) const
{
	std::string StreamText;
    //Load the text stream into data
    {
        std::stringstream StringStreamText;
        StringStreamText << InputStream.rdbuf();
        StreamText = StringStreamText.str();
    }

	FCPtrStore Result;

    //Create the Xml document from the text
    rapidxml::xml_document<char> doc;    // character type defaults to char
    try
    {
        //doc.parse<rapidxml::parse_non_destructive | rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(const_cast<char *>(StreamText.str().c_str()));
        doc.parse<rapidxml::parse_non_destructive | rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(const_cast<char *>(&StreamText[0]));
    }
    catch (rapidxml::parse_error& e)
    {
        printXMLParseError(e, StreamText, FileNameOrExtension);
        return Result;
    }


    IDLookupMap TheIDLookupMap;
    FCIdMapper TheFCIdMapper(&TheIDLookupMap);
    Path RootPath = FCFileHandler::the()->getRootFilePath();

    FieldContainerUnrecPtr NewFieldContainer;
    const FieldDescriptionBase* Desc;
    EditFieldHandlePtr TheFieldHandle;
    std::string FieldValue;
    IDLookupMap::iterator FCInfoIter;
    UInt32 CurrentFieldContainerOldId;
    //xmlpp::xmlattributes::const_iterator SearchItor;
    
    rapidxml::attribute_iterator<char> AttributeIterator;

    XMLHandlerMap::const_iterator HandlerSearchItor;

        //Create all of the Fields
    TheIDLookupMap = createFieldContainers(rapidxml::node_iterator<char>(doc.first_node(RootFCXMLToken.c_str())), rapidxml::node_iterator<char>(), FileNameOrExtension);
    
    FieldContainerFactory::the()->setMapper(&TheFCIdMapper);

    //Vector to hold the Mask of fields changed for each read FieldContainer
    typedef std::pair<FieldContainerUnrecPtr, BitVector> FieldContainerChangedPair;
    typedef std::vector<FieldContainerChangedPair > ChangedFieldsVector;
    typedef ChangedFieldsVector::iterator ChangedFieldsVectorItor;

    ChangedFieldsVector ChangedFieldsVec;

    for(rapidxml::node_iterator<char> NodeListItor(doc.first_node(RootFCXMLToken.c_str())) ; NodeListItor!=rapidxml::node_iterator<char>() ; ++NodeListItor)
    {
        //Find the FieldContainerId Token
        rapidxml::xml_attribute<char> *IdAttrib(NodeListItor->first_attribute(FieldContainerIDXMLToken.c_str()));
        if(IdAttrib == NULL)
        {
            printXMLSemanticError( "Couldn't find "+FieldContainerIDXMLToken+" attribute for '" + std::string(NodeListItor->name(), NodeListItor->name_size()) + "'!",
                                   StreamText,
                                   IdAttrib->value() - StreamText.c_str(),
                                   FileNameOrExtension);
            continue;
        }
        //Get the FieldContainer with that ID
        CurrentFieldContainerOldId = TypeTraits<UInt32>::getFromCString(std::string(IdAttrib->value(), IdAttrib->value_size()).c_str());
        FCInfoIter = TheIDLookupMap.find(CurrentFieldContainerOldId);
        if(FCInfoIter == TheIDLookupMap.end())
        {
            printXMLSemanticError("No matching container found for ID " +
                                   std::string(IdAttrib->value(), IdAttrib->value_size()) + "." ,
                                   StreamText,
                                   IdAttrib->value() - StreamText.c_str(),
                                   FileNameOrExtension);

            continue;
        }

        if(FCInfoIter->second._Read)
        {
            printXMLSemanticError("A FieldContainer by this Id has already been written to.  Subsequent definitions will overwrite the previous ones. Original ID: " +
                                   boost::lexical_cast<std::string>(CurrentFieldContainerOldId) +
                                   ", new ID: " +
                                   boost::lexical_cast<std::string>(FCInfoIter->second._NewId),
                                   StreamText,
                                   IdAttrib->value() - StreamText.c_str(),
                                   FileNameOrExtension);
        }
        NewFieldContainer = FCInfoIter->second._Ptr;
        //if(NewFieldContainer->getType().isDerivedFrom(AttachmentContainer::getClassType()))
        //{
        //	//Search for File attachment
        //	SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(FileAttachmentXMLToken));
        //	if(SearchItor != (*NodeListItor)->get_attrmap().end())
        //	{
//                    Result.insert(NewFieldContainer);
//                    continue;
        //	}
        //}

        if(NewFieldContainer != NULL)
        {
            BitVector ChangedFields = 0;
            for(AttributeIterator = rapidxml::attribute_iterator<char>(&(*NodeListItor)); AttributeIterator != rapidxml::attribute_iterator<char>(); ++AttributeIterator)
            {
                std::string FieldName(AttributeIterator->name(), AttributeIterator->name_size());
                if(FieldName.compare(FieldContainerIDXMLToken) == 0 ||
                   FieldName.compare(NameAttachmentXMLToken) == 0 ||
                   FieldName.compare(FileAttachmentXMLToken) == 0)
                {
                    continue;
                }
                FieldValue = std::string(AttributeIterator->value(), AttributeIterator->value_size());

                if(NewFieldContainer->getType().isDerivedFrom(AttachmentContainer::getClassType()) &&
                        FieldName.compare(AttachmentsXMLToken) == 0)
                {
                    //Get all of the attachments
                    FieldContainerUnrecPtr TheFC;
                    std::vector< std::string > SplitVec;
                    boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(std::string(";")) );
                    for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
                    {
                        if(SplitVec[SplitIndex].empty())
                        {
                            continue;
                        }
                        try
                        {
                            UInt32 FCId;
                            FCId = boost::lexical_cast<UInt32>(SplitVec[SplitIndex].c_str());
                            IDLookupMap::const_iterator FCInfoSearch(TheIDLookupMap.find(FCId));
                            if( FCInfoSearch == TheIDLookupMap.end())
                            {
                                if(FCId != 0)
                                {
                                    printXMLSemanticError( "Could not find Attachment referenced with Id: " + SplitVec[SplitIndex],
                                                           StreamText,
                                                           AttributeIterator->value() - StreamText.c_str(),
                                                           FileNameOrExtension);
                                }
                                TheFC = NULL;
                            }
                            else
                            {
                                TheFC = FCInfoSearch->second._Ptr;
                            }
                        }
                        catch(boost::bad_lexical_cast&)
                        {
                            TheFC = getFieldContainer(SplitVec[SplitIndex].c_str());
                            if(TheFC == NULL)
                            {
                                printXMLSemanticError( "Could not find Attachment referenced with Id: " + SplitVec[SplitIndex],
                                                       StreamText,
                                                       AttributeIterator->value() - StreamText.c_str(),
                                                       FileNameOrExtension);
                            }
                        }
                        if(TheFC != NULL)
                        {
                            //Check if the type of the FieldContainer Pointed to is derived from Attachment
                            if(TheFC->getType().isDerivedFrom(Attachment::getClassType()))
                            {
                                dynamic_pointer_cast<AttachmentContainer>(NewFieldContainer)->addAttachment(dynamic_pointer_cast<Attachment>(TheFC));
                            }
                            else
                            {
                                printXMLSemanticError( "Attempting to add a FieldContainer that is not derived from Attachment to the attachments.  Type of Field container with id: "
                                     + FieldValue + " attemped to assign: " + TheFC->getType().getCName(),
                                                                                   StreamText,
                                                                                   AttributeIterator->value() - StreamText.c_str(),
                                                                                   FileNameOrExtension);
                            }
                        }
                    }
                    continue;
                }
                Desc = NewFieldContainer->getFieldDescription(FieldName.c_str());
                if(Desc == NULL)
                {
                    printXMLSemanticError(" There is no Field named: " + FieldName +
                        ", for FieldContainers of Type: " + NewFieldContainer->getType().getCName(),
                                                                       StreamText,
                                                                       AttributeIterator->value() - StreamText.c_str(),
                                                                       FileNameOrExtension);
                }
                else
                {
                    TheFieldHandle = NewFieldContainer->editField(Desc->getFieldId());
                    if(TheFieldHandle == NULL)
                    {
                        continue;
                    }
                    ChangedFields = ChangedFields | Desc->getFieldMask();
                    if(Desc->getFieldType().isPtrField())
                    {
                        if(Desc->getFieldType().getCardinality() == FieldType::SingleField)
                        {
                            FieldContainerUnrecPtr TheFC;
                            try
                            {
                                UInt32 FCId;
                                FCId = boost::lexical_cast<UInt32>(FieldValue.c_str());
                                IDLookupMap::const_iterator FCInfoSearch(TheIDLookupMap.find(FCId));
                                if( FCInfoSearch == TheIDLookupMap.end())
                                {
                                    if(FCId != 0)
                                    {
                                        printXMLSemanticError("Could not find Container referenced with Id: " + FieldValue,
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                    }
                                    TheFC = NULL;
                                }
                                else
                                {
                                    TheFC = FCInfoSearch->second._Ptr;
                                }
                            }
                            catch(boost::bad_lexical_cast&)
                            {
                                TheFC = getFieldContainer(FieldValue);
                                if(TheFC == NULL)
                                {
                                        printXMLSemanticError("Could not find Container referenced with Id: " + FieldValue,
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                }
                            }
                            if(TheFC != NULL)
                            {
                                //Check if the type of the FieldContainer Pointed to is derived from the type
                                //expected for this field
                                if(isFieldContentDerivedFrom( Desc->getFieldType(),&(TheFC->getType())))
                                {

                                    static_cast<SFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->setValue(TheFC);
                                }
                                else
                                {
                                    printXMLSemanticError( "Attempting to assign a FieldContainerUnrecPtr to field: " 
                                                            + std::string(Desc->getCName()) + " of different types. Type of field: " 
                                                            + std::string(Desc->getFieldType().getContentType().getCName()) + ". Type of Field container with id: " 
                                                            + FieldValue + " attemped to assign: " + std::string(TheFC->getType().getCName()),
                                                           StreamText,
                                                           AttributeIterator->value() - StreamText.c_str(),
                                                           FileNameOrExtension);
                                    static_cast<SFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->setValue(NULL);
                                }
                            }
                            else
                            {
                                static_cast<SFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->setValue(NULL);
                            }
                        }
                        else if(Desc->getFieldType().getCardinality() == FieldType::MultiField &&
                            !FieldValue.empty())
                        {
                            std::vector< std::string > SplitVec;
                            boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(std::string(";")) );
                            for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
                            {
                                FieldContainerUnrecPtr TheFC;
                                try
                                {
                                    UInt32 FCId;
                                    FCId = boost::lexical_cast<UInt32>(SplitVec[SplitIndex].c_str());
                                    IDLookupMap::const_iterator FCInfoSearch(TheIDLookupMap.find(FCId));
                                    if( FCInfoSearch == TheIDLookupMap.end())
                                    {
                                        if(FCId != 0)
                                        {
                                            printXMLSemanticError("Could not find Container referenced with Id: " + SplitVec[SplitIndex],
                                                                   StreamText,
                                                                   AttributeIterator->value() - StreamText.c_str(),
                                                                   FileNameOrExtension);
                                        }
                                        TheFC = NULL;
                                    }
                                    else
                                    {
                                        TheFC = FCInfoSearch->second._Ptr;
                                    }
                                }
                                catch(boost::bad_lexical_cast&)
                                {
                                    TheFC = getFieldContainer(SplitVec[SplitIndex]);
                                    if(TheFC == NULL)
                                    {
                                        printXMLSemanticError("Could not find Container referenced with Id: " + SplitVec[SplitIndex],
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                    }
                                }
                                if(TheFC != NULL)
                                {
                                    //Check if the type of the FieldContainer Pointed to is derived from the type
                                    //expected for this field
                                    if(isFieldContentDerivedFrom( Desc->getFieldType(),&(TheFC->getType())))
                                    {
                                        static_cast<MFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->push_back(TheFC);
                                    }
                                    else
                                    {
                                        printXMLSemanticError( "Attempting to assign a FieldContainerPtr to a field of different types. Type of field: " 
                                                                + std::string(Desc->getFieldType().getContentType().getCName()) + ". Type of Field container with id: " 
                                                                + SplitVec[SplitIndex] + " attemped to assign: " + TheFC->getType().getCName(),
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                    }
                                }
                                
                            }
                        }
                    }
                    else
                    {
                        if(Desc->getFieldType().getCardinality() == FieldType::SingleField)
                        {
                            if(Desc->getFieldType() == SFPath::getClassType())
                            {
                                //If the field type is a Path
                                Path TheFilePath(FieldValue.c_str());
                                if(!TheFilePath.has_root_path())
                                {
                                    TheFilePath = RootPath / TheFilePath;
                                }
                                static_cast<SFPath*>(TheFieldHandle->getField())->setValue(TheFilePath);
                            }
                            else
                            {
                                TheFieldHandle->pushValueFromCString(FieldValue.c_str());
                            }
                        }
                        else if(Desc->getFieldType().getCardinality() == FieldType::MultiField &&
                            !FieldValue.empty())
                        {
                            std::vector< std::string > SplitVec;
                            boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(std::string(";")) );
                            for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
                            {
                                if(Desc->getFieldType() == MFPath::getClassType())
                                {
                                    //If the field type is a Path
                                    Path TheFilePath(SplitVec[SplitIndex].c_str());
                                    if(!TheFilePath.has_root_path())
                                    {
                                        TheFilePath = RootPath / TheFilePath;
                                    }
                                    static_cast<MFPath*>(TheFieldHandle->getField())->push_back(TheFilePath);
                                }
                                else
                                {
                                    TheFieldHandle->pushValueFromCString(SplitVec[SplitIndex].c_str());
                                }
                            }
                        }
                    }
                }
            }
            //ChangedFieldsVec.push_back(FieldContainerChangedPair(NewFieldContainer, ChangedFields));

            try
            {
                XMLHandlerMap::const_iterator _MapItor = _HandlerMap.find(&NewFieldContainer->getType());
                if(_MapItor != _HandlerMap.end())
                    (_MapItor->second.first)(*NodeListItor,TheIDLookupMap,NewFieldContainer);
            }
            catch(XMLFCException& e)
            {
                printXMLSemanticError( e.getMessage(),
                                       StreamText,
                                       e.getNode().value() - StreamText.c_str(),
                                       FileNameOrExtension);
            }

            Result.insert(NewFieldContainer);
            FCInfoIter->second._Read = true;
        }
        else
        {
            printXMLSemanticError("Could not create FieldContainer of type name " + std::string(NodeListItor->name(),NodeListItor->name_size()) +
                ", because no such Field Container types are registered in the Field Container Factory",
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
        }
    }

    //Send the changed event to each FieldContainer
    //for the fields that were changed

    //for(ChangedFieldsVectorItor Itor(ChangedFieldsVec.begin()) ; Itor != ChangedFieldsVec.end() ; ++Itor)
    //{
        //changedCP(Itor->first, Itor->second);
    //}
    commitChanges();
    

    FieldContainerFactory::the()->setMapper(NULL);
	return Result;
}

XMLFCFileType::IDLookupMap XMLFCFileType::createFieldContainers(rapidxml::node_iterator<char> Begin, rapidxml::node_iterator<char> End,
	                     const std::string& FileNameOrExtension) const
{
	//FieldContainerFactory::TypeIdMap ContainerOldIdMap;
	FCInfoStruct NewFCInfo;
	UInt32 OldFCId;
	IDLookupMap OldToNewFCLookupMap;
    const FieldContainerType *FCType;
    Path RootPath = FCFileHandler::the()->getRootFilePath();
    //Create all of the Fields
    for(rapidxml::node_iterator<char> NodeListItor(Begin) ; NodeListItor!=End ; ++NodeListItor)
    {
        NewFCInfo._Ptr = NULL;
        std::string TypeName(NodeListItor->name(), NodeListItor->name_size());
        FCType = FieldContainerFactory::the()->findType(TypeName.c_str());

        //If it is a Attachment Container Type
        if(FCType != NULL && FCType->isDerivedFrom(AttachmentContainer::getClassType()))
        {
            //Check if there is a File attachment
            rapidxml::xml_attribute<char> *FileAttachmentAttrib(NodeListItor->first_attribute(FileAttachmentXMLToken.c_str()));

            //If there is a file attachment then attempt to load this contianer from that file
            if(FileAttachmentAttrib != NULL)
            {
                Path TheFilePath(FileAttachmentAttrib->value(), FileAttachmentAttrib->value() + FileAttachmentAttrib->value_size());
                if(!TheFilePath.has_root_path())
                {
                    TheFilePath = RootPath / TheFilePath;
                }

                try{
                    if(boost::filesystem::exists(TheFilePath))
                    {

                        NewFCInfo._Ptr = FilePathAttachment::loadFromFilePath(TheFilePath, *FCType);
                        if(NewFCInfo._Ptr == NULL)
                        {
                            SWARNING <<
                                "ERROR in XMLFCFileType::read():" <<
                                "could not load type: " << NewFCInfo._Ptr->getType().getCName() <<
                                " from file " <<TheFilePath.string() <<
                                std::endl;
                        }
                        else
                        {
                            FilePathAttachment::setFilePath(dynamic_pointer_cast<AttachmentContainer>(NewFCInfo._Ptr),TheFilePath);
                        }
                    }
                    else
                    {
                        SWARNING <<
                            "ERROR in XMLFCFileType::read():" <<
                            "could not load type: " << FCType->getCName() <<
                            " from file " <<TheFilePath.string() << " because that file does not exist." <<
                            std::endl;
                    }
                }
                catch(boost::filesystem::basic_filesystem_error<Path>& e)
                {
                    SWARNING <<
                        "ERROR in XMLFCFileType::read():" <<
                        "could not load type: " << FCType->getCName() <<
                        " from file " <<TheFilePath.string() << " because that file does not exist." << ". Error: " << e.what() <<
                        std::endl;
                }
            }
        }
        if(NewFCInfo._Ptr == NULL)
        {
            NewFCInfo._Ptr = FieldContainerFactory::the()->createContainer(std::string(NodeListItor->name(), NodeListItor->name_size()).c_str());
        }

        if(NewFCInfo._Ptr == NULL)
        {
            SWARNING << FileNameOrExtension << ": Couldn't create unknown FieldContainer with type '" << std::string(NodeListItor->name(), NodeListItor->name_size()) << "'!" << std::endl;
        }
        else
        {
            //If there is a name attachment, than attach a name to this container
            if(NewFCInfo._Ptr->getType().isDerivedFrom(AttachmentContainer::getClassType()))
            {
                //Search for name attachment xml token
                rapidxml::xml_attribute<char> *NameAttrib(NodeListItor->first_attribute(NameAttachmentXMLToken.c_str()));
                if(NameAttrib != NULL)
                {
                    setName(dynamic_pointer_cast<AttachmentContainer>(NewFCInfo._Ptr),std::string(NameAttrib->value(), NameAttrib->value_size()).c_str());
                }
            }


            //Attach the FieldID mapping to this container
            rapidxml::xml_attribute<char> *FieldContainerIdAttrib(NodeListItor->first_attribute(FieldContainerIDXMLToken.c_str()));
            if(FieldContainerIdAttrib == NULL)
            {
                SFATAL << FileNameOrExtension << ": Couldn't find "+FieldContainerIDXMLToken+" attribute for '" << std::string(NodeListItor->name(), NodeListItor->name_size()) << "'!" << std::endl;
            }
            OldFCId = TypeTraits<UInt32>::getFromCString(std::string(FieldContainerIdAttrib->value(), FieldContainerIdAttrib->value_size()).c_str());
            NewFCInfo._NewId = NewFCInfo._Ptr->getId();
            if(OldToNewFCLookupMap.insert(std::make_pair(OldFCId, NewFCInfo)).second == false)
            {
                SFATAL << FileNameOrExtension << ": ERROR in XMLFCFileType::createFieldContainers()" <<
                    std::endl;
            }
        }
    }
	return OldToNewFCLookupMap;
}

bool XMLFCFileType::write(const FCPtrStore &Containers, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension, const FCTypeVector& IgnoreTypes) const
{
    OutStream OSGOutputStream(OutputStream);

    Path RootPath = FCFileHandler::the()->getRootFilePath();

    //Get all of the dependent FieldContainers
    const std::set<FieldContainerUnrecPtr> IgnoreContainers;
    FCPtrStore AllContainers;
    AllContainers = getAllDependantFCs(Containers, IgnoreContainers, IgnoreTypes);


    OSGOutputStream << "<?xml version=\"1.0\"  encoding=\"utf-8\"?>" << std::endl << std::endl;
    OSGOutputStream << "<" << RootFCXMLToken << ">" << std::endl;

    for(FCPtrStore::const_iterator FCItor(AllContainers.begin()) ; FCItor != AllContainers.end() ; ++FCItor)
    {
        OSGOutputStream << "\t<" << (*FCItor)->getType().getCName() << std::endl;
        OSGOutputStream << "\t\t"+FieldContainerIDXMLToken+"=\"";
        TypeTraits<UInt32>::putToStream((*FCItor)->getId(), OSGOutputStream);
        OSGOutputStream << "\"" << std::endl;

        if((*FCItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
        {
            //Output Name
            const char* Name(OSG::getName(dynamic_pointer_cast<AttachmentContainer>(*FCItor)));
            if(Name != NULL)
            {
                OSGOutputStream << "\t\t" + NameAttachmentXMLToken + "=\"" << Name << "\"" << std::endl;
            }

            //Output FilePath
            const Path* FilePath(FilePathAttachment::getFilePath(dynamic_pointer_cast<AttachmentContainer>(*FCItor)));
            if(FilePath != NULL)
            {
                OSGOutputStream << "\t\t" + FileAttachmentXMLToken + "=\"" << FilePath->string() << "\"" << std::endl;
                continue;
            }

            //All of the others
            std::vector<std::string> AttachmentIds;
            AttachmentMap::const_iterator MapItor(dynamic_pointer_cast<AttachmentContainer>(*FCItor)->getSFAttachments()->getValue().begin());
            AttachmentMap::const_iterator MapEnd(dynamic_pointer_cast<AttachmentContainer>(*FCItor)->getSFAttachments()->getValue().end());
            for( ; MapItor!=MapEnd  ; ++MapItor)
            {
                if(MapItor->second->getType() != Name::getClassType() &&
                   MapItor->second->getType() != FilePathAttachment::getClassType())
                {
                    AttachmentIds.push_back(boost::lexical_cast<std::string>(MapItor->second->getId()));
                }
            }

            if(AttachmentIds.size() > 0)
            {
                OSGOutputStream << "\t\t" + AttachmentsXMLToken + "=\"";
                for( UInt32 i(0)  ; i<AttachmentIds.size()  ; ++i)
                {
                    if(i != 0) { OSGOutputStream << ";"; }
                    OSGOutputStream << AttachmentIds[i];
                }
                OSGOutputStream << "\"" << std::endl;
            }
		}

        //Write all of the Fields
        FieldContainerType& TheFCType((*FCItor)->getType());
        UInt32 NumFields(TheFCType.getNumFieldDescs());
        const FieldDescriptionBase* Desc;
        std::string FieldValue("");
        const Field* TheField(NULL);
        for(UInt32 i(1) ; i<NumFields+1 ; ++i)
        {
            Desc = (*FCItor)->getFieldDescription(i);
            if(Desc->getFieldType() == SFAttachmentPtrMap::getClassType())
            {
                continue;
            }
            if(Desc->isInternal())
            {
                if((*FCItor)->getType().isDerivedFrom(Node::getClassType()) &&
                    Desc == Node::getClassType().getFieldDesc(i))
                {
                }
                else
                {
                    continue;
                }
            }

            if((*FCItor)->getField(i) == NULL)
            {
                continue;
            }
            TheField = (*FCItor)->getField(i)->getField();
            if(Desc->getFieldType().isPtrField())
            {
                OSGOutputStream << "\t\t" << Desc->getCName() << "=\"";
                if(TheField->getCardinality() == FieldType::SingleField)
                {
                    if(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue() == NULL ||
                        std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()->getTypeId()) != IgnoreTypes.end())
                    {
                        TypeTraits<UInt32>::putToStream(0,OSGOutputStream);
                    }
                    else
                    {
                        TypeTraits<UInt32>::putToStream(static_cast<const SFUnrecFieldContainerPtr *>(TheField)->getValue()->getId(),OSGOutputStream);
                    }
                }
                else if(TheField->getCardinality() == FieldType::MultiField)
                {
                    for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
                    {
                        if(Index!=0)
                        {
                            OSGOutputStream << ";";
                        }
                        if(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](Index) == NULL ||
                            std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](Index)->getTypeId()) != IgnoreTypes.end())
                        {
                            TypeTraits<UInt32>::putToStream(0,OSGOutputStream);
                        }
                        else
                        {
                            TypeTraits<UInt32>::putToStream(static_cast<const MFUnrecFieldContainerPtr *>(TheField)->operator[](Index)->getId(),OSGOutputStream);
                        }
                    }
                }
                OSGOutputStream << "\"" << std::endl;
            }
            else if(TheField->getType() == SFPath::getClassType())
            {
                FieldValue.clear();
                //Path RootPath = boost::filesystem::system_complete(RootPath);
                Path FilePath = boost::filesystem::system_complete(static_cast<const SFPath*>(TheField)->getValue());
                //Path RelativePath = makeRelative(RootPath, FilePath);
                //FieldValue = RelativePath.string();//TheField->getValueByStr(FieldValue);
                OSGOutputStream << "\t\t" << Desc->getCName() << "=\"" << FilePath.string()  << "\"" << std::endl;
            }
            else if(TheField->getType() == MFPath::getClassType())
            {
                OSGOutputStream << "\t\t" << Desc->getCName() << "=\"" ;
                //Path RootPath = boost::filesystem::system_complete(RootPath);
                Path FilePath;
                //Path RelativePath;
                for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
                {
                    FieldValue.clear();
                    FilePath = boost::filesystem::system_complete((*static_cast<const MFPath*>(TheField))[Index]);
                    //RelativePath = makeRelative(RootPath, FilePath);
                    FieldValue = FilePath.string();
                    if(Index!=0)
                    {
                        OSGOutputStream << ";";
                    }
                    OSGOutputStream << FieldValue;
                }
                OSGOutputStream << "\"" << std::endl;
            }
            else
            {
                if(TheField->getCardinality() == FieldType::SingleField)
                {
                    //FieldValue.clear();
                    //TheField->pushValueToString(FieldValue);
                    //boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of(std::string("\"")));
                    //OSGOutputStream << "\t\t" << Desc->getCName() << "=\"" << FieldValue << "\"" << std::endl;
                    OSGOutputStream << "\t\t" << Desc->getCName() << "=\"";
                    TheField->pushValueToStream(OSGOutputStream);
                    OSGOutputStream << "\"" << std::endl;
                }
                else if(TheField->getCardinality() == FieldType::MultiField)
                {
                    OSGOutputStream << "\t\t" << Desc->getCName() << "=\"" ;
                    for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
                    {
                        //FieldValue.clear();
                        //TheField->pushValueToString(FieldValue, Index);
                        //boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of(std::string("\"")));
                        if(Index!=0)
                        {
                            OSGOutputStream << ";";
                        }
                        //OSGOutputStream << FieldValue;
                        TheField->pushValueToStream(OSGOutputStream, Index);
                    }
                    OSGOutputStream << "\"" << std::endl;
                }
            }
        }

        OSGOutputStream << "\t>" << std::endl;

        XMLHandlerMap::const_iterator XMLHandlerMapItor = _HandlerMap.find(&TheFCType);
        //TODO: Add Write Handler Code
        if(XMLHandlerMapItor != _HandlerMap.end())
            (XMLHandlerMapItor->second.second)(*FCItor,OutputStream);

        OSGOutputStream << "\t</" << TheFCType.getCName() << ">" << std::endl;
    }
    OSGOutputStream << "</" << RootFCXMLToken << ">" << std::endl << std::endl;

	return true;
}

bool XMLFCFileType::registerHandler(const FieldContainerType* HandleFCType, OpenSGToolboxXMLReadHandler TheReadHandler, OpenSGToolboxXMLWriteHandler TheWriteHandler)
{
	if(_HandlerMap.find(HandleFCType) != _HandlerMap.end())
    {
        SWARNING << "XMLFCFileType: Could not register XML Handler for XML token because a handler for that token is already registered."  << std::endl;
        return false;
    }
    else
    {
        _HandlerMap[HandleFCType] = HandlerFuncPair(TheReadHandler, TheWriteHandler);
        return true;
    }
}
     
bool XMLFCFileType::unregisterHandler(const FieldContainerType* HandleFCType)
{
    if(_HandlerMap.find(HandleFCType) != _HandlerMap.end())
    {
        _HandlerMap.erase(_HandlerMap.find(HandleFCType));
        return true;
    }
    else
    {
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

XMLFCFileType::XMLFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("xml")),
        false,
        50,
        FCFileType::OSG_READ_SUPPORTED | FCFileType::OSG_WRITE_SUPPORTED)
{
}

XMLFCFileType::XMLFCFileType(const XMLFCFileType &obj) : Inherited(obj)
{
}

XMLFCFileType::~XMLFCFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

XMLFCFileType::FCInfoStruct::FCInfoStruct() : _NewId(0),_Ptr(NULL),_Read(false)
{
}

XMLFCFileType::FCIdMapper::FCIdMapper(IDLookupMap *m): _PtrMap(m)
{
}

UInt32 XMLFCFileType::FCIdMapper::map(UInt32 uiId)
{
    UInt32 id = 0;
    IDLookupMap::const_iterator iterID = _PtrMap->find(uiId);
    if(!(iterID == _PtrMap->end()))
    {
        id = iterID->second._NewId;
    }

    return id;
}

OSG_END_NAMESPACE

