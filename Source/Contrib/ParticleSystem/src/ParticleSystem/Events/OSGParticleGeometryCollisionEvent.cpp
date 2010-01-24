/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGParticleGeometryCollisionEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleGeometryCollisionEventBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleGeometryCollisionEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleGeometryCollisionEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleGeometryCollisionEventTransitPtr ParticleGeometryCollisionEvent::create(
                                                                                FieldContainerRefPtr Source,
                                        Time TimeStamp,
                                        Real32 HitT,
                                        NodeRefPtr HitNode,
                                        Int32 HitPolygonIndex,
                                        Vec3f HitNormal,
                                        Pnt3f HitPoint,
                                        ParticleSystemRefPtr System,
                                        UInt32 Index)
{
    ParticleGeometryCollisionEvent* TheEvent = ParticleGeometryCollisionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setHitT(HitT);
    TheEvent->setHitNode(HitNode);
    TheEvent->setHitPolygonIndex(HitPolygonIndex);
    TheEvent->setHitNormal(HitNormal);
    TheEvent->setHitPoint(HitPoint);
    TheEvent->setSystem(System);
    TheEvent->setParticleIndex(Index);

    return ParticleGeometryCollisionEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleGeometryCollisionEvent::ParticleGeometryCollisionEvent(void) :
    Inherited()
{
}

ParticleGeometryCollisionEvent::ParticleGeometryCollisionEvent(const ParticleGeometryCollisionEvent &source) :
    Inherited(source)
{
}

ParticleGeometryCollisionEvent::~ParticleGeometryCollisionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleGeometryCollisionEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleGeometryCollisionEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleGeometryCollisionEvent NI" << std::endl;
}

OSG_END_NAMESPACE
