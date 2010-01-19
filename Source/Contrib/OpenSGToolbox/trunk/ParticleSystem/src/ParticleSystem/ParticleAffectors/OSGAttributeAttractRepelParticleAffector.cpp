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

#include "OSGAttributeAttractRepelParticleAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AttributeAttractRepelParticleAffector
l 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AttributeAttractRepelParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AttributeAttractRepelParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	if(System != NullFC)
	{
		Vec3f Displacement(System->getSecPosition(ParticleIndex) - System->getPosition(ParticleIndex) );

		Real32 Distance(Displacement.squareLength());

		if((Distance > getMinDistance()*getMinDistance()) &&
		(Distance < getMaxDistance()*getMaxDistance()))
		{
			Distance = osgsqrt(Distance);
			Displacement.normalize();

			Real32 t((getQuadratic() * (Distance*Distance) + getLinear() * Distance + getConstant())*elps);
			if(t > Distance)
			{
				t=Distance;
			}

			System->setPosition(System->getPosition(ParticleIndex) + (Displacement * t),ParticleIndex) ;
		}
	}
	return false;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AttributeAttractRepelParticleAffector::AttributeAttractRepelParticleAffector(void) :
    Inherited()
{
}

AttributeAttractRepelParticleAffector::AttributeAttractRepelParticleAffector(const AttributeAttractRepelParticleAffector &source) :
    Inherited(source)
{
}

AttributeAttractRepelParticleAffector::~AttributeAttractRepelParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AttributeAttractRepelParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AttributeAttractRepelParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AttributeAttractRepelParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

