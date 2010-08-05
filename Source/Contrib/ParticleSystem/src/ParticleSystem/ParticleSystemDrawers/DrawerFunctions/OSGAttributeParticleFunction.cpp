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

#include "OSGAttributeParticleFunction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAttributeParticleFunctionBase.cpp file.
// To modify it, please change the .fcd file (OSGAttributeParticleFunction.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AttributeParticleFunction::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

UInt32 AttributeParticleFunction::evaluate(ParticleSystemUnrecPtr System, UInt32 ParticleIndex, UInt32 SequenceLength)
{
	UInt32 index(System->getAttribute(ParticleIndex,getAttribute()));
	switch(getSequenceOrder())
	{
	case CUSTOM:
		{
			index = getCustomSequence(index);
			break;
		}
	case DIRECT:
	default:
		{
			break;
		}
	}

	return index;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AttributeParticleFunction::AttributeParticleFunction(void) :
    Inherited()
{
}

AttributeParticleFunction::AttributeParticleFunction(const AttributeParticleFunction &source) :
    Inherited(source)
{
}

AttributeParticleFunction::~AttributeParticleFunction(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AttributeParticleFunction::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AttributeParticleFunction::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AttributeParticleFunction NI" << std::endl;
}

OSG_END_NAMESPACE
