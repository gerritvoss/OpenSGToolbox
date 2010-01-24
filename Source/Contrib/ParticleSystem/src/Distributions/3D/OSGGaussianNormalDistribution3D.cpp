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

#include "OSGGaussianNormalDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGaussianNormalDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGGaussianNormalDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GaussianNormalDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f GaussianNormalDistribution3D::generate(void) const
{
    //Use the Box-Muller method for generating 3 normally distributed values
    Real32 X(osgSqrt(-2.0f * osgLog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgCos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationX() + getMean().x());

    Real32 Y(osgSqrt(-2.0f * osgLog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgCos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationY() + getMean().y());
    
    Real32 Z(osgSqrt(-2.0f * osgLog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgCos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationZ() + getMean().z());
    
    return Vec3f(X, Y,Z);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GaussianNormalDistribution3D::GaussianNormalDistribution3D(void) :
    Inherited()
{
}

GaussianNormalDistribution3D::GaussianNormalDistribution3D(const GaussianNormalDistribution3D &source) :
    Inherited(source)
{
}

GaussianNormalDistribution3D::~GaussianNormalDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GaussianNormalDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GaussianNormalDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GaussianNormalDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE
