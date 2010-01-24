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

#include "OSGAgeSizeParticleAffector.h"
#include "OSGParticleSystem.h"
#include "OSGInterpolations.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAgeSizeParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGAgeSizeParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AgeSizeParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


bool AgeSizeParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
	if(getMFAges()->size()!=getMFSizes()->size())
	{
		return false;
	}
	else
	{
		Real32 time;
		UInt32 i(0);
        Real32 Age(System->getAge(ParticleIndex)),Lifespan(System->getLifespan(ParticleIndex));
        if(Lifespan < 0.0)
        {
            return false;
        }

		time = (Age)/(Lifespan);
		for( ;i<getMFAges()->size() && time>getAges(i);++i)
		{
			
		}

		if(i == getMFSizes()->size())
		{
			System->setSize(getMFSizes()->back(),ParticleIndex);
		}
		else if(i == 0.0)
		{
			System->setSize(getMFSizes()->front(),ParticleIndex);
		}
		else
		{
			Vec3f size;
            time = (time - getAges(i-1))/(getAges(i)-getAges(i-1));

            lerp(getSizes(i-1),getSizes(i),time,size);
            System->setSize(size,ParticleIndex);
		}


	}
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AgeSizeParticleAffector::AgeSizeParticleAffector(void) :
    Inherited()
{
}

AgeSizeParticleAffector::AgeSizeParticleAffector(const AgeSizeParticleAffector &source) :
    Inherited(source)
{
}

AgeSizeParticleAffector::~AgeSizeParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AgeSizeParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AgeSizeParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AgeSizeParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
