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

#include "OSGBooleanFunction.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BooleanFunction
A Boolean Function. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BooleanFunction::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector BooleanFunction::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
	if(getOperation() == BOOLEAN_NOT)
	{
		for(UInt32 i(0) ; i<InputTypes.size() ; ++i)
		{
			OutputTypes.push_back(FunctionIOType(std::string("Value"), TypeFactory::the()->findType("bool")));
		}
	}
	else
	{
		OutputTypes.push_back(FunctionIOType(std::string("Value"), TypeFactory::the()->findType("bool")));
	}
    return OutputTypes;
}

FunctionIOTypeVector BooleanFunction::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
	if(getOperation() == BOOLEAN_NOT)
	{
		InputTypes.push_back(FunctionIOType(std::string("Value"), TypeFactory::the()->findType("bool")));
	}
	else
	{
		InputTypes.push_back(FunctionIOType(std::string("Value"), TypeFactory::the()->findType("bool")));
		InputTypes.push_back(FunctionIOType(std::string("Value"), TypeFactory::the()->findType("bool")));
	}
    return InputTypes;
}

FunctionIOParameterVector BooleanFunction::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    FunctionIOParameterVector ResultVector;

	bool Result;
	switch(getOperation())
	{
	case BOOLEAN_NOT:
		{
			for(UInt32 i(0) ; i<InputParameters.size() ; ++i)
			{
				Result = ! dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData();
				ResultVector.push_back(FunctionIOParameter(std::string("Value"),
					new FunctionIOData<bool>(Result)));
			}
			break;
		}
	case BOOLEAN_AND:
		{
			if(InputParameters.size() <= 1) { throw FunctionInputException(); }
			Result = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[0].getDataPtr())->getData();
			for(UInt32 i(1) ; i<InputParameters.size() ; ++i )
			{
				Result = Result && dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData();
			}
			ResultVector.push_back(FunctionIOParameter(std::string("Value"),
				new FunctionIOData<bool>(Result)));
			break;
		}
	case BOOLEAN_OR:
		{
			if(InputParameters.size() <= 1) { throw FunctionInputException(); }
			Result = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[0].getDataPtr())->getData();
			for(UInt32 i(1) ; i<InputParameters.size() ; ++i )
			{
				Result = Result || dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData();
			}
			ResultVector.push_back(FunctionIOParameter(std::string("Value"),
				new FunctionIOData<bool>(Result)));
			break;
		}
		break;
	case BOOLEAN_XOR:
		{
			if(InputParameters.size() <= 1) { throw FunctionInputException(); }
			Result = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[0].getDataPtr())->getData();
			bool RightValue;
			for(UInt32 i(1) ; i<InputParameters.size() ; ++i )
			{
				
				RightValue = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData();
				Result = (Result || RightValue) && !(Result && RightValue); 
			}
			ResultVector.push_back(FunctionIOParameter(std::string("Value"),
				new FunctionIOData<bool>(Result)));
			break;
		}
		break;
	case BOOLEAN_NAND:
		{
			if(InputParameters.size() <= 1) { throw FunctionInputException(); }
			Result = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[0].getDataPtr())->getData();
			for(UInt32 i(1) ; i<InputParameters.size() ; ++i )
			{
				Result = ! (Result && dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData() );
			}
			ResultVector.push_back(FunctionIOParameter(std::string("Value"),
				new FunctionIOData<bool>(Result)));
			break;
		}
		break;
	case BOOLEAN_NOR:
		{
			if(InputParameters.size() <= 1) { throw FunctionInputException(); }
			Result = dynamic_cast<const FunctionIOData<bool>* >(InputParameters[0].getDataPtr())->getData();
			for(UInt32 i(1) ; i<InputParameters.size() ; ++i )
			{
				Result = ! (Result || dynamic_cast<const FunctionIOData<bool>* >(InputParameters[i].getDataPtr())->getData() );
			}
			ResultVector.push_back(FunctionIOParameter(std::string("Value"),
				new FunctionIOData<bool>(Result)));
			break;
		}
		break;
	default:
		throw FunctionInputException();
		break;
	}
	

    return ResultVector;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BooleanFunction::BooleanFunction(void) :
    Inherited()
{
}

BooleanFunction::BooleanFunction(const BooleanFunction &source) :
    Inherited(source)
{
}

BooleanFunction::~BooleanFunction(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BooleanFunction::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BooleanFunction::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BooleanFunction NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBOOLEANFUNCTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBOOLEANFUNCTIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBOOLEANFUNCTIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

