/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGDistanceFadeParticleAffector.h"
#include "OSGInterpolations.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDistanceFadeParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGDistanceFadeParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceFadeParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DistanceFadeParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement)
{
    Real32 Alpha(0.0f);
    Real32 DistanceSqrd(Displacement.squareLength());
    if(DistanceSqrd >= getDistanceFadeStart()*getDistanceFadeStart())
    {
        if(DistanceSqrd >= getDistanceFadeEnd()*getDistanceFadeEnd())
        {
            Alpha = getFadeEndAlpha();
        }
        else
        {
            lerp<Real32>(getFadeStartAlpha(),getFadeEndAlpha(),(osgSqrt(DistanceSqrd) - getDistanceFadeStart())/(getDistanceFadeEnd() - getDistanceFadeStart()), Alpha);
        }
    }
    else
    {
        Alpha = getFadeStartAlpha();
    }
    Color4f Color = System->getColor(ParticleIndex);
    Color[3] = Alpha;
    System->setColor(Color, ParticleIndex);

    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceFadeParticleAffector::DistanceFadeParticleAffector(void) :
    Inherited()
{
}

DistanceFadeParticleAffector::DistanceFadeParticleAffector(const DistanceFadeParticleAffector &source) :
    Inherited(source)
{
}

DistanceFadeParticleAffector::~DistanceFadeParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceFadeParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DistanceFadeParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DistanceFadeParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
