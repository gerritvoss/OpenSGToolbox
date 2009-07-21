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

#include "OSGDynamicsParticleGenerator.h"
#include <OpenSG/Dynamics/OSGFunction.h>
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DynamicsParticleGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DynamicsParticleGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DynamicsParticleGenerator::generateDynamic(ParticleSystemPtr System, Real32 AdditionalAging) const
{
	Pnt3f PositionReturnValue = Pnt3f(0.0,0.0f,0.0f);
	Pnt3f SecPositionReturnValue = Pnt3f(0.0,0.0f,0.0f);
	Vec3f NormalReturnValue = Vec3f(0.0,0.0f,1.0f);
	Pnt3f ColorReturnValue = Pnt3f(0.0,0.0f,0.0f);
	Real32 TransparencyReturnValue(1.0f);
	Vec3f SizeReturnValue = Vec3f(1.0,1.0f,1.0f);
	Time LifespanReturnValue = -1;
	Time AgeReturnValue = 0;
	Vec3f VelocityReturnValue = Vec3f(0.0,0.0f,0.0f);
	Vec3f SecVelocityReturnValue = Vec3f(0.0,0.0f,0.0f);
	Vec3f AccelerationReturnValue = Vec3f(0.0,0.0f,0.0f);
	StringToUInt32Map AttributesReturnValue;


    FunctionIOParameterVector EmptyParameters;
	if(getPositionFunction() != NullFC)
	{
		PositionReturnValue = 
			FunctionIOData<Pnt3f>::dcast(
			getPositionFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
	if(getSecPositionFunction() != NullFC)
	{
		SecPositionReturnValue = 
			FunctionIOData<Pnt3f>::dcast(
			getSecPositionFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}

	if(getNormalFunction() != NullFC)
	{
		NormalReturnValue = 
			FunctionIOData<Vec3f>::dcast(
			getNormalFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
		
	if(getColorFunction() != NullFC)
	{
		ColorReturnValue = 
			FunctionIOData<Pnt3f>::dcast(
			getColorFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}

	if(getTransparencyFunction() != NullFC)
	{
		TransparencyReturnValue = 
			FunctionIOData<Real32>::dcast(
			getColorFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();

	}
	
	Color4f FinalColorValue(ColorReturnValue[0],ColorReturnValue[1],ColorReturnValue[2],TransparencyReturnValue);

	if(getSizeFunction() != NullFC)
	{
		SizeReturnValue = 
			FunctionIOData<Vec3f>::dcast(
			getSizeFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}

	if(getLifespanFunction() != NullFC)
	{
		LifespanReturnValue = 
			FunctionIOData<Real32>::dcast(
			getLifespanFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
	if(getAgeFunction() != NullFC)
	{
		AgeReturnValue = 
			FunctionIOData<Real32>::dcast(
			getAgeFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
	AgeReturnValue += AdditionalAging;
	if(getVelocityFunction() != NullFC)
	{
		VelocityReturnValue = 
			FunctionIOData<Vec3f>::dcast(
			getVelocityFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
	if(getSecVelocityFunction() != NullFC)
	{
		SecVelocityReturnValue = 
			FunctionIOData<Vec3f>::dcast(
			getSecVelocityFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}
	if(getAccelerationFunction() != NullFC)
	{
		AccelerationReturnValue = 
			FunctionIOData<Vec3f>::dcast(
			getAccelerationFunction()->evaluate(EmptyParameters).front().getDataPtr()
			)->getData();
	}

	generate(System,
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
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DynamicsParticleGenerator::DynamicsParticleGenerator(void) :
    Inherited()
{
}

DynamicsParticleGenerator::DynamicsParticleGenerator(const DynamicsParticleGenerator &source) :
    Inherited(source)
{
}

DynamicsParticleGenerator::~DynamicsParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DynamicsParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DynamicsParticleGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DynamicsParticleGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDYNAMICSPARTICLEGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDYNAMICSPARTICLEGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDYNAMICSPARTICLEGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

