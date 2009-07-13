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

#include "OSGPerlinNoiseDistribution1D.h"
#include <OpenSG/Toolbox/OSGPerlinNoise.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PerlinNoiseDistribution1D
An SegmentSetDistribution1D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution1D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


FunctionIOTypeVector PerlinNoiseDistribution1D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector PerlinNoiseDistribution1D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    InputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE_DIST_INPUTPARAMETERS));
    return InputTypes;
}

FunctionIOParameterVector PerlinNoiseDistribution1D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_PERLINNOISE_DIST_OUTPUTPARAMETERS, generate(dynamic_cast<const FunctionIOData<Real32>* >(InputParameters[0].getDataPtr())->getData())));

    return ResultVector;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
Real32 PerlinNoiseDistribution1D::generate(Real32 t) const
{
	return calcPerlinNoise(t,getAmplitude(),getFrequency(),getPhase(),getPersistance(),getOctaves(),getInterpolationType(),getUseSmoothing());
}

/*----------------------- constructors & destructors ----------------------*/

PerlinNoiseDistribution1D::PerlinNoiseDistribution1D(void) :
    Inherited()
{
}

PerlinNoiseDistribution1D::PerlinNoiseDistribution1D(const PerlinNoiseDistribution1D &source) :
    Inherited(source)
{
}

PerlinNoiseDistribution1D::~PerlinNoiseDistribution1D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerlinNoiseDistribution1D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PerlinNoiseDistribution1D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution1D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPERLINNOISEDISTRIBUTION1DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPERLINNOISEDISTRIBUTION1DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPERLINNOISEDISTRIBUTION1DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

