/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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

#include "OSGRandomMovementParticleAffector.h"

#include <OpenSG/Toolbox/OSGRandomPoolManager.h>
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RandomMovementParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RandomMovementParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RandomMovementParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	Vec3f RandVec(RandomPoolManager::getRandomReal32(-1.0,1.0),RandomPoolManager::getRandomReal32(-1.0,1.0),RandomPoolManager::getRandomReal32(-1.0,1.0));
	RandVec.normalize();
	switch(getAttributeAffected())
	{
	case ACCELERATION_ATTRIBUTE:
		if(getSmooth())
		{
			System->setAcceleration(System->getAcceleration(ParticleIndex) + ( RandVec *getMagnitude() * elps),ParticleIndex);
		}
		else
		{
			System->setAcceleration(RandVec *getMagnitude(),ParticleIndex);
		}
		break;
	case VELOCITY_ATTRIBUTE:
		if(getSmooth())
		{
			System->setVelocity(System->getVelocity(ParticleIndex) + ( RandVec *getMagnitude() * elps),ParticleIndex);
		}
		else
		{
			System->setVelocity(RandVec *getMagnitude(),ParticleIndex);
		}
		break;
	case POSITION_ATTRIBUTE:
	default:
		if(getSmooth())
		{
			System->setPosition(System->getPosition(ParticleIndex) + ( RandVec *getMagnitude() * elps),ParticleIndex);
		}
		else
		{
			System->setPosition(Pnt3f(RandVec *getMagnitude()),ParticleIndex);
		}
		break;
	}
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RandomMovementParticleAffector::RandomMovementParticleAffector(void) :
    Inherited()
{
}

RandomMovementParticleAffector::RandomMovementParticleAffector(const RandomMovementParticleAffector &source) :
    Inherited(source)
{
}

RandomMovementParticleAffector::~RandomMovementParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RandomMovementParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RandomMovementParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RandomMovementParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGRANDOMMOVEMENTPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRANDOMMOVEMENTPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRANDOMMOVEMENTPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

