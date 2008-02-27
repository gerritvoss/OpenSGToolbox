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

#include "OSGBinFCFileType.h"


#include <boost/algorithm/string.hpp>
#include <algorithm>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BinFCFileType
A BinFCFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

BinFCFileType*  BinFCFileType::_the(new BinFCFileType());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

BinFCFileType *BinFCFileType::the(void)
{
	return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string BinFCFileType::getName(void) const
{
	return std::string("BinFCFileType");
}

 BinFCFileType::FCPtrStore BinFCFileType::read(std::istream &InputStream,
	                     const std::string& FileNameOrExtension) const
{
	FCPtrStore Result;

	return Result;
}

bool BinFCFileType::write(const FCPtrStore &Containers, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension, const FCTypeVector& IgnoreTypes) const
{

	FCPtrStore AllContainers(getAllDependantFCs(Containers, FCPtrStore(), IgnoreTypes));
	/*OutputStream << "<?bin version=\"1.0\"?>" << std::endl << std::endl;
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
							if(static_cast<MFFieldContainerPtr *>(TheField)->getValue(Index) == NullFC ||
								std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<MFFieldContainerPtr *>(TheField)->getValue(Index)->getTypeId()) != IgnoreTypes.end())
							{
								OutputStream << TypeTraits<UInt32>::putToString(0);
							}
							else
							{
								OutputStream << TypeTraits<UInt32>::putToString(static_cast<MFFieldContainerPtr *>(TheField)->getValue(Index).getFieldContainerId());
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
	OutputStream << "</OSGFieldContainers>" << std::endl << std::endl;*/

	return true;
}

BinFCFileType::FCPtrStore BinFCFileType::getAllDependantFCs(FCPtrStore Containers, FCPtrStore IgnoreContainers, const FCTypeVector& IgnoreTypes) const
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
							if(static_cast<MFFieldContainerPtr *>(TheField)->getValue(i) != NullFC &&
								AllContainers.find(static_cast<MFFieldContainerPtr *>(TheField)->getValue(i)) == AllContainers.end() &&
								IgnoreContainers.find(static_cast<MFFieldContainerPtr *>(TheField)->getValue(i)) == IgnoreContainers.end() && 
								std::find(IgnoreTypes.begin(), IgnoreTypes.end(), static_cast<MFFieldContainerPtr *>(TheField)->getValue(i)->getTypeId()) == IgnoreTypes.end())
							{
								FCPtrStore TheContainer;
								TheContainer.insert(static_cast<MFFieldContainerPtr *>(TheField)->getValue(i));
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

bool BinFCFileType::isFieldAFieldContainerPtr(const Field* TheField) const
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

BinFCFileType::BinFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("bin")), FCFileType::OSG_READ_SUPPORTED | FCFileType::OSG_WRITE_SUPPORTED)
{
}

BinFCFileType::BinFCFileType(const BinFCFileType &obj) : Inherited(obj)
{
}

BinFCFileType::~BinFCFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

BinFCFileType::FCInfoStruct::FCInfoStruct() : _NewId(0),_Ptr(NullFC),_Read(false)
{
}

BinFCFileType::FCIdMapper::FCIdMapper(IDLookupMap *m): _PtrMap(m)
{
}

UInt32 BinFCFileType::FCIdMapper::map(UInt32 uiId)
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

