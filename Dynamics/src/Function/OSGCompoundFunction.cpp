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

#include "OSGCompoundFunction.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CompoundFunction
A Compound Function. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CompoundFunction::FunctionIOTypeVector CompoundFunction::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes(InputTypes);
	for(UInt32 i(0) ; i<getFunctions().size() ; ++i)
	{
		OutputTypes = getFunctions().getValue(i)->getOutputTypes(OutputTypes);
	}
    return OutputTypes;
}

CompoundFunction::FunctionIOTypeVector CompoundFunction::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes(OutputTypes);
	for(UInt32 i(0) ; i<getFunctions().size() ; ++i)
	{
		InputTypes = getFunctions().getValue(i)->getInputTypes(InputTypes);
	}
    return InputTypes;
}

CompoundFunction::FunctionIOParameterVector CompoundFunction::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector(InputParameters);

	for(UInt32 i(0) ; i<getFunctions().size() ; ++i)
	{
		ResultVector = getFunctions().getValue(i)->evaluate(ResultVector);
	}

    return ResultVector;
}
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CompoundFunction::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CompoundFunction::CompoundFunction(void) :
    Inherited()
{
}

CompoundFunction::CompoundFunction(const CompoundFunction &source) :
    Inherited(source)
{
}

CompoundFunction::~CompoundFunction(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CompoundFunction::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CompoundFunction::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CompoundFunction NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOMPOUNDFUNCTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPOUNDFUNCTIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPOUNDFUNCTIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

