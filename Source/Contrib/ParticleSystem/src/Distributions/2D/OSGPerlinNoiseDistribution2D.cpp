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

#include "OSGPerlinNoiseDistribution2D.h"
#include "OSGPerlinNoise.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPerlinNoiseDistribution2DBase.cpp file.
// To modify it, please change the .fcd file (OSGPerlinNoiseDistribution2D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution2D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f PerlinNoiseDistribution2D::generate(void) const
{
    return Vec2f(generate(0.0f),generate(0.0f));
}

Real32 PerlinNoiseDistribution2D::generate(Pnt2f t) const
{	
	return calcPerlinNoise(t,getAmplitude(),getFrequency(),getPhase(),getPersistance(),getOctaves(),getInterpolationType(),getUseSmoothing());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PerlinNoiseDistribution2D::PerlinNoiseDistribution2D(void) :
    Inherited()
{
}

PerlinNoiseDistribution2D::PerlinNoiseDistribution2D(const PerlinNoiseDistribution2D &source) :
    Inherited(source)
{
}

PerlinNoiseDistribution2D::~PerlinNoiseDistribution2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerlinNoiseDistribution2D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PerlinNoiseDistribution2D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution2D NI" << std::endl;
}

OSG_END_NAMESPACE
