/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGRateParticleDecorator.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRateParticleDecoratorBase.cpp file.
// To modify it, please change the .fcd file (OSGRateParticleDecorator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RateParticleDecorator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RateParticleDecorator::generate(ParticleSystemRefPtr System, const Time& elps)
{
	setTimeSinceLastGeneration(getTimeSinceLastGeneration()+elps);

	while(getTimeSinceLastGeneration() > 1.0f/getGenerationRate())
	{
		getDecoratee()->generate(System, elps);

		//Decrement Time Since Last Action
		setTimeSinceLastGeneration(getTimeSinceLastGeneration()-1.0f/getGenerationRate());
	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RateParticleDecorator::RateParticleDecorator(void) :
    Inherited()
{
}

RateParticleDecorator::RateParticleDecorator(const RateParticleDecorator &source) :
    Inherited(source)
{
}

RateParticleDecorator::~RateParticleDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RateParticleDecorator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void RateParticleDecorator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump RateParticleDecorator NI" << std::endl;
}

OSG_END_NAMESPACE
