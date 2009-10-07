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

#include <OpenSG/OSGConfig.h>

#include "OSGCollisionEvent.h"
#include "ODE/Geom/OSGPhysicsGeom.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CollisionEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionEvent::initMethod (void)
{
}

CollisionEventPtr CollisionEvent::create(  FieldContainerPtr Source,
                                            Time TimeStamp,
                                            const Pnt3f& Position,
                                            const Vec3f& Normal,
                                            PhysicsGeomPtr Geom1,
                                            PhysicsGeomPtr Geom2,
                                            const Vec3f& Velocity1,
                                            const Vec3f& Velocity2)
{
    CollisionEventPtr TheEvent = CollisionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setPosition(Position);
    TheEvent->setNormal(Normal);
    TheEvent->setObject1Geom(Geom1);
    TheEvent->setObject2Geom(Geom2);
    TheEvent->setObject1Velocity(Velocity1);
    TheEvent->setObject2Velocity(Velocity2);

    return TheEvent;
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

void CollisionEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CollisionEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CollisionEvent NI" << std::endl;
}


OSG_END_NAMESPACE

