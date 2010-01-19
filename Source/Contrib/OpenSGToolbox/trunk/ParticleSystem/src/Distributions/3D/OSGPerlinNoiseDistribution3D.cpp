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

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>

#include "OSGPerlinNoiseDistribution3D.h"
#include <OpenSG/Toolbox/OSGPerlinNoise.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PerlinNoiseDistribution3D
A PerlinNoiseDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution3D::initMethod (void)
{
}

Vec3f PerlinNoiseDistribution3D::generate(void) const
{
    return Vec3f(generate(0.0f),generate(0.0f),generate(0.0f));
}

Real32 PerlinNoiseDistribution3D::generate(Pnt3f t) const
{
	return calcPerlinNoise(t,getAmplitude(),getFrequency(),getPhase(),getPersistance(),getOctaves(),getInterpolationType(),getUseSmoothing());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PerlinNoiseDistribution3D::PerlinNoiseDistribution3D(void) :
    Inherited()
{
}

PerlinNoiseDistribution3D::PerlinNoiseDistribution3D(const PerlinNoiseDistribution3D &source) :
    Inherited(source)
{
}

PerlinNoiseDistribution3D::~PerlinNoiseDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerlinNoiseDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PerlinNoiseDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

