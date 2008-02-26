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

#include "OSGXMLFCFileType.h"
#include "OSGFCFileHandler.h"

//This is needed so that the Shared Ptr included in the OSG library is not used
//because it is already defined in the boost library
#define BOOST_SMART_PTR_HPP
#include <OpenSG/OSGXmlpp.h>

#include <boost/algorithm/string.hpp>

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
	                     const std::string& fileNameOrExtension) const
{
	FCPtrStore Result;

	int nodeCount;
	xmlpp::xmlcontextptr               context( new xmlpp::xmlcontext );
	xmlpp::xmldocument                 node( context );
	xmlpp::xmlnodeptr                  nP;
	xmlpp::xmlnodelist::const_iterator nI;
	xmlpp::xmlattributes               attr;
	xmlpp::xmlattributes::iterator     AttributeIterator;

	try
	{
		FieldContainerPtr NewFieldContainer;
		const FieldDescription* Desc;
		std::string FieldValue;
		while(true)
		{
			node.get_attrmap().clear();
			node.load( InputStream, context );
			attr = node.get_attrmap();

			NewFieldContainer = FieldContainerFactory::the()->createFieldContainer(node.get_name().c_str());
			if(NewFieldContainer != NullFC)
			{
				for(AttributeIterator = attr.begin(); AttributeIterator != attr.end(); AttributeIterator++)
				{
					Desc = NewFieldContainer->getType().findFieldDescription(AttributeIterator->first.c_str());
					if(Desc != NULL)
					{
						FieldValue = AttributeIterator->second;
						if(NewFieldContainer->getField(Desc->getFieldId())->getCardinality() == FieldType::SINGLE_FIELD)
						{
							NewFieldContainer->getField(Desc->getFieldId())->pushValueByStr(FieldValue.c_str());
						}
						else if(NewFieldContainer->getField(Desc->getFieldId())->getCardinality() == FieldType::MULTI_FIELD &&
							!FieldValue.empty())
						{
							std::vector< std::string > SplitVec;
							boost::algorithm::split( SplitVec, FieldValue, boost::algorithm::is_any_of(";") );
							for(UInt32 SplitIndex(0); SplitIndex<SplitVec.size() ; ++SplitIndex)
							{
								NewFieldContainer->getField(Desc->getFieldId())->pushValueByStr(SplitVec[SplitIndex].c_str());
							}
						}
					}
				}
				Result.insert(NewFieldContainer);
			}
			else
			{
				SWARNING << "Could not create FieldContainer of type name " << node.get_name() <<
					", because no such Field Container types are registered in the Field Container Factory" << std::endl;
			}
		}
	}
	catch (xmlpp::xmlerror& e)
	{
		xmlpp::xmllocation where( context->get_location() );
		xmlpp::xmlstring errmsg( e.get_strerror() );
        
		// print out where the error occured
		SWARNING << fileNameOrExtension << ":" << where.get_line() << " ";
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

	return Result;
}

 bool XMLFCFileType::write(const FCPtrStore &Containers, std::ostream &OutputStream,
                    const std::string& fileNameOrExtension) const
 {

	OutputStream << "<?xml version=\"1.0\"?>" << std::endl << std::endl;

	for(FCPtrStore::const_iterator FCItor(Containers.begin()) ; FCItor != Containers.end() ; ++FCItor)
	{
		OutputStream << "<" << (*FCItor)->getType().getCName() << std::endl;

		//Write all of the Fields
		FieldContainerType& TheFCType((*FCItor)->getType());
		UInt32 NumFields(TheFCType.getNumFieldDescs());
		const FieldDescription* Desc;
		std::string FieldValue("");
		for(UInt32 i(1) ; i<NumFields+1 ; ++i)
		{
			Desc = TheFCType.getFieldDescription(i);
			if((*FCItor)->getField(i)->getCardinality() == FieldType::SINGLE_FIELD)
			{
				FieldValue.clear();
				(*FCItor)->getField(i)->getValueByStr(FieldValue);
				boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of("\""));
				OutputStream << "\t" << Desc->getCName() << "=\"" << FieldValue << "\"" << std::endl;
			}
			else if((*FCItor)->getField(i)->getCardinality() == FieldType::MULTI_FIELD)
			{
				OutputStream << "\t" << Desc->getCName() << "=\"" ;
				for(UInt32 Index(0) ; Index<(*FCItor)->getField(i)->getSize() ; ++Index)
				{
					FieldValue.clear();
					(*FCItor)->getField(i)->getValueByStr(FieldValue, Index);
					boost::algorithm::trim_if(FieldValue, boost::algorithm::is_any_of("\""));
					if(Index!=0)
					{
						OutputStream << " ; ";
					}
					OutputStream << FieldValue;
				}
				OutputStream << "\"" << std::endl;
			}
		}

		OutputStream << ">" << std::endl;
		OutputStream << "</" << TheFCType.getCName() << ">" << std::endl;
	}

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

OSG_END_NAMESPACE

