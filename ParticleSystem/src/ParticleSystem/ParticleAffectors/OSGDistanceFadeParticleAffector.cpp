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

#include "OSGDistanceFadeParticleAffector.h"
#include <OpenSG/Toolbox/OSGInterpolations.h>
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistanceFadeParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceFadeParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DistanceFadeParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement)
{
    //TODO: Implement
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
			lerp<Real32>(getFadeStartAlpha(),getFadeEndAlpha(),(osgsqrt(DistanceSqrd) - getDistanceFadeStart())/(getDistanceFadeEnd() - getDistanceFadeStart()), Alpha);
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

void DistanceFadeParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DistanceFadeParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DistanceFadeParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISTANCEFADEPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCEFADEPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCEFADEPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

