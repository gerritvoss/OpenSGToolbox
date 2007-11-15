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

#include "OSGDataCombiner.h"
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGMFSysTypes.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DataCombiner
A Data Combiner. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DataCombiner::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


DataCombiner::FunctionIOTypeVector DataCombiner::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;

	if(getToTypeName().compare( FieldDataTraits<Real32>::getType().getCName() ) == 0)
	{
		//Real32
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( SFReal32::getClassType().getCName()) == 0)
	{
		//SFReal32
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &SFReal32::getClassType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec2f>::getType().getCName() ) == 0)
	{
		//Vec2f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Vec2f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt2f>::getType().getCName() ) == 0)
	{
		//Pnt2f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Pnt2f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec3f>::getType().getCName() ) == 0)
	{
		//Vec3f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Vec3f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt3f>::getType().getCName() ) == 0)
	{
		//Pnt3f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Pnt3f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color3f>::getType().getCName() ) == 0)
	{
		//Color3f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Color3f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec4f>::getType().getCName() ) == 0)
	{
		//Vec4f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Vec4f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt4f>::getType().getCName() ) == 0)
	{
		//Pnt4f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Pnt4f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color4f>::getType().getCName() ) == 0)
	{
		//Color4f
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Color4f>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Quaternion>::getType().getCName() ) == 0)
	{
		//Quaternion
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Quaternion>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Matrix>::getType().getCName() ) == 0)
	{
		//Matrix
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Matrix>::getType()));
	}
	else if (getToTypeName().compare( MFReal32::getClassType().getCName()) == 0)
	{
		//MFReal32
		OutputTypes.push_back(FunctionIOType(std::string("Value"), &MFReal32::getClassType()));
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

    return OutputTypes;
}

DataCombiner::FunctionIOTypeVector DataCombiner::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
	
	if(getToTypeName().compare( FieldDataTraits<Real32>::getType().getCName() ) == 0)
	{
		//Real32
		InputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( SFReal32::getClassType().getCName()) == 0)
	{
		//SFReal32
		InputTypes.push_back(FunctionIOType(std::string("Value"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec2f>::getType().getCName() ) == 0)
	{
		//Vec2f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt2f>::getType().getCName() ) == 0)
	{
		//Pnt2f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec3f>::getType().getCName() ) == 0)
	{
		//Vec3f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt3f>::getType().getCName() ) == 0)
	{
		//Pnt3f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color3f>::getType().getCName() ) == 0)
	{
		//Color3f
		InputTypes.push_back(FunctionIOType(std::string("r"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("g"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("b"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec4f>::getType().getCName() ) == 0)
	{
		//Vec4f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt4f>::getType().getCName() ) == 0)
	{
		//Pnt4f
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color4f>::getType().getCName() ) == 0)
	{
		//Color4f
		InputTypes.push_back(FunctionIOType(std::string("r"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("g"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("b"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("a"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Quaternion>::getType().getCName() ) == 0)
	{
		//Quaternion
		InputTypes.push_back(FunctionIOType(std::string("x"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("y"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("z"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("w"), &FieldDataTraits<Real32>::getType()));
	}
	else if(getToTypeName().compare( FieldDataTraits<Matrix>::getType().getCName() ) == 0)
	{
		//Matrix
		InputTypes.push_back(FunctionIOType(std::string("00"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("01"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("02"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("03"), &FieldDataTraits<Real32>::getType()));
		
		InputTypes.push_back(FunctionIOType(std::string("10"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("11"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("12"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("13"), &FieldDataTraits<Real32>::getType()));
		
		InputTypes.push_back(FunctionIOType(std::string("20"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("21"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("22"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("23"), &FieldDataTraits<Real32>::getType()));
		
		InputTypes.push_back(FunctionIOType(std::string("30"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("31"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("32"), &FieldDataTraits<Real32>::getType()));
		InputTypes.push_back(FunctionIOType(std::string("33"), &FieldDataTraits<Real32>::getType()));
	}
	else if (getToTypeName().compare( MFReal32::getClassType().getCName()) == 0)
	{
		//MFReal32
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

    return InputTypes;
}

DataCombiner::FunctionIOParameterVector DataCombiner::evaluate(FunctionIOParameterVector& InputParameters)
{
    FunctionIOParameterVector ResultVector;

	if(getToTypeName().compare( FieldDataTraits<Real32>::getType().getCName() ) == 0)
	{
		//Real32
		if(InputParameters.size() != 1){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Real32>(dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData())));
	}
	else if(getToTypeName().compare( SFReal32::getClassType().getCName()) == 0)
	{
		//SFReal32
		if(InputParameters.size() != 1){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOFieldData<SFReal32>(SFReal32(dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData()))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec2f>::getType().getCName() ) == 0)
	{
		//Vec2f
		if(InputParameters.size() != 2){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Vec2f>(
			Vec2f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt2f>::getType().getCName() ) == 0)
	{
		//Pnt2f
		if(InputParameters.size() != 2){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Pnt2f>(
			Pnt2f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec3f>::getType().getCName() ) == 0)
	{
		//Vec3f
		if(InputParameters.size() != 3){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Vec3f>(
			Vec3f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt3f>::getType().getCName() ) == 0)
	{
		//Pnt3f
		if(InputParameters.size() != 3){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Pnt3f>(
			Pnt3f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color3f>::getType().getCName() ) == 0)
	{
		//Color3f
		if(InputParameters.size() != 3){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Color3f>(
			Color3f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Vec4f>::getType().getCName() ) == 0)
	{
		//Vec4f
		if(InputParameters.size() != 4){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Vec4f>(
			Vec4f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[3].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Pnt4f>::getType().getCName() ) == 0)
	{
		//Pnt4f
		if(InputParameters.size() != 4){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Pnt4f>(
			Pnt4f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[3].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Color4f>::getType().getCName() ) == 0)
	{
		//Color4f
		if(InputParameters.size() != 4){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Color4f>(
			Color4f(   dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[3].getDataPtr())->getData()
			))));
	}
	else if(getToTypeName().compare( FieldDataTraits<Quaternion>::getType().getCName() ) == 0)
	{
		//Quaternion
		if(InputParameters.size() != 4){throw FunctionInputException();}
		Quaternion q;
		q.setValueAsQuat(dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[3].getDataPtr())->getData()
			);
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Quaternion>(q)));
	}
	else if(getToTypeName().compare( FieldDataTraits<Matrix>::getType().getCName() ) == 0)
	{
		//Matrix
		if(InputParameters.size() != 16){throw FunctionInputException();}
		ResultVector.push_back(FunctionIOParameter(std::string("Value"),
			new FunctionIOData<Matrix>(
			Matrix(  dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[1].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[2].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[3].getDataPtr())->getData(),

					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[4].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[5].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[6].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[7].getDataPtr())->getData(),

					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[8].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[9].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[10].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[11].getDataPtr())->getData(),

					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[12].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[13].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[14].getDataPtr())->getData(),
					 dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[15].getDataPtr())->getData()
			))));
	}
	else if (getToTypeName().compare( MFReal32::getClassType().getCName()) == 0)
	{
		//MFReal32
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

    return ResultVector;
}

void DataCombiner::addCombineOutputData(FunctionIOParameterVector& OutputData, const FunctionIOParameterVector& InputParameters)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DataCombiner::DataCombiner(void) :
    Inherited()
{
}

DataCombiner::DataCombiner(const DataCombiner &source) :
    Inherited(source)
{
}

DataCombiner::~DataCombiner(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DataCombiner::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DataCombiner::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DataCombiner NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDATACOMBINERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDATACOMBINERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDATACOMBINERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

