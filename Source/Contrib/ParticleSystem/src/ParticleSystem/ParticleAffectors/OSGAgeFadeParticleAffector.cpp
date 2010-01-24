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

#include "OSGAgeFadeParticleAffector.h"
#include "OSGInterpolations.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAgeFadeParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGAgeFadeParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AgeFadeParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AgeFadeParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
	Real32 Alpha(0.0f);
	if(System->getAge(ParticleIndex)<getFadeInTime())
	{
		lerp<Real32>(getStartAlpha(), getFadeToAlpha(),1.0f-((getFadeInTime() - System->getAge(ParticleIndex))/getFadeInTime()), Alpha); 
	}
	else if(System->getLifespan(ParticleIndex) < 0 || (System->getAge(ParticleIndex)< System->getLifespan(ParticleIndex)-getFadeOutTime()))
	{
		Alpha = getFadeToAlpha();
	}
	else
	{
		//lerp
		lerp<Real32>(getFadeToAlpha(), getEndAlpha(), ((System->getAge(ParticleIndex)-System->getLifespan(ParticleIndex)+getFadeOutTime())/(getFadeOutTime())), Alpha);
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

AgeFadeParticleAffector::AgeFadeParticleAffector(void) :
    Inherited()
{
}

AgeFadeParticleAffector::AgeFadeParticleAffector(const AgeFadeParticleAffector &source) :
    Inherited(source)
{
}

AgeFadeParticleAffector::~AgeFadeParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AgeFadeParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AgeFadeParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AgeFadeParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
