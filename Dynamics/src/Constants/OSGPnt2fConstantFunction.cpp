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

#include "OSGPnt2fConstantFunction.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Pnt2fConstantFunction
An Pnt2fConstantFunction. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Pnt2fConstantFunction::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector Pnt2fConstantFunction::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PNT2F_CONSTANT_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector Pnt2fConstantFunction::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector Pnt2fConstantFunction::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PNT2F_CONSTANT_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PNT2F_CONSTANT_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_PNT2F_CONSTANT_OUTPUTPARAMETERS, getValue()));

    return ResultVector;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Pnt2fConstantFunction::Pnt2fConstantFunction(void) :
    Inherited()
{
}

Pnt2fConstantFunction::Pnt2fConstantFunction(const Pnt2fConstantFunction &source) :
    Inherited(source)
{
}

Pnt2fConstantFunction::~Pnt2fConstantFunction(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Pnt2fConstantFunction::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Pnt2fConstantFunction::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Pnt2fConstantFunction NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPNT2FCONSTANTFUNCTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPNT2FCONSTANTFUNCTIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPNT2FCONSTANTFUNCTIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

