/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#include "OSGParticleCollisionEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleCollisionEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleCollisionEvent::initMethod (void)
{
}

ParticleCollisionEventPtr ParticleCollisionEvent::create(  FieldContainerPtr Source,
                                        Time TimeStamp,
                                        Real32 HitT,
                                        NodePtr HitNode,
                                        Int32 HitPolygonIndex,
                                        Vec3f HitNormal,
                                        Pnt3f HitPoint)
{
    ParticleCollisionEventPtr TheEvent = ParticleCollisionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setHitT(HitT);
    TheEvent->setHitNode(HitNode);
    TheEvent->setHitPolygonIndex(HitPolygonIndex);
    TheEvent->setHitNormal(HitNormal);
    TheEvent->setHitPoint(HitPoint);

    return TheEvent;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleCollisionEvent::ParticleCollisionEvent(void) :
    Inherited()
{
}

ParticleCollisionEvent::ParticleCollisionEvent(const ParticleCollisionEvent &source) :
    Inherited(source)
{
}

ParticleCollisionEvent::~ParticleCollisionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleCollisionEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleCollisionEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleCollisionEvent NI" << std::endl;
}


OSG_END_NAMESPACE

