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
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include "Attachments/OSGFilePathAttachment.h"

#include "OSGXMLFCFileType.h"
#include "Util/OSGFieldContainerUtils.h"

#include "Util/OSGFieldContainerUtils.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
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
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

XMLFCFileType *XMLFCFileType::the(void)
{
	return _the;
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
	FCPtrStore Result;

	xmlpp::xmlcontextptr               Context( new xmlpp::xmlcontext );
	xmlpp::xmldocument                 node( Context );
	xmlpp::xmlnodeptr                  nP;
	xmlpp::xmlnodelist::const_iterator nI;
	xmlpp::xmlattributes               attr;
	xmlpp::xmlattributes::iterator     AttributeIterator;

	IDLookupMap TheIDLookupMap;
	FCIdMapper TheFCIdMapper(&TheIDLookupMap);

	try
	{
		FieldContainerPtr NewFieldContainer;
		const FieldDescription* Desc;
		Field* TheField;
		std::string FieldValue;
		IDLookupMap::iterator FCInfoIter;
		UInt32 CurrentFieldContainerOldId;
		xmlpp::xmlattributes::const_iterator SearchItor;
		//while(true)
		//{
			node.get_attrmap().clear();
			node.load( InputStream, Context );

			//Create all of the Fields
			TheIDLookupMap = createFieldContainers(node.get_nodelist().begin(), node.get_nodelist().end(), Context, FileNameOrExtension);
			
			FieldContainerFactory::the()->setMapper(&TheFCIdMapper);

			for(xmlpp::xmlnodelist::iterator NodeListItor(node.get_nodelist().begin()) ; NodeListItor!=node.get_nodelist().end() ; ++NodeListItor)
			{
				attr.clear();
				attr = (*NodeListItor)->get_attrmap();
				
				SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(FieldContainerIDXMLToken));
				if(SearchItor == (*NodeListItor)->get_attrmap().end())
				{
					SFATAL << FileNameOrExtension << ": Couldn't find "+FieldContainerIDXMLToken+" attribute for '" << (*NodeListItor)->get_name() << "'!" << std::endl;
				}
				CurrentFieldContainerOldId = TypeTraits<UInt32>::getFromString(SearchItor->second.c_str());
				FCInfoIter = TheIDLookupMap.find(CurrentFieldContainerOldId);
				if(FCInfoIter == TheIDLookupMap.end())
				{
					SWARNING <<
						"ERROR in XMLFCFileType::read():" <<
						std::endl <<
						"no matching container found for ID " <<
						CurrentFieldContainerOldId <<
						std::endl <<
						"THIS SHOULD NOT HAPPEN!!!" <<
						std::endl;

					continue;
				}

				if(FCInfoIter->second._Read)
				{
					SWARNING <<
						"ERROR in XMLFCFileType::read():" <<
						std::endl <<
						"original ID: " <<
						CurrentFieldContainerOldId <<
						std::endl <<
						"new ID     : " <<
						FCInfoIter->second._NewId <<
						std::endl <<
						"CONTAINER ALREADY WRITTEN! CONTAINER " <<
						"WILL BE OVERWRITTEN!" <<
						std::endl <<
						"THIS SHOULD NOT HAPPEN!!!" <<
						std::endl;
				}
				NewFieldContainer = FCInfoIter->second._Ptr;
				if(NewFieldContainer->getType().isDerivedFrom(AttachmentContainer::getClassType()))
				{
					//Search for File
					SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(FileAttachmentXMLToken));
					if(SearchItor != (*NodeListItor)->get_attrmap().end())
					{
                        continue;
					}
				}

				if(NewFieldContainer != NullFC)
				{
                    BitVector ChangedFields = 0;
					for(AttributeIterator = attr.begin(); AttributeIterator != attr.end(); AttributeIterator++)
					{
						std::string FieldName = AttributeIterator->first;
						if(FieldName.compare(FieldContainerIDXMLToken) == 0 ||
						   FieldName.compare(NameAttachmentXMLToken) == 0 ||
						   FieldName.compare(FileAttachmentXMLToken) == 0)
						{
							continue;
						}
						Desc = NewFieldContainer->getType().findFieldDescription(FieldName.c_str());
						if(Desc == NULL)
						{
							SWARNING <<
								"ERROR in XMLFCFileType::read():" <<
								" There is no Field named: " <<
								FieldName <<
								", for FieldContainers of Type: " <<
								NewFieldContainer->getType().getCName() << std::endl;
						}
						else
						{
							FieldValue = AttributeIterator->second;
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
										        SWARNING <<
											        "ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << FieldValue <<
											        std::endl;
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
										    SWARNING <<
											    "ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << FieldValue <<
											    std::endl;
                                        }
									}

								    static_cast<SFFieldContainerPtr *>(TheField)->setValue(TheFC);
								}
								else if(TheField->getCardinality() == FieldType::MULTI_FIELD &&
									!FieldValue.empty())
								{
								    UInt32 FCId;
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
										            SWARNING <<
											            "ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << FieldValue <<
											            std::endl;
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
										        SWARNING <<
											        "ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << SplitVec[SplitIndex] <<
											        std::endl;
                                            }
									    }

										static_cast<MFFieldContainerPtr *>(TheField)->push_back(TheFC);
									    
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
											TheFilePath = FCFileHandler::the()->getRootFilePath() / TheFilePath;
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
												TheFilePath = FCFileHandler::the()->getRootFilePath() / TheFilePath;
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
					SWARNING << "Could not create FieldContainer of type name " << (*NodeListItor)->get_name() <<
						", because no such Field Container types are registered in the Field Container Factory" << std::endl;
				}
			}
		//}
	}
	catch (xmlpp::xmlerror& e)
	{
		printXMLError(e, Context, FileNameOrExtension);
	}

	FieldContainerFactory::the()->setMapper(NULL);
	return Result;
}

XMLFCFileType::IDLookupMap XMLFCFileType::createFieldContainers(xmlpp::xmlnodelist::iterator Begin, xmlpp::xmlnodelist::iterator End, xmlpp::xmlcontextptr Context,
	                     const std::string& FileNameOrExtension) const
{
	//FieldContainerFactory::TypeIdMap ContainerOldIdMap;
	FCInfoStruct NewFCInfo;
	UInt32 OldFCId;
	IDLookupMap OldToNewFCLookupMap;
	//Create all of the Fields
	try
	{
		for(xmlpp::xmlnodelist::iterator NodeListItor(Begin) ; NodeListItor!=End ; ++NodeListItor)
		{
			NewFCInfo._Ptr = FieldContainerFactory::the()->createFieldContainer((*NodeListItor)->get_name().c_str());
			if(NewFCInfo._Ptr == NullFC)
			{
				SFATAL << FileNameOrExtension << ": Couldn't create unknown FieldContainer with type '" << (*NodeListItor)->get_name() << "'!" << std::endl;
			}
			else
			{
				xmlpp::xmlattributes::const_iterator SearchItor((*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(FieldContainerIDXMLToken)));
				if(SearchItor == (*NodeListItor)->get_attrmap().end())
				{
					SFATAL << FileNameOrExtension << ": Couldn't find "+FieldContainerIDXMLToken+" attribute for '" << (*NodeListItor)->get_name() << "'!" << std::endl;
				}
				OldFCId = TypeTraits<UInt32>::getFromString(SearchItor->second.c_str());
				NewFCInfo._NewId = NewFCInfo._Ptr.getFieldContainerId();
				if(OldToNewFCLookupMap.insert(std::make_pair(OldFCId, NewFCInfo)).second == false)
				{
					SFATAL << FileNameOrExtension << ": ERROR in XMLFCFileType::createFieldContainers()" <<
						std::endl;
				}
                

                if(NewFCInfo._Ptr->getType().isDerivedFrom(AttachmentContainer::getClassType()))
                {
					//Search for name
					SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(NameAttachmentXMLToken));
					if(SearchItor != (*NodeListItor)->get_attrmap().end())
					{
						setName(AttachmentContainerPtr::dcast(NewFCInfo._Ptr),SearchItor->second.c_str());
					}

                    //Search for File
					SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring(FileAttachmentXMLToken));
					if(SearchItor != (*NodeListItor)->get_attrmap().end())
					{
                        Path TheFilePath(SearchItor->second.c_str());
                        if(!TheFilePath.has_root_path())
                        {
                            TheFilePath = FCFileHandler::the()->getRootFilePath() / TheFilePath;
                        }


						FilePathAttachment::setFilePath(AttachmentContainerPtr::dcast(NewFCInfo._Ptr),TheFilePath);

						if(!FilePathAttachment::loadFromFilePath(AttachmentContainerPtr::dcast(NewFCInfo._Ptr)))
						{
							SWARNING <<
								"ERROR in XMLFCFileType::read():" <<
								"could not load type: " << NewFCInfo._Ptr->getType().getCName() <<
								" from file " <<FilePathAttachment::getFilePath(AttachmentContainerPtr::dcast(NewFCInfo._Ptr)) <<
								std::endl;
						}
					}
                }
			}
		}
	}
	catch(xmlpp::xmlerror& e)
	{
		printXMLError(e, Context, FileNameOrExtension);
	}
	return OldToNewFCLookupMap;
}

void XMLFCFileType::printXMLError(const xmlpp::xmlerror& Error, xmlpp::xmlcontextptr Context,
	                     const std::string& FileNameOrExtension) const
{
	xmlpp::xmllocation where( Context->get_location() );
	xmlpp::xmlstring errmsg( Error.get_strerror() );
    
	// print out where the error occured
	SWARNING << FileNameOrExtension << ":" << where.get_line() << " ";
	SWARNING << "at position " << where.get_pos();
	SWARNING << ": error: " << errmsg.c_str();
	SWARNING << std::endl;
    
	// print out line where the error occured
	/*std::ifstream errfile;
	errfile.open(FilePath.file_string().c_str());
	if(errfile)
	{
		int linenr = where.get_line();
		char linebuffer[1024];
		for(int i=0;i<linenr&&!errfile.eof();i++)
		{
			errfile.getline(linebuffer,1024);
		}
        
		int pos = where.get_pos();
        
		if(pos >= 80) 
		{
			pos %= 80;
		}
        
		std::string line( linebuffer + (where.get_pos()-pos) );
		if (line.length()>=79) line.erase(79);
		SWARNING << line.c_str() << std::endl;
		for(int j=2;j<pos;j++)
		{
			SWARNING << ' ';
		}
		SWARNING << '^' << std::endl;
		errfile.close();
	}*/
}

bool XMLFCFileType::write(const FCPtrStore &Containers, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension, const FCTypeVector& IgnoreTypes) const
{

	FCPtrStore AllContainers(getAllDependantFCs(Containers, FCPtrStore(), IgnoreTypes));
	OutputStream << "<?xml version=\"1.0\"?>" << std::endl << std::endl;
	OutputStream << "<OSGFieldContainers>" << std::endl;

	for(FCPtrStore::const_iterator FCItor(AllContainers.begin()) ; FCItor != AllContainers.end() ; ++FCItor)
	{
		OutputStream << "\t<" << (*FCItor)->getType().getCName() << std::endl;
		OutputStream << "\t\t"+FieldContainerIDXMLToken+"=\"" << TypeTraits<UInt32>::putToString(FieldContainerPtr(*FCItor).getFieldContainerId()) << "\"" << std::endl;

		if((*FCItor)->getType().isDerivedFrom(AttachmentContainer::getClassType()))
		{
			//Output Name
			const Char8* Name(osg::getName(AttachmentContainerPtr::dcast(*FCItor)));
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
				Path RootPath = boost::filesystem::system_complete(FCFileHandler::the()->getRootFilePath());
				Path FilePath = boost::filesystem::system_complete(static_cast<SFPath*>(TheField)->getValue());
				Path RelativePath = makeRelative(RootPath, FilePath);
				FieldValue = RelativePath.string();//TheField->getValueByStr(FieldValue);
				OutputStream << "\t\t" << Desc->getCName() << "=\"" << FieldValue << "\"" << std::endl;
			}
			else if(TheField->getType() == MFPath::getClassType())
			{
				OutputStream << "\t\t" << Desc->getCName() << "=\"" ;
				Path RootPath = boost::filesystem::system_complete(FCFileHandler::the()->getRootFilePath());
				Path FilePath;
				Path RelativePath;
				for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
				{
					FieldValue.clear();
					FilePath = boost::filesystem::system_complete((*static_cast<MFPath*>(TheField))[Index]);
					RelativePath = makeRelative(RootPath, FilePath);
					FieldValue = RelativePath.string();
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
	OutputStream << "</OSGFieldContainers>" << std::endl << std::endl;

	return true;
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

