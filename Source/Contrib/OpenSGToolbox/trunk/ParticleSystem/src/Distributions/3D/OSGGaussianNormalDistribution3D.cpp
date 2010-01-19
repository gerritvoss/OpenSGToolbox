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

#include <OpenSG/OSGConfig.h>

#include "OSGGaussianNormalDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GaussianNormalDistribution3D
An GaussianNormalDistribution2D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GaussianNormalDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


Vec3f GaussianNormalDistribution3D::generate(void) const
{
    //Use the Box-Muller method for generating 3 normally distributed values
    Real32 X(osgsqrt(-2.0f * osglog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgcos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationX() + getMean().x());

    Real32 Y(osgsqrt(-2.0f * osglog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgcos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationY() + getMean().y());
    
    Real32 Z(osgsqrt(-2.0f * osglog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))* osgcos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getStandardDeviationZ() + getMean().z());
    
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

void GaussianNormalDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GaussianNormalDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GaussianNormalDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

