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

#include "OSGCollisionEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCollisionEventBase.cpp file.
// To modify it, please change the .fcd file (OSGCollisionEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

CollisionEventTransitPtr CollisionEvent::create(  FieldContainerUnrecPtr Source,
                                            Time TimeStamp,
                                            const Pnt3f& Position,
                                            const Vec3f& Normal,
                                            PhysicsGeomUnrecPtr Geom1,
                                            PhysicsGeomUnrecPtr Geom2,
                                            UInt64 Geom1Cat,
                                            UInt64 Geom1Col,
                                            UInt64 Geom2Cat,
                                            UInt64 Geom2Col,
                                            const Vec3f& Velocity1,
                                            const Vec3f& Velocity2,
                                            const Real32& ProjectedNormalSpeed)
{
    CollisionEvent* TheEvent = CollisionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setPosition(Position);
    TheEvent->setNormal(Normal);
    TheEvent->setObject1Geom(Geom1);
    TheEvent->setObject2Geom(Geom2);
    TheEvent->setObject1CategoryBits(Geom1Cat);
    TheEvent->setObject1CollideBits(Geom1Col);
    TheEvent->setObject2CategoryBits(Geom2Cat);
    TheEvent->setObject2CollideBits(Geom2Col);
    TheEvent->setObject1Velocity(Velocity1);
    TheEvent->setObject2Velocity(Velocity2);


    TheEvent->setProjectedNormalSpeed(ProjectedNormalSpeed);

    return CollisionEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollisionEvent::CollisionEvent(void) :
    Inherited()
{
}

CollisionEvent::CollisionEvent(const CollisionEvent &source) :
    Inherited(source)
{
}

CollisionEvent::~CollisionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollisionEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CollisionEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CollisionEvent NI" << std::endl;
}

OSG_END_NAMESPACE
