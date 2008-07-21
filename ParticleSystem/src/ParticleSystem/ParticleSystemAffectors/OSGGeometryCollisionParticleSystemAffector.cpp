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
#include <OpenSG/OSGIntersectAction.h>

#include "OSGGeometryCollisionParticleSystemAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeometryCollisionParticleSystemAffector
s 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeometryCollisionParticleSystemAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GeometryCollisionParticleSystemAffector::affect(ParticleSystemPtr System, const Time& elps)
{
	UInt32 NumParticles(System->getNumParticles());
	
	Line ray;// = Line(Pnt3f(5,0,-10), Vec3f(0,-1,0));
    IntersectAction *iAct = IntersectAction::create();
	Pnt3f ParticlePos, ParticleSecPos;
    

	Real32 HitT(0.0f);
	for(UInt32 i(0) ; i<NumParticles ; ++i)
	{
		ParticlePos = System->getPosition(i);
		ParticleSecPos = System->getSecPosition(i);
		ray.setValue(ParticleSecPos, ParticlePos);
		iAct->setLine(ray);
		iAct->apply(getCollisionNode());
	    
		if (iAct->didHit())
		{
			HitT = iAct->getHitT();
			if(HitT > 0.0f && HitT*HitT<ParticlePos.dist2(ParticleSecPos))
			{
				//System->killParticle(i);
				System->setVelocity(-System->getVelocity(i),i);
				System->setSecPosition(iAct->getHitPoint(), i);
				System->setPosition(iAct->getHitPoint(),i);
			}
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeometryCollisionParticleSystemAffector::GeometryCollisionParticleSystemAffector(void) :
    Inherited()
{
}

GeometryCollisionParticleSystemAffector::GeometryCollisionParticleSystemAffector(const GeometryCollisionParticleSystemAffector &source) :
    Inherited(source)
{
}

GeometryCollisionParticleSystemAffector::~GeometryCollisionParticleSystemAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeometryCollisionParticleSystemAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeometryCollisionParticleSystemAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeometryCollisionParticleSystemAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGEOMETRYCOLLISIONPARTICLESYSTEMAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOMETRYCOLLISIONPARTICLESYSTEMAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOMETRYCOLLISIONPARTICLESYSTEMAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

