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

#include "OSGParticleGenerator.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void ParticleGenerator::generate(ParticleSystemPtr System,
		Pnt3f& PositionReturnValue, 
		Pnt3f& SecPositionReturnValue, 
		Vec3f& NormalReturnValue,
		Color4f& ColorReturnValue,
		Vec3f& SizeReturnValue,
		Time& LifespanReturnValue,
		Time& AgeReturnValue,
		Vec3f& VelocityReturnValue,
		Vec3f& SecVelocityReturnValue,
		Vec3f& AccelerationReturnValue,
        StringToUInt32Map& AttributeReturnValue) const
{
	if(System != NullFC)
	{
		if(getBeacon() == NullFC)
		{
			System->addParticle(PositionReturnValue,
				SecPositionReturnValue,
				NormalReturnValue,
				ColorReturnValue,
				SizeReturnValue,
				LifespanReturnValue,
				AgeReturnValue,
				VelocityReturnValue,
				SecVelocityReturnValue,
				AccelerationReturnValue,
				AttributeReturnValue);
		}
		else
		{
			Matrix BeaconToWorld(getBeacon()->getToWorld());
			
			BeaconToWorld.mult(PositionReturnValue, PositionReturnValue);
			BeaconToWorld.mult(SecPositionReturnValue, SecPositionReturnValue);
			BeaconToWorld.mult(NormalReturnValue, NormalReturnValue);
			BeaconToWorld.mult(SizeReturnValue, SizeReturnValue);
			BeaconToWorld.mult(VelocityReturnValue, VelocityReturnValue);
			BeaconToWorld.mult(SecVelocityReturnValue, SecVelocityReturnValue);
			BeaconToWorld.mult(AccelerationReturnValue, AccelerationReturnValue);
		
			System->addParticle(PositionReturnValue,
				SecPositionReturnValue,
				NormalReturnValue,
				ColorReturnValue,
				SizeReturnValue,
				LifespanReturnValue,
				AgeReturnValue,
				VelocityReturnValue,
				SecVelocityReturnValue,
				AccelerationReturnValue,
				AttributeReturnValue);

		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleGenerator::ParticleGenerator(void) :
    Inherited()
{
}

ParticleGenerator::ParticleGenerator(const ParticleGenerator &source) :
    Inherited(source)
{
}

ParticleGenerator::~ParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPARTICLEGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLEGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLEGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

