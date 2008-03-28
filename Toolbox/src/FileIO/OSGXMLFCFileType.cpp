/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include <OpenSG/OSGSFFieldContainerPtr.h>
#include <OpenSG/OSGMFFieldContainerPtr.h>

#include "OSGXMLFCFileType.h"


#include <boost/algorithm/string.hpp>
#include <algorithm>

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
		while(true)
		{
			node.get_attrmap().clear();
			node.load( InputStream, Context );

			//Create all of the Fields
			TheIDLookupMap = createFieldContainers(node.get_nodelist().begin(), node.get_nodelist().end(), Context, FileNameOrExtension);
			
			FieldContainerFactory::the()->setMapper(&TheFCIdMapper);

			for(xmlpp::xmlnodelist::iterator NodeListItor(node.get_nodelist().begin()) ; NodeListItor!=node.get_nodelist().end() ; ++NodeListItor)
			{
				attr.clear();
				attr = (*NodeListItor)->get_attrmap();
				
				SearchItor = (*NodeListItor)->get_attrmap().find(xmlpp::xmlstring("fieldcontainerid"));
				if(SearchItor == (*NodeListItor)->get_attrmap().end())
				{
					SFATAL << FileNameOrExtension << ": Couldn't find fieldcontainerid attribute for '" << (*NodeListItor)->get_name() << "'!" << std::endl;
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
				if(NewFieldContainer != NullFC)
				{
					for(AttributeIterator = attr.begin(); AttributeIterator != attr.end(); AttributeIterator++)
					{
						Desc = NewFieldContainer->getType().findFieldDescription(AttributeIterator->first.c_str());
						if(Desc != NULL)
						{
							FieldValue = AttributeIterator->second;
							TheField = NewFieldContainer->getField(Desc->getFieldId());
							if(isFieldAFieldContainerPtr(TheField))
							{
								UInt32 FCId;
								IDLookupMap::const_iterator FCInfoSearch;
								if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
								{
									FCId = TypeTraits<UInt32>::getFromString(FieldValue.c_str());
									FCInfoSearch = TheIDLookupMap.find(FCId);
									if(FCId == 0)
									{
										static_cast<SFFieldContainerPtr *>(TheField)->setValue(NullFC);
									}
									else if(FCInfoSearch == TheIDLookupMap.end())
									{
										SWARNING <<
											"ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << FCId <<
											std::endl;
										static_cast<SFFieldContainerPtr *>(TheField)->setValue(NullFC);
									}
									else
									{
										static_cast<SFFieldContainerPtr *>(TheField)->setValue(FCInfoSearch->second._Ptr);
									}
								}
								else if(TheField->getCardinality() == FieldType::MULTI_FIELD &&
									!FieldValue.empty())
								{
									std::vector< std::string > SplitVec;
									boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(";") );
									for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
									{
										FCId = TypeTraits<UInt32>::getFromString(SplitVec[SplitIndex].c_str());
										FCInfoSearch = TheIDLookupMap.find(FCId);
										if(FCId == 0)
										{
											static_cast<MFFieldContainerPtr *>(TheField)->push_back(NullFC);
										}
										else if(FCInfoSearch == TheIDLookupMap.end())
										{
											SWARNING <<
												"ERROR in XMLFCFileType::read(): Could not find Container referenced with Id: " << FCId <<
												std::endl;
											static_cast<MFFieldContainerPtr *>(TheField)->push_back(NullFC);
										}
										else
										{
											static_cast<MFFieldContainerPtr *>(TheField)->push_back(FCInfoSearch->second._Ptr);
										}
									}
								}
							}
							else
							{
								if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
								{
									TheField->pushValueByStr(FieldValue.c_str());
								}
								else if(TheField->getCardinality() == FieldType::MULTI_FIELD &&
									!FieldValue.empty())
								{
									std::vector< std::string > SplitVec;
									boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(";") );
									for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
									{
										TheField->pushValueByStr(SplitVec[SplitIndex].c_str());
									}
								}
							}
						}
					}
					Result.insert(NewFieldContainer);
					FCInfoIter->second._Read = true;
				}
				else
				{
					SWARNING << "Could not create FieldContainer of type name " << (*NodeListItor)->get_name() <<
						", because no such Field Container types are registered in the Field Container Factory" << std::endl;
				}
			}
		}
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
				xmlpp::xmlattributes::const_iterator SearchItor((*NodeListItor)->get_attrmap().find(xmlpp::xmlstring("fieldcontainerid")));
				if(SearchItor == (*NodeListItor)->get_attrmap().end())
				{
					SFATAL << FileNameOrExtension << ": Couldn't find fieldcontainerid attribute for '" << (*NodeListItor)->get_name() << "'!" << std::endl;
				}
				OldFCId = TypeTraits<UInt32>::getFromString(SearchItor->second.c_str());
				NewFCInfo._NewId = NewFCInfo._Ptr.getFieldContainerId();
				if(OldToNewFCLookupMap.insert(std::make_pair(OldFCId, NewFCInfo)).second == false)
				{
					SFATAL << FileNameOrExtension << ": ERROR in XMLFCFileType::createFieldContainers()" <<
						std::endl;
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
		OutputStream << "\t\tfieldcontainerid=\"" << TypeTraits<UInt32>::putToString(FieldContainerPtr(*FCItor).getFieldContainerId()) << "\"" << std::endl;

		//Write all of the Fields
		FieldContainerType& TheFCType((*FCItor)->getType());
		UInt32 NumFields(TheFCType.getNumFieldDescs());
		const FieldDescription* Desc;
		std::string FieldValue("");
		Field* TheField(NULL);
		for(UInt32 i(1) ; i<NumFields+1 ; ++i)
		{
			Desc = TheFCType.getFieldDescription(i);
			if(Desc->isInternal())
			{
				continue;
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
			else
			{
				if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
				{
					FieldValue.clear();
					TheField->getValueByStr(FieldValue);
					boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of("\""));
					OutputStream << "\t\t" << Desc->getCName() << "=\"" << FieldValue << "\"" << std::endl;
				}
				else if(TheField->getCardinality() == FieldType::MULTI_FIELD)
				{
					OutputStream << "\t\t" << Desc->getCName() << "=\"" ;
					for(UInt32 Index(0) ; Index<TheField->getSize() ; ++Index)
					{
						FieldValue.clear();
						TheField->getValueByStr(FieldValue, Index);
						boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of("\""));
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

XMLFCFileType::FCPtrStore XMLFCFileType::getAllDependantFCs(FCPtrStore Containers, FCPtrStore IgnoreContainers, const FCTypeVector& IgnoreTypes) const
{
	FCPtrStore AllContainers(Containers);
	FCPtrStore NewIgnores(IgnoreContainers);

	UInt32 NumFields;
	const FieldDescription* TheFieldDesc(NULL);
	Field* TheField(NULL);

	//Loop through all of the given containers
	FCPtrStore ContainersDifference;
	std::set_difference(AllContainers.begin(),AllContainers.end(), IgnoreContainers.begin(), IgnoreContainers.end(), std::inserter(ContainersDifference, ContainersDifference.begin()));
	for(FCPtrStore::iterator ContainersItor(ContainersDifference.begin()) ; ContainersItor != ContainersDifference.end() ; ++ContainersItor)
	{
		if(std::find(IgnoreTypes.begin(), IgnoreTypes.end(), (*ContainersItor)->getType().getId()) != IgnoreTypes.end())
		{
			continue;
		}

		//Loop through all of the fields of the Container
		NumFields = (*ContainersItor)->getType().getNumFieldDescs();
		for(UInt32 i(1) ; i<NumFields+1 ; ++i)
		{
			TheFieldDesc = (*ContainersItor)->getType().getFieldDescription(i);
			TheField = (*ContainersItor)->getField(TheFieldDesc->getFieldId());

			if(!TheFieldDesc->isInternal())
			{
				//Determine if the Field is a Field Container Ptr
				if(isFieldAFieldContainerPtr(TheField))
				{
					//Determine the cardinality of the field
					if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
					{
						//If the Ptr is NOT NullFC and is NOT in the Containers already
						if(static_cast<SFFieldContainerPtr *>(TheField)->getValue() != NullFC &&
							AllContainers.find(static_cast<SFFieldContainerPtr *>(TheField)->getValue()) == AllContainers.end() &&
							IgnoreContainers.find(static_cast<SFFieldContainerPtr *>(TheField)->getValue()) == IgnoreContainers.end() && 
							std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<SFFieldContainerPtr *>(TheField)->getValue()->getTypeId()) == IgnoreTypes.end())
						{
							FCPtrStore TheContainer;
							
							TheContainer.insert(static_cast<SFFieldContainerPtr *>(TheField)->getValue());
							FCPtrStore NewContainers(getAllDependantFCs(TheContainer, AllContainers, IgnoreTypes));

							AllContainers.insert(NewContainers.begin(), NewContainers.end());
							IgnoreContainers.insert(NewContainers.begin(), NewContainers.end());
						}
					}
					else
					{
						for(UInt32 i(0) ; i<TheField->getSize() ; ++i)
						{
							if(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i) != NullFC &&
								AllContainers.find(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)) == AllContainers.end() &&
								IgnoreContainers.find(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)) == IgnoreContainers.end() && 
								std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<MFFieldContainerPtr *>(TheField)->operator[](i)->getTypeId()) == IgnoreTypes.end())
							{
								FCPtrStore TheContainer;
								TheContainer.insert(static_cast<MFFieldContainerPtr *>(TheField)->operator[](i));
								FCPtrStore NewContainers(getAllDependantFCs(TheContainer, AllContainers, IgnoreTypes));

								AllContainers.insert(NewContainers.begin(), NewContainers.end());
								IgnoreContainers.insert(NewContainers.begin(), NewContainers.end());
							}
						}
					}
				}
			}
		}
	}

	return AllContainers;
}

bool XMLFCFileType::isFieldAFieldContainerPtr(const Field* TheField) const
{
	if(TheField != NULL)
	{
		std::string TypeName(TheField->getType().getCName());
		return TypeName.size() >= 3 && TypeName.substr(TypeName.size()-3,3).compare("Ptr") == 0;
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

