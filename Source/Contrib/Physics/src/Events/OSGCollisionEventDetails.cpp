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

#include "OSGCollisionEventDetails.h"
#include "OSGPhysicsGeom.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCollisionEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGCollisionEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

CollisionEventDetailsTransitPtr CollisionEventDetails::create(  FieldContainer* const Source,
                                            Time TimeStamp,
                                            const Pnt3f& Position,
                                            const Vec3f& Normal,
                                            PhysicsGeom* const Geom1,
                                            PhysicsGeom* const Geom2,
                                            UInt64 Geom1Cat,
                                            UInt64 Geom1Col,
                                            UInt64 Geom2Cat,
                                            UInt64 Geom2Col,
                                            const Vec3f& Velocity1,
                                            const Vec3f& Velocity2,
                                            const Real32& ProjectedNormalSpeed)
{
    CollisionEventDetails* TheEventDetails = CollisionEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setPosition(Position);
    TheEventDetails->setNormal(Normal);
    TheEventDetails->setObject1Geom(Geom1);
    TheEventDetails->setObject2Geom(Geom2);
    TheEventDetails->setObject1CategoryBits(Geom1Cat);
    TheEventDetails->setObject1CollideBits(Geom1Col);
    TheEventDetails->setObject2CategoryBits(Geom2Cat);
    TheEventDetails->setObject2CollideBits(Geom2Col);
    TheEventDetails->setObject1Velocity(Velocity1);
    TheEventDetails->setObject2Velocity(Velocity2);


    TheEventDetails->setProjectedNormalSpeed(ProjectedNormalSpeed);

    return CollisionEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollisionEventDetails::CollisionEventDetails(void) :
    Inherited()
{
}

CollisionEventDetails::CollisionEventDetails(const CollisionEventDetails &source) :
    Inherited(source)
{
}

CollisionEventDetails::~CollisionEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollisionEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CollisionEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CollisionEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
