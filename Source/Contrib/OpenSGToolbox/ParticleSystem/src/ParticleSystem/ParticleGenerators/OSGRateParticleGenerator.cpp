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
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>
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
	Real32 SecPerParticle(0.0f);

    //the actual generation rate will depend on whether or not there is a rate spread
    if(getRateSpread() > 0.0f  && getGenerationRate() > 0.0f)
    {   
        //SecPerParticle = abs(1.0f/RandomPoolManager::getRandomReal32(getGenerationRate()-getRateSpread(),getGenerationRate()+getRateSpread()));
        SecPerParticle = 1.0f/getGenerationRate();
    }
    else
    {
		SecPerParticle = 1.0f/getGenerationRate();
    }

	while(getTimeSinceLastGeneration() > SecPerParticle)
	{
		generateDynamic(System, getTimeSinceLastGeneration()-SecPerParticle);

		//Decrement Time Since Last Action
		setTimeSinceLastGeneration(getTimeSinceLastGeneration()-SecPerParticle);

        //if(getRateSpread() > 0.0f  && getGenerationRate() > 0.0f)
        //{   
            //SecPerParticle = abs(1.0f/(osgsqrt(-2.0f * osglog(1.0f - RandomPoolManager::getRandomReal32(0.0,1.0)))*
                //osgcos(6.283185f * RandomPoolManager::getRandomReal32(0.0,1.0))*getRateSpread() + getGenerationRate()));
        //}

	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RateParticleGenerator::RateParticleGenerator(void) :
    Inherited(),
		_IsRateZero(false),
        _NormalDistribution(0.0,1.0)
{
}

RateParticleGenerator::RateParticleGenerator(const RateParticleGenerator &source) :
    Inherited(source),
		_IsRateZero(source._IsRateZero),
        _NormalDistribution(source._NormalDistribution)
{
}

RateParticleGenerator::~RateParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RateParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & GenerationRateFieldMask)
    {
		if(_IsRateZero)
		{
			setTimeSinceLastGeneration(0.0f);
		}

		_IsRateZero = (getGenerationRate() <= 0.0);
    }
    if(((whichField & GenerationRateFieldMask) || (whichField & RateSpreadFieldMask))
            && (getGenerationRate() > 0.0f && getRateSpread() > 0.0f))
    {
        _NormalDistribution = boost::normal_distribution<Real32>(getGenerationRate(), getRateSpread());
    }
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
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

