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

#include "OSGPerlinNoiseDistribution1D.h"
#include "OSGPerlinNoise.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPerlinNoiseDistribution1DBase.cpp file.
// To modify it, please change the .fcd file (OSGPerlinNoiseDistribution1D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution1D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 PerlinNoiseDistribution1D::generate(void) const
{
    //TODO: Define a way to send meaningful data to the parameterize generate method
    return generate(0.0f);
}

Real32 PerlinNoiseDistribution1D::generate(Real32 t) const
{
	return calcPerlinNoise(t,getAmplitude(),getFrequency(),getPhase(),getPersistance(),getOctaves(),getInterpolationType(),getUseSmoothing());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void PerlinNoiseDistribution1D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PerlinNoiseDistribution1D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution1D NI" << std::endl;
}

OSG_END_NAMESPACE
