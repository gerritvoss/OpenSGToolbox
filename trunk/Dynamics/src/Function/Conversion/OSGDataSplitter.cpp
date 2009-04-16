/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGMFSysTypes.h>

#include "OSGDataSplitter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DataSplitter
A Data Splitter. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DataSplitter::initMethod (void)
{
}

void DataSplitter::addSplitOutputTypes(FunctionIOTypeVector& OutputTypes, const FunctionIOType& InputType)
{
	UInt32 TypeId(InputType.getType()->getId());

	if(TypeId == FieldDataTraits<Real32>::getType().getId())
	{
		//1 Real32
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == SFReal32::getClassType().getId())
	{
		//1 Real32
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Vec2f>::getType().getId())
	{
		//2 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Pnt2f>::getType().getId())
	{
		//2 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Vec3f>::getType().getId())
	{
		//3 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Pnt3f>::getType().getId())
	{
		//3 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Color3f>::getType().getId())
	{
		//3 Real32
		OutputTypes.push_back(FunctionIOType(std::string("r"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("g"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("b"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Vec4f>::getType().getId())
	{
		//4 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Pnt4f>::getType().getId())
	{
		//4 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Color4f>::getType().getId())
	{
		//4 Real32
		OutputTypes.push_back(FunctionIOType(std::string("r"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("g"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("b"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("a"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Quaternion>::getType().getId())
	{
		//4 Real32
		OutputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(TypeId == FieldDataTraits<Matrix>::getType().getId())
	{
		//16 Real32
		OutputTypes.push_back(FunctionIOType(std::string("00"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("01"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("02"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("03"), &FieldDataTraits<Real32>::getType()));
		
		OutputTypes.push_back(FunctionIOType(std::string("10"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("11"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("12"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("13"), &FieldDataTraits<Real32>::getType()));
		
		OutputTypes.push_back(FunctionIOType(std::string("20"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("21"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("22"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("23"), &FieldDataTraits<Real32>::getType()));
		
		OutputTypes.push_back(FunctionIOType(std::string("30"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("31"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("32"), &FieldDataTraits<Real32>::getType()));
		OutputTypes.push_back(FunctionIOType(std::string("33"), &FieldDataTraits<Real32>::getType()));
	}
	else if (TypeId == MFReal32::getClassType().getId())
	{
		//n Real32
	}

	//TODO: Implement
	//1 UInt8 SFUInt8
	//2 UInt8
	//3 UInt8
	//4 UInt8

	//1 Int8 SFInt8
	//2 Int8
	//3 Int8
	//4 Int8
	
	//1 UInt16 SFInt16
	//2 UInt16
	//3 UInt16
	//4 UInt16
	
	//1 Int16 SFInt16
	//2 Int16
	//3 Int16
	//4 Int16
	
	//1 Real64 Time SFReal64
	//2 Real64
	//3 Real64
	//4 Real64
	
	//1 Real128 SFReal128
	//2 Real128
	//3 Real128
	//4 Real128
	
	//1 Int32 SFInt32
	//1 UInt32
	//1 Int64
	//1 UInt64

	//MFInt8
	//MFUInt8
	//MFInt16
	//MFUInt16
	//MFInt32
	//MFUInt32
	//MFInt64
	//MFUInt64
	//MFReal32
	//MFReal64 Time
	//MFReal128

}

void DataSplitter::addSplitOutputData(FunctionIOParameterVector& OutputData, const FunctionIOParameter& InputParameter)
{
	UInt32 TypeId(InputParameter.getDataPtr()->getType()->getId());

	if(TypeId == FieldDataTraits<Real32>::getType().getId())
	{
		//1 Real32
		OutputData.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Real32>* >(InputParameter.getDataPtr())->getData())));
	}
	else if(TypeId == SFReal32::getClassType().getId())
	{
		//1 Real32
		OutputData.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOFieldData<SFReal32>* >(InputParameter.getDataPtr())->getData().getValue())));
	}
	else if(TypeId == FieldDataTraits<Vec2f>::getType().getId())
	{
		//2 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec2f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec2f>* >(InputParameter.getDataPtr())->getData().y())));
	}
	else if(TypeId == FieldDataTraits<Pnt2f>::getType().getId())
	{
		//2 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt2f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt2f>* >(InputParameter.getDataPtr())->getData().y())));
	}
	else if(TypeId == FieldDataTraits<Vec3f>::getType().getId())
	{
		//3 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec3f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec3f>* >(InputParameter.getDataPtr())->getData().y())));
		OutputData.push_back(FunctionIOParameter(std::string("z"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec3f>* >(InputParameter.getDataPtr())->getData().z())));
	}
	else if(TypeId == FieldDataTraits<Pnt3f>::getType().getId())
	{
		//3 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt3f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt3f>* >(InputParameter.getDataPtr())->getData().y())));
		OutputData.push_back(FunctionIOParameter(std::string("z"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt3f>* >(InputParameter.getDataPtr())->getData().z())));
	}
	else if(TypeId == FieldDataTraits<Color3f>::getType().getId())
	{
		//3 Real32
		OutputData.push_back(FunctionIOParameter(std::string("r"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color3f>* >(InputParameter.getDataPtr())->getData().red())));
		OutputData.push_back(FunctionIOParameter(std::string("g"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color3f>* >(InputParameter.getDataPtr())->getData().green())));
		OutputData.push_back(FunctionIOParameter(std::string("b"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color3f>* >(InputParameter.getDataPtr())->getData().blue())));
	}
	else if(TypeId == FieldDataTraits<Vec4f>::getType().getId())
	{
		//4 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec4f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec4f>* >(InputParameter.getDataPtr())->getData().y())));
		OutputData.push_back(FunctionIOParameter(std::string("z"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec4f>* >(InputParameter.getDataPtr())->getData().z())));
		OutputData.push_back(FunctionIOParameter(std::string("w"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Vec4f>* >(InputParameter.getDataPtr())->getData().w())));
	}
	else if(TypeId == FieldDataTraits<Pnt4f>::getType().getId())
	{
		//4 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt4f>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt4f>* >(InputParameter.getDataPtr())->getData().y())));
		OutputData.push_back(FunctionIOParameter(std::string("z"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt4f>* >(InputParameter.getDataPtr())->getData().z())));
		OutputData.push_back(FunctionIOParameter(std::string("w"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Pnt4f>* >(InputParameter.getDataPtr())->getData().w())));
	}
	else if(TypeId == FieldDataTraits<Color4f>::getType().getId())
	{
		//4 Real32
		OutputData.push_back(FunctionIOParameter(std::string("r"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color4f>* >(InputParameter.getDataPtr())->getData().red())));
		OutputData.push_back(FunctionIOParameter(std::string("g"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color4f>* >(InputParameter.getDataPtr())->getData().green())));
		OutputData.push_back(FunctionIOParameter(std::string("b"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color4f>* >(InputParameter.getDataPtr())->getData().blue())));
		OutputData.push_back(FunctionIOParameter(std::string("a"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Color4f>* >(InputParameter.getDataPtr())->getData().alpha())));
	}
	else if(TypeId == FieldDataTraits<Quaternion>::getType().getId())
	{
		//4 Real32
		OutputData.push_back(FunctionIOParameter(std::string("x"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Quaternion>* >(InputParameter.getDataPtr())->getData().x())));
		OutputData.push_back(FunctionIOParameter(std::string("y"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Quaternion>* >(InputParameter.getDataPtr())->getData().y())));
		OutputData.push_back(FunctionIOParameter(std::string("z"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Quaternion>* >(InputParameter.getDataPtr())->getData().z())));
		OutputData.push_back(FunctionIOParameter(std::string("w"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Quaternion>* >(InputParameter.getDataPtr())->getData().w())));
	}
	else if(TypeId == FieldDataTraits<Matrix>::getType().getId())
	{
		//16 Real32
		OutputData.push_back(FunctionIOParameter(std::string("00"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[0][0])));
		OutputData.push_back(FunctionIOParameter(std::string("01"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[0][1])));
		OutputData.push_back(FunctionIOParameter(std::string("02"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[0][2])));
		OutputData.push_back(FunctionIOParameter(std::string("03"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[0][3])));
		
		OutputData.push_back(FunctionIOParameter(std::string("10"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[1][0])));
		OutputData.push_back(FunctionIOParameter(std::string("11"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[1][1])));
		OutputData.push_back(FunctionIOParameter(std::string("12"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[1][2])));
		OutputData.push_back(FunctionIOParameter(std::string("13"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[1][3])));
		
		OutputData.push_back(FunctionIOParameter(std::string("20"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[2][0])));
		OutputData.push_back(FunctionIOParameter(std::string("21"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[2][1])));
		OutputData.push_back(FunctionIOParameter(std::string("22"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[2][2])));
		OutputData.push_back(FunctionIOParameter(std::string("23"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[2][3])));
		
		OutputData.push_back(FunctionIOParameter(std::string("30"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[3][0])));
		OutputData.push_back(FunctionIOParameter(std::string("31"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[3][1])));
		OutputData.push_back(FunctionIOParameter(std::string("32"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[3][2])));
		OutputData.push_back(FunctionIOParameter(std::string("33"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Matrix>* >(InputParameter.getDataPtr())->getData()[3][3])));
		
	}
	else if (TypeId == MFReal32::getClassType().getId())
	{
		//n Real32
	}
	
	//TODO: Implement
	//1 UInt8 SFUInt8
	//2 UInt8
	//3 UInt8
	//4 UInt8

	//1 Int8 SFInt8
	//2 Int8
	//3 Int8
	//4 Int8
	
	//1 UInt16 SFInt16
	//2 UInt16
	//3 UInt16
	//4 UInt16
	
	//1 Int16 SFInt16
	//2 Int16
	//3 Int16
	//4 Int16
	
	//1 Real64 Time SFReal64
	//2 Real64
	//3 Real64
	//4 Real64
	
	//1 Real128 SFReal128
	//2 Real128
	//3 Real128
	//4 Real128
	
	//1 Int32 SFInt32
	//1 UInt32
	//1 Int64
	//1 UInt64

	//MFInt8
	//MFUInt8
	//MFInt16
	//MFUInt16
	//MFInt32
	//MFUInt32
	//MFInt64
	//MFUInt64
	//MFReal32
	//MFReal64 Time
	//MFReal128
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector DataSplitter::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;

	FunctionIOTypeVector::const_iterator InputTypeIter;
	for(InputTypeIter = InputTypes.begin() ; InputTypeIter != InputTypes.end() ; ++InputTypeIter)
	{
		addSplitOutputTypes(OutputTypes, (*InputTypeIter));
	}
    return OutputTypes;
}

FunctionIOTypeVector DataSplitter::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector DataSplitter::evaluate(FunctionIOParameterVector& InputParameters)
{
    FunctionIOParameterVector ResultVector;

	FunctionIOParameterVector::const_iterator InputParameterIter;
	for(InputParameterIter = InputParameters.begin() ; InputParameterIter != InputParameters.end() ; ++InputParameterIter)
	{
		addSplitOutputData(ResultVector, (*InputParameterIter));
	}

    return ResultVector;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DataSplitter::DataSplitter(void) :
    Inherited()
{
}

DataSplitter::DataSplitter(const DataSplitter &source) :
    Inherited(source)
{
}

DataSplitter::~DataSplitter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DataSplitter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DataSplitter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DataSplitter NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDATASPLITTERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDATASPLITTERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDATASPLITTERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

