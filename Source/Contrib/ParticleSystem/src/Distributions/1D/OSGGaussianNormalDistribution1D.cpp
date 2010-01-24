/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGRandomPoolManager.h"
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGaussianNormalDistribution1DBase.cpp file.
// To modify it, please change the .fcd file (OSGGaussianNormalDistribution1D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GaussianNormalDistribution1D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 GaussianNormalDistribution1D::generate(void) const
{
    //Use the Box-Muller method for generating normally distributed values
    return osgSqrt(-2.0f * osgLog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgCos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviation() + getMean();
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

void GaussianNormalDistribution1D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GaussianNormalDistribution1D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GaussianNormalDistribution1D NI" << std::endl;
}

OSG_END_NAMESPACE
