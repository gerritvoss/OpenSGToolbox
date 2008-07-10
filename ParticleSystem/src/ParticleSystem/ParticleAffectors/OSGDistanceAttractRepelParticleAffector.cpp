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
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>

#include "OSGDistanceAttractRepelParticleAffector.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistanceAttractRepelParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceAttractRepelParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DistanceAttractRepelParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement)
{
	Real32 d = Displacement.length();
	Vec3f dnormal =  Displacement;
	dnormal =  dnormal *(1.0/d);
	if( d > getMinDistance()  && d < getMaxDistance())
	{
		Real32 t((getQuadratic() * (1.0/(d*d)) + getLinear() * (1.0/d) + getConstant())*elps);
		if(t > d)
		{
			t=d;
		}

		Pnt3f pos = System->getPosition(ParticleIndex) + (dnormal * t);
		System->setPosition(pos,ParticleIndex) ;
	}
	return false;
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceAttractRepelParticleAffector::DistanceAttractRepelParticleAffector(void) :
    Inherited()
{
}

DistanceAttractRepelParticleAffector::DistanceAttractRepelParticleAffector(const DistanceAttractRepelParticleAffector &source) :
    Inherited(source)
{
}

DistanceAttractRepelParticleAffector::~DistanceAttractRepelParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceAttractRepelParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DistanceAttractRepelParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DistanceAttractRepelParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISTANCEATTRACTREPELPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCEATTRACTREPELPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCEATTRACTREPELPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

