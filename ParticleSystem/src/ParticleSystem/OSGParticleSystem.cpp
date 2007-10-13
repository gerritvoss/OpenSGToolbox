/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystem

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystem::update(const Time& elps)
{
    //TODO: Implement
    //Fire a Update Event
    produceSystemUpdated();
}

void ParticleSystem::produceParticleGenerated(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleGenerated(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceParticleKilled(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleKilled(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceParticleStolen(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleStolen(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceSystemUpdated(void)
{
   ParticleSystemEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->systemUpdated(TheEvent);
      SetItor = NextItor;
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystem::ParticleSystem(void) :
    Inherited(),
    _SystemUpdateListener(this)
{
}

ParticleSystem::ParticleSystem(const ParticleSystem &source) :
    Inherited(source),
    _SystemUpdateListener(this)
{
}

ParticleSystem::~ParticleSystem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleSystem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystem NI" << std::endl;
}

/*----------------------------- internal classes ----------------------------*/
void ParticleSystem::SystemUpdateListener::update(const UpdateEvent& e)
{
    _System->update(e.getElapsedTime());
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
    static Char8 cvsid_hpp       [] = OSGPARTICLESYSTEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLESYSTEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLESYSTEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

