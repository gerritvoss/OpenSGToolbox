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

#include "OSGBurstParticleGenerator.h"
#include "ParticleSystem/OSGParticleSystem.h"
//#include "ParticleSystem/OSGRateParticleGeneratorBase.h"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BurstParticleGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BurstParticleGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool BurstParticleGenerator::generate(ParticleSystemPtr System, const Time& elps)
{
	for(int i(0);i<getBurstAmount();i++)
	{
		generateDynamic(System);
	}
	return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BurstParticleGenerator::BurstParticleGenerator(void) :
    Inherited()
{
}

BurstParticleGenerator::BurstParticleGenerator(const BurstParticleGenerator &source) :
    Inherited(source)
{
}

BurstParticleGenerator::~BurstParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BurstParticleGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BurstParticleGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BurstParticleGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBURSTPARTICLEGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBURSTPARTICLEGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBURSTPARTICLEGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

