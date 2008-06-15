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

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGGaussianNormalDistribution1D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GaussianNormalDistribution1D
An GaussianNormalDistribution1D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GaussianNormalDistribution1D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector GaussianNormalDistribution1D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_GAUSSIANNORMAL_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector GaussianNormalDistribution1D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector GaussianNormalDistribution1D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_GAUSSIANNORMAL_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_GAUSSIANNORMAL_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_GAUSSIANNORMAL_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Real32 GaussianNormalDistribution1D::generate(void)
{
    //Use the Box-Muller method for generating normally distributed values
    return osgsqrt(-2.0f * osglog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgcos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviation() + getMean();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GaussianNormalDistribution1D::GaussianNormalDistribution1D(void) :
    Inherited()
{
}

GaussianNormalDistribution1D::GaussianNormalDistribution1D(const GaussianNormalDistribution1D &source) :
    Inherited(source)
{
}

GaussianNormalDistribution1D::~GaussianNormalDistribution1D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GaussianNormalDistribution1D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GaussianNormalDistribution1D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GaussianNormalDistribution1D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGAUSSIANNORMALDISTRIBUTION1DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGAUSSIANNORMALDISTRIBUTION1DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGAUSSIANNORMALDISTRIBUTION1DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

