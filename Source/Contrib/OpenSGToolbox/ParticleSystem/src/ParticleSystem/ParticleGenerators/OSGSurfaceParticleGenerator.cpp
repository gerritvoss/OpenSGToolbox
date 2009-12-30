/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala , Daniel Guilliams                  *
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

#include "OSGSurfaceParticleGenerator.h"
#include "Distributions/1D/OSGDistribution1D.h"
#include "Distributions/3D/OSGDistribution3D.h"
#include "Distributions/3D/OSGGeoSurfaceDistribution3D.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SurfaceParticleGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SurfaceParticleGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool SurfaceParticleGenerator::generate(ParticleSystemPtr System, const Time& elps)
{
	Pnt3f PositionReturnValue = Pnt3f(0.0f,0.0f,0.0f);
	Pnt3f SecPositionReturnValue = Pnt3f(0.0f,0.0f,0.0f);
	Vec3f NormalReturnValue = Vec3f(0.0f,0.0f,1.0f);
	Vec3f ColorReturnValue = Pnt3f(1.0,1.0f,1.0f);
	Real32 TransparencyReturnValue(1.0f);
	Vec3f SizeReturnValue = Vec3f(1.0,1.0f,1.0f);
	Time LifespanReturnValue = -1;
	Time AgeReturnValue = 0;
	Vec3f VelocityReturnValue = Vec3f(0.0f,0.0f,0.0f);
	Vec3f SecVelocityReturnValue = Vec3f(0.0f,0.0f,0.0f);
	Vec3f TangentReturnValue = Vec3f(0.0f,0.0f,1.0f);
	Real32 SpeedReturnValue = 0.0;
	Vec3f AccelerationReturnValue = Vec3f(0.0f,0.0f,0.0f);
	StringToUInt32Map AttributesReturnValue;

    Vec3f Tangent;

	if(getPositionVelocityDistribution() != NullFC)
	{
        getPositionVelocityDistribution()->generate(PositionReturnValue, NormalReturnValue, Tangent);
        SecPositionReturnValue = PositionReturnValue;
	}
		
	if(getColorDistribution() != NullFC)
	{
		ColorReturnValue = getColorDistribution()->generate();
	}

	if(getTransparencyDistribution() != NullFC)
	{
		TransparencyReturnValue = getTransparencyDistribution()->generate();
	}
	Color4f FinalColorValue(ColorReturnValue[0],ColorReturnValue[1],ColorReturnValue[2],TransparencyReturnValue);

	if(getSizeDistribution() != NullFC)
	{
		SizeReturnValue = getSizeDistribution()->generate();
	}

	if(getLifespanDistribution() != NullFC)
	{
		LifespanReturnValue = getLifespanDistribution()->generate();
	}
	if(getAgeDistribution() != NullFC)
	{
		AgeReturnValue = getAgeDistribution()->generate();
	}
	AgeReturnValue += elps;
	if(getSpeedDistribution() != NullFC)
	{
		SpeedReturnValue = getSpeedDistribution()->generate();
	}

	if(getPositionVelocityDistribution() != NullFC)
	{
		VelocityReturnValue = SpeedReturnValue * NormalReturnValue;
	}
    SecVelocityReturnValue = VelocityReturnValue;
	if(getAccelerationDistribution() != NullFC)
	{
		AccelerationReturnValue = getAccelerationDistribution()->generate();
	}

	ParticleGenerator::generate(System,
		PositionReturnValue, 
		SecPositionReturnValue, 
		NormalReturnValue,
		FinalColorValue,
		SizeReturnValue,
		LifespanReturnValue,
		AgeReturnValue,
		VelocityReturnValue,
		SecVelocityReturnValue,
		AccelerationReturnValue,
		AttributesReturnValue);


	
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SurfaceParticleGenerator::SurfaceParticleGenerator(void) :
    Inherited()
{
}

SurfaceParticleGenerator::SurfaceParticleGenerator(const SurfaceParticleGenerator &source) :
    Inherited(source)
{
}

SurfaceParticleGenerator::~SurfaceParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SurfaceParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SurfaceParticleGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SurfaceParticleGenerator NI" << std::endl;
}

OSG_END_NAMESPACE

