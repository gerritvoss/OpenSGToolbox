/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>



#include <OpenSG/OSGField.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include "Attachments/OSGFilePathAttachment.h"

#include "OSGXMLFCFileType.h"
#include "Util/OSGFieldContainerUtils.h"

#include "Util/OSGTextUtils.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
#include <sstream>
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

	FieldContainerPtr NewFieldContainer;
	const FieldDescription* Desc;
	Field* TheField;
	std::string FieldValue;
	IDLookupMap::iterator FCInfoIter;
	UInt32 CurrentFieldContainerOldId;
	//xmlpp::xmlattributes::const_iterator SearchItor;
    
    rapidxml::attribute_iterator<char> AttributeIterator;

    XMLHandlerMap::const_iterator HandlerSearchItor;

		//Create all of the Fields
	TheIDLookupMap = createFieldContainers(rapidxml::node_iterator<char>(doc.first_node(RootFCXMLToken.c_str())), rapidxml::node_iterator<char>(), FileNameOrExtension);
	
	FieldContainerFactory::the()->setMapper(&TheFCIdMapper);

    for(rapidxml::node_iterator<char> NodeListItor(doc.first_node(RootFCXMLToken.c_str())) ; NodeListItor!=rapidxml::node_iterator<char>() ; ++NodeListItor)
	{
		//Check if the Token is registerd by a handler
        HandlerSearchItor = _HandlerMap.find(std::string(NodeListItor->name(), NodeListItor->name_size()));
        if(HandlerSearchItor != _HandlerMap.end() )
        {
            if(!HandlerSearchItor->second(*NodeListItor, TheFCIdMapper))
            {
                printXMLSemanticError( "Failed to handle node with xml token: " +  std::string(NodeListItor->name(), NodeListItor->name_size()),
                                       StreamText,
                                       AttributeIterator->value() - StreamText.c_str(),
                                       FileNameOrExtension);
            }

            continue;
        }

        //Find the FieldContainerId Token
        rapidxml::xml_attribute<char> *IdAttrib(NodeListItor->first_attribute(FieldContainerIDXMLToken.c_str()));
		if(IdAttrib == NULL)
		{
            printXMLSemanticError( "Couldn't find "+FieldContainerIDXMLToken+" attribute for '" + std::string(NodeListItor->name(), NodeListItor->name_size()) + "'!",
                                   StreamText,
                                   AttributeIterator->value() - StreamText.c_str(),
                                   FileNameOrExtension);
            continue;
		}
		CurrentFieldContainerOldId = TypeTraits<UInt32>::getFromString(std::string(IdAttrib->value(), IdAttrib->value_size()).c_str());
		FCInfoIter = TheIDLookupMap.find(CurrentFieldContainerOldId);
		if(FCInfoIter == TheIDLookupMap.end())
		{
            printXMLSemanticError("No matching container found for ID " +
			                       std::string(IdAttrib->value(), IdAttrib->value_size()) + "." ,
                                   StreamText,
                                   AttributeIterator->value() - StreamText.c_str(),
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
                                   AttributeIterator->value() - StreamText.c_str(),
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

		if(NewFieldContainer != NullFC)
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
                    FieldContainerPtr TheFC;
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
                                TheFC = NullFC;
                            }
                            else
                            {
                                TheFC = FCInfoSearch->second._Ptr;
                            }
                        }
                        catch(boost::bad_lexical_cast&)
                        {
                            TheFC = getFieldContainer(SplitVec[SplitIndex].c_str());
                            if(TheFC == NullFC)
                            {
                                printXMLSemanticError( "Could not find Attachment referenced with Id: " + SplitVec[SplitIndex],
                                                       StreamText,
                                                       AttributeIterator->value() - StreamText.c_str(),
                                                       FileNameOrExtension);
                            }
                        }
                        if(TheFC != NullFC)
                        {
                            //Check if the type of the FieldContainer Pointed to is derived from Attachment
                            if(TheFC->getType().isDerivedFrom(Attachment::getClassType()))
                            {
                                AttachmentContainerPtr::dcast(NewFieldContainer)->addAttachment(AttachmentPtr::dcast(TheFC));
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
				Desc = NewFieldContainer->getType().findFieldDescription(FieldName.c_str());
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
					TheField = NewFieldContainer->getField(Desc->getFieldId());
                    ChangedFields = ChangedFields | Desc->getFieldMask();
					if(isFieldAFieldContainerPtr(TheField))
					{
						if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
						{
						    FieldContainerPtr TheFC;
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
									TheFC = NullFC;
								}
                                else
                                {
                                    TheFC = FCInfoSearch->second._Ptr;
                                }
							}
							catch(boost::bad_lexical_cast&)
							{
                                TheFC = getFieldContainer(FieldValue);
                                if(TheFC == NullFC)
                                {
                                        printXMLSemanticError("Could not find Container referenced with Id: " + FieldValue,
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                }
							}
                            if(TheFC != NullFC)
                            {
                                //Check if the type of the FieldContainer Pointed to is derived from the type
                                //expected for this field
                                if(isFieldConentDerivedFrom( TheField,&(TheFC->getType())))
                                {

						            static_cast<SFFieldContainerPtr *>(TheField)->setValue(TheFC);
                                }
                                else
                                {
                                    printXMLSemanticError( "Attempting to assign a FieldContainerPtr to a field of different types. Type of field: " 
                                                            + std::string(TheField->getContentType().getCName()) + ". Type of Field container with id: " 
                                                            + FieldValue + " attemped to assign: " + std::string(TheFC->getType().getCName()),
                                                           StreamText,
                                                           AttributeIterator->value() - StreamText.c_str(),
                                                           FileNameOrExtension);
						            static_cast<SFFieldContainerPtr *>(TheField)->setValue(NullFC);
                                }
                            }
                            else
                            {
                                static_cast<SFFieldContainerPtr *>(TheField)->setValue(NullFC);
                            }
						}
						else if(TheField->getCardinality() == FieldType::MULTI_FIELD &&
							!FieldValue.empty())
						{
							std::vector< std::string > SplitVec;
                            boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(std::string(";")) );
							for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
							{
						        FieldContainerPtr TheFC;
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
									    TheFC = NullFC;
								    }
                                    else
                                    {
                                        TheFC = FCInfoSearch->second._Ptr;
                                    }
							    }
							    catch(boost::bad_lexical_cast&)
							    {
                                    TheFC = getFieldContainer(SplitVec[SplitIndex]);
                                    if(TheFC == NullFC)
                                    {
                                        printXMLSemanticError("Could not find Container referenced with Id: " + SplitVec[SplitIndex],
                                                               StreamText,
                                                               AttributeIterator->value() - StreamText.c_str(),
                                                               FileNameOrExtension);
                                    }
							    }
                                if(TheFC != NullFC)
                                {
                                    //Check if the type of the FieldContainer Pointed to is derived from the type
                                    //expected for this field
                                    if(isFieldConentDerivedFrom( TheField,&(TheFC->getType())))
                                    {
                                        static_cast<MFFieldContainerPtr *>(TheField)->push_back(TheFC);
                                    }
                                    else
                                    {
                                        printXMLSemanticError( "Attempting to assign a FieldContainerPtr to a field of different types. Type of field: " 
                                                                + std::string(TheField->getContentType().getCName()) + ". Type of Field container with id: " 
                                                                + FieldValue + " attemped to assign: " + TheFC->getType().getCName(),
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
						if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
						{
							if(TheField->getType() == SFPath::getClassType())
							{
								//If the field type is a Path
								Path TheFilePath(FieldValue.c_str());
								if(!TheFilePath.has_root_path())
								{
									TheFilePath = RootPath / TheFilePath;
								}
								static_cast<SFPath*>(TheField)->setValue(TheFilePath);
							}
							else
							{
								TheField->pushValueByStr(FieldValue.c_str());
							}
						}
						else if(TheField->getCardinality() == FieldType::MULTI_FIELD &&
							!FieldValue.empty())
						{
							std::vector< std::string > SplitVec;
							boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(std::string(";")) );
							for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
							{
								if(TheField->getType() == MFPath::getClassType())
								{
									//If the field type is a Path
									Path TheFilePath(SplitVec[SplitIndex].c_str());
									if(!TheFilePath.has_root_path())
									{
										TheFilePath = RootPath / TheFilePath;
									}
									static_cast<MFPath*>(TheField)->push_back(TheFilePath);
								}
								else
								{
									TheField->pushValueByStr(SplitVec[SplitIndex].c_str());
								}
							}
						}
					}
				}
			}
            changedCP(NewFieldContainer, ChangedFields);
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
        NewFCInfo._Ptr = NullFC;
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
			            if(NewFCInfo._Ptr == NullFC)
			            {
				            SWARNING <<
					            "ERROR in XMLFCFileType::read():" <<
					            "could not load type: " << NewFCInfo._Ptr->getType().getCName() <<
					            " from file " <<TheFilePath.string() <<
					            std::endl;
			            }
                        else
                        {
			                FilePathAttachment::setFilePath(AttachmentContainerPtr::dcast(NewFCInfo._Ptr),TheFilePath);
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
        if(NewFCInfo._Ptr == NullFC)
        {
            NewFCInfo._Ptr = FieldContainerFactory::the()->createFieldContainer(std::string(NodeListItor->name(), NodeListItor->name_size()).c_str());
        }

	    if(NewFCInfo._Ptr == NullFC)
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
				    setName(AttachmentContainerPtr::dcast(NewFCInfo._Ptr),std::string(NameAttrib->value(), NameAttrib->value_size()).c_str());
			    }
            }


            //Attach the FieldID mapping to this container
            rapidxml::xml_attribute<char> *FieldContainerIdAttrib(NodeListItor->first_attribute(FieldContainerIDXMLToken.c_str()));
		    if(FieldContainerIdAttrib == NULL)
		    {
			    SFATAL << FileNameOrExtension << ": Couldn't find "+FieldContainerIDXMLToken+" attribute for '" << std::string(NodeListItor->name(), NodeListItor->name_size()) << "'!" << std::endl;
		    }
		    OldFCId = TypeTraits<UInt32>::getFromString(std::string(FieldContainerIdAttrib->value(), FieldContainerIdAttrib->value_size()).c_str());
		    NewFCInfo._NewId = NewFCInfo._Ptr.getFieldContainerId();
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
    Path RootPath = FCFileHandler::the()->getRootFilePath();

	FCPtrStore AllContainers(getAllDependantFCs(Containers, FCPtrStore(), IgnoreTypes));
	OutputStream << "<?xml version=\"1.0\"  encoding=\"utf-8\"?>" << std::endl << std::endl;
	OutputStream << "<" << RootFCXMLToken << ">" << std::endl;

	for(FCPtrStore::const_iterator FCItor(AllContainers.begin()) ; FCItor != AllContainers.end() ; ++FCItor)
	{
		OutputStream << "\t<" << (*FCItor)->getType().getCName() << std::endl;
		OutputStream << "\t\t"+FieldContainerIDXMLToken+"=\"" << TypeTraits<UInt32>::putToString(FieldContainerPtr(*FCItor).getFieldContainerId()) << "\"" << std::endl;

		if((*FCItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
		{
			//Output Name
			const char* Name(osg::getName(AttachmentContainerPtr::dcast(*FCItor)));
			if(Name != NULL)
			{
				OutputStream << "\t\t" + NameAttachmentXMLToken + "=\"" << Name << "\"" << std::endl;
			}

			//Output FilePath
			const Path* FilePath(FilePathAttachment::getFilePath(AttachmentContainerPtr::dcast(*FCItor)));
			if(FilePath != NULL)
			{
				OutputStream << "\t\t" + FileAttachmentXMLToken + "=\"" << FilePath->string() << "\"" << std::endl;
				continue;
			}

            //All of the others
            std::vector<std::string> AttachmentIds;
            AttachmentMap::iterator MapItor(AttachmentContainerPtr::dcast(*FCItor)->getSFAttachments()->getValue().begin());
            AttachmentMap::iterator MapEnd(AttachmentContainerPtr::dcast(*FCItor)->getSFAttachments()->getValue().end());
            for( ; MapItor!=MapEnd  ; ++MapItor)
            {
                if(MapItor->second->getType() != Name::getClassType() &&
                   MapItor->second->getType() != FilePathAttachment::getClassType())
                {
                    AttachmentIds.push_back(TypeTraits<UInt32>::putToString(MapItor->second.getFieldContainerId()));
                }
            }

            if(AttachmentIds.size() > 0)
            {
				OutputStream << "\t\t" + AttachmentsXMLToken + "=\"";
                for( UInt32 i(0)  ; i<AttachmentIds.size()  ; ++i)
                {
                    if(i != 0) { OutputStream << ";"; }
                    OutputStream << AttachmentIds[i];
                }
				OutputStream << "\"" << std::endl;
            }
		}

		//Write all of the Fields
		FieldContainerType& TheFCType((*FCItor)->getType());
		UInt32 NumFields(TheFCType.getNumFieldDescs());
		const FieldDescription* Desc;
		std::string FieldValue("");
		Field* TheField(NULL);
		for(UInt32 i(1) ; i<NumFields+1 ; ++i)
		{
			Desc = TheFCType.getFieldDescription(i);
            if(Desc->getFieldType() == SFAttachmentMap::getClassType())
            {
                continue;
            }
            if(Desc->isInternal())
			{
		        if((*FCItor)->getType().isDerivedFrom(Node::getClassType()) &&
                    Desc == Node::getClassType().getFieldDescription(i))
		        {
                }
                else
                {
				    continue;
                }
			}

			TheField = (*FCItor)->getField(i);
			if(isFieldAFieldContainerPtr(TheField))
			{
				if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
				{
					OutputStream << "\t\t" << Desc->getCName() << "=\"";
					if(static_cast<SFFieldContainerPtr *>(TheField)->getValue() == NullFC ||
						std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<SFFieldContainerPtr *>(TheField)->getValue()->getTypeId()) != IgnoreTypes.end())
					{
						OutputStream << TypeTraits<UInt32>::putToString(0);
					}
					else
					{
						OutputStream << TypeTraits<UInt32>::putToString(static_cast<SFFieldContainerPtr *>(TheField)->getValue().getFieldContainerId());
					}
					OutputStream << "\"" << std::endl;
				}
				else if(TheField->getCardinality() == FieldType::MULTI_FIELD)
				{
						OutputStream << "\t\t" << Desc->getCName() << "=\"" ;
						for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
						{
							if(Index!=0)
							{
								OutputStream << ";";
							}
							if(static_cast<MFFieldContainerPtr *>(TheField)->operator[](Index) == NullFC ||
								std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<MFFieldContainerPtr *>(TheField)->operator[](Index)->getTypeId()) != IgnoreTypes.end())
							{
								OutputStream << TypeTraits<UInt32>::putToString(0);
							}
							else
							{
								OutputStream << TypeTraits<UInt32>::putToString(static_cast<MFFieldContainerPtr *>(TheField)->operator[](Index).getFieldContainerId());
							}
						}
						OutputStream << "\"" << std::endl;
				}
			}
			else if(TheField->getType() == SFPath::getClassType())
			{
				FieldValue.clear();
				//Path RootPath = boost::filesystem::system_complete(RootPath);
				Path FilePath = boost::filesystem::system_complete(static_cast<SFPath*>(TheField)->getValue());
				//Path RelativePath = makeRelative(RootPath, FilePath);
				//FieldValue = RelativePath.string();//TheField->getValueByStr(FieldValue);
				OutputStream << "\t\t" << Desc->getCName() << "=\"" << FilePath  << "\"" << std::endl;
			}
			else if(TheField->getType() == MFPath::getClassType())
			{
				OutputStream << "\t\t" << Desc->getCName() << "=\"" ;
				//Path RootPath = boost::filesystem::system_complete(RootPath);
				Path FilePath;
				//Path RelativePath;
				for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
				{
					FieldValue.clear();
					FilePath = boost::filesystem::system_complete((*static_cast<MFPath*>(TheField))[Index]);
					//RelativePath = makeRelative(RootPath, FilePath);
					FieldValue = FilePath.string();
					if(Index!=0)
					{
						OutputStream << ";";
					}
					OutputStream << FieldValue;
				}
				OutputStream << "\"" << std::endl;
			}
			else
			{
				if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
				{
					FieldValue.clear();
					TheField->getValueByStr(FieldValue);
					boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of(std::string("\"")));
					OutputStream << "\t\t" << Desc->getCName() << "=\"" << FieldValue << "\"" << std::endl;
				}
				else if(TheField->getCardinality() == FieldType::MULTI_FIELD)
				{
					OutputStream << "\t\t" << Desc->getCName() << "=\"" ;
					for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
					{
						FieldValue.clear();
						TheField->getValueByStr(FieldValue, Index);
						boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of(std::string("\"")));
						if(Index!=0)
						{
							OutputStream << ";";
						}
						OutputStream << FieldValue;
					}
					OutputStream << "\"" << std::endl;
				}
			}
		}

		OutputStream << "\t>" << std::endl;
		OutputStream << "\t</" << TheFCType.getCName() << ">" << std::endl;
	}
	OutputStream << "</" << RootFCXMLToken << ">" << std::endl << std::endl;

	return true;
}

bool XMLFCFileType::registerHandler(std::string XMLNodeToken, OpenSGToolboxXMLHandler TheHandler)
{
    if(_HandlerMap.find(XMLNodeToken) == _HandlerMap.end())
    {
        SWARNING << "XMLFCFileType: Could not register XML Handler for XML token " << XMLNodeToken << " because a handler for that token is already registered."  << std::endl;
        return false;
    }
    else if(FieldContainerFactory::the()->findType(XMLNodeToken.c_str()) == NULL)
    {
        SWARNING << "XMLFCFileType: Could not register XML Handler for XML token " << XMLNodeToken << " because that token is already used for reading Field Containers with the same type."  << std::endl;
        return false;
    }
    else
    {
        _HandlerMap[XMLNodeToken] = TheHandler;
        return true;
    }
}
     
bool XMLFCFileType::unregisterHandler(std::string HandlerName)
{
    if(_HandlerMap.find(HandlerName) != _HandlerMap.end())
    {
        _HandlerMap.erase(_HandlerMap.find(HandlerName));
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

XMLFCFileType::XMLFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("xml")), FCFileType::OSG_READ_SUPPORTED | FCFileType::OSG_WRITE_SUPPORTED)
{
}

XMLFCFileType::XMLFCFileType(const XMLFCFileType &obj) : Inherited(obj)
{
}

XMLFCFileType::~XMLFCFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

XMLFCFileType::FCInfoStruct::FCInfoStruct() : _NewId(0),_Ptr(NullFC),_Read(false)
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

