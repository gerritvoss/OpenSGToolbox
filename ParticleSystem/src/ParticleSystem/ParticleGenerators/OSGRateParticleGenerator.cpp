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

#include "OSGRateParticleGenerator.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RateParticleGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RateParticleGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RateParticleGenerator::generate(ParticleSystemPtr System, const Time& elps)
{
	setTimeSinceLastGeneration(getTimeSinceLastGeneration()+elps);

	while(getTimeSinceLastGeneration() > 1.0f/getGenerationRate())
	{
		generateDynamic(System, getTimeSinceLastGeneration()-1.0f/getGenerationRate());

		//Decrement Time Since Last Action
		setTimeSinceLastGeneration(getTimeSinceLastGeneration()-1.0f/getGenerationRate());

	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RateParticleGenerator::RateParticleGenerator(void) :
    Inherited()
{
}

RateParticleGenerator::RateParticleGenerator(const RateParticleGenerator &source) :
    Inherited(source)
{
}

RateParticleGenerator::~RateParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RateParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RateParticleGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RateParticleGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGRATEPARTICLEGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRATEPARTICLEGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRATEPARTICLEGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

