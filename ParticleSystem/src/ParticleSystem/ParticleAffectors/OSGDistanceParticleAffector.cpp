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
#include <OpenSG/OSGCamera.h>
#include <OpenSG/Toolbox/OSGMathUtils.h>
#include "ParticleSystem/OSGParticleSystem.h"

#include "OSGDistanceParticleAffector.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistanceParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


bool DistanceParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	if(System != NullFC && getParticleSystemNode() != NullFC)
	{
		Vec3f Displacement;

		Pnt3f ParticlePositionInWorldSpace = System->getPosition(ParticleIndex);
		getParticleSystemNode()->getToWorld().multFullMatrixPnt(ParticlePositionInWorldSpace);

		Pnt3f NodePositionInWorldSpace;

		//Calculate the Distance
		switch(getDistanceFromSource())
		{
		case DISTANCE_FROM_NODE:
			if(getDistanceFromNode() != NullFC)
			{
				Matrix m = getDistanceFromNode()->getToWorld();
				NodePositionInWorldSpace.setValues(m[0][3],m[1][3],m[2][3]);
			}
			break;
		case DISTANCE_FROM_CAMERA:
			if(getDistanceFromCamera() != NullFC)
			{
				Matrix m;
				getDistanceFromCamera()->getViewing(m,1,1);
				getPFromViewMat(NodePositionInWorldSpace,m);
			}
		default:
			break;
		}

		Displacement = NodePositionInWorldSpace - ParticlePositionInWorldSpace;

		return affect(System, ParticleIndex, elps, Displacement);
	}
	else
	{
		return false;
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceParticleAffector::DistanceParticleAffector(void) :
    Inherited()
{
}

DistanceParticleAffector::DistanceParticleAffector(const DistanceParticleAffector &source) :
    Inherited(source)
{
}

DistanceParticleAffector::~DistanceParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DistanceParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DistanceParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISTANCEPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCEPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCEPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

