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

#include "OSGParticleGeometryCollisionEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleGeometryCollisionEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleGeometryCollisionEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleGeometryCollisionEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleGeometryCollisionEventDetailsTransitPtr ParticleGeometryCollisionEventDetails::create(
                                                                                FieldContainer* const Source,
                                        Time TimeStamp,
                                        Real32 HitT,
                                        Node* const HitNode,
                                        Int32 HitPolygonIndex,
                                        Vec3f HitNormal,
                                        Pnt3f HitPoint,
                                        ParticleSystem* const System,
                                        UInt32 Index)
{
    ParticleGeometryCollisionEventDetails* TheEventDetails = ParticleGeometryCollisionEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setHitT(HitT);
    TheEventDetails->setHitNode(HitNode);
    TheEventDetails->setHitPolygonIndex(HitPolygonIndex);
    TheEventDetails->setHitNormal(HitNormal);
    TheEventDetails->setHitPoint(HitPoint);
    TheEventDetails->setSystem(System);
    TheEventDetails->setParticleIndex(Index);

    return ParticleGeometryCollisionEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleGeometryCollisionEventDetails::ParticleGeometryCollisionEventDetails(void) :
    Inherited()
{
}

ParticleGeometryCollisionEventDetails::ParticleGeometryCollisionEventDetails(const ParticleGeometryCollisionEventDetails &source) :
    Inherited(source)
{
}

ParticleGeometryCollisionEventDetails::~ParticleGeometryCollisionEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleGeometryCollisionEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleGeometryCollisionEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleGeometryCollisionEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
