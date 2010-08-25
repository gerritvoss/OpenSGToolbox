/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)*
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGAgeParticleFunction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAgeParticleFunctionBase.cpp file.
// To modify it, please change the .fcd file (OSGAgeParticleFunction.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AgeParticleFunction::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AgeParticleFunction::AgeParticleFunction(void) :
    Inherited()
{
}

AgeParticleFunction::AgeParticleFunction(const AgeParticleFunction &source) :
    Inherited(source)
{
}

AgeParticleFunction::~AgeParticleFunction(void)
{
}

UInt32 AgeParticleFunction::evaluate(ParticleSystemUnrecPtr System, UInt32 ParticleIndex, UInt32 SequenceLength)
{
	Real32 age = System->getAge(ParticleIndex);
	UInt32 index(0);
	switch(getSequenceOrder())
	{

	case REVERSE_CYCLE:
		{
			index = SequenceLength - ((UInt32)(osgFloor(age/getSequenceTime() + 0.5f)) % SequenceLength);
			index--;
			break;
		}

	case CUSTOM:
		{
			index = (UInt32)(osgFloor(age/getSequenceTime() + 0.5f));
			index = index % getMFCustomSequence()->size();
			index = getCustomSequence(index) % SequenceLength;
			break;
		}

	case CYCLE:
	default:
		{
			index = (UInt32)(osgFloor(age/getSequenceTime() + 0.5f)) % SequenceLength;
			break;
		}

	} 
	return index;
}

/*----------------------------- class specific ----------------------------*/

void AgeParticleFunction::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AgeParticleFunction::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AgeParticleFunction NI" << std::endl;
}

OSG_END_NAMESPACE
