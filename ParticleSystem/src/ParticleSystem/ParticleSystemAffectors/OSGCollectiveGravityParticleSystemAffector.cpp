/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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

#include "OSGCollectiveGravityParticleSystemAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CollectiveGravityParticleSystemAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollectiveGravityParticleSystemAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CollectiveGravityParticleSystemAffector::affect(ParticleSystemPtr System, const Time& elps)
{
    //TODO: Implement
	Vec3f Force,Ftotal,LineSegment,Acceleration;
	Real32 DistanceSquared;
	Pnt3f CenterMass, TempCenterMass;
	/*for(int i(0); i < System->getNumParticles(); ++i)
	{
		Ftotal.setValues(0.0,0.0,0.0);
		for(int n(0);  n < System->getNumParticles();++n)
		{
			if(i!= n)
			{
				LineSegment = System->getPosition(n) - System->getPosition(i);
				DistanceSquared = System->getPosition(n).dist2(System->getPosition(i));
				if(DistanceSquared > 0)
				{
					Force = (getGravitationalConstant() * getParticleMass() * getParticleMass() * LineSegment)*(1/DistanceSquared);
					Ftotal = Ftotal + Force;
				}
			}
		}
		Acceleration = 1.0f/getParticleMass() * Ftotal;
		System->setAcceleration(Acceleration,i);
	}*/

	//calculate Center Mass of all particles
	for(int i(0); i < System->getNumParticles(); ++i)
	{
		CenterMass = CenterMass + System->getPosition(i);
	}

	CenterMass*=1.0/System->getNumParticles();
	
	for(int i(0); i < System->getNumParticles(); ++i)
	{
		TempCenterMass = CenterMass - Vec3f(System->getPosition(i) * (1.0/System->getNumParticles()));
		DistanceSquared = System->getPosition(i).dist2(TempCenterMass);
		if(DistanceSquared > 0)
		{
			Force = (getGravitationalConstant() * getParticleMass()* getParticleMass() * (System->getNumParticles()-1)* (TempCenterMass - System->getPosition(i)))* (1.0/DistanceSquared);
			
		}
		else
		{
			Force.setValues(0.0,0.0,0.0);
		}
			Acceleration = 1.0f/getParticleMass() * Force;
			System->setAcceleration(Acceleration,i);
	}
	//subtract 

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollectiveGravityParticleSystemAffector::CollectiveGravityParticleSystemAffector(void) :
    Inherited()
{
}

CollectiveGravityParticleSystemAffector::CollectiveGravityParticleSystemAffector(const CollectiveGravityParticleSystemAffector &source) :
    Inherited(source)
{
}

CollectiveGravityParticleSystemAffector::~CollectiveGravityParticleSystemAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollectiveGravityParticleSystemAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CollectiveGravityParticleSystemAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CollectiveGravityParticleSystemAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

