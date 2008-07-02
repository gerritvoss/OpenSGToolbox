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

#include "OSGDistanceKillParticleAffector.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistanceKillParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceKillParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool DistanceKillParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Real32& DistanceSqrd)
{
    //TODO: Implement

	return DistanceSqrd <= getKillDistance()*getKillDistance();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceKillParticleAffector::DistanceKillParticleAffector(void) :
    Inherited()
{
}

DistanceKillParticleAffector::DistanceKillParticleAffector(const DistanceKillParticleAffector &source) :
    Inherited(source)
{
}

DistanceKillParticleAffector::~DistanceKillParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceKillParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DistanceKillParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DistanceKillParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISTANCEKILLPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTANCEKILLPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTANCEKILLPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

