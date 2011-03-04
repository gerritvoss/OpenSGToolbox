/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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

#include "OSGPhysicsHashSpace.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsHashSpaceBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsHashSpace.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHashSpace::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsHashSpace::initHashSpace()
{
    setLevels(getLevels());
    initSpace();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsHashSpace::onCreate(const PhysicsHashSpace *id /* = NULL */)
{
    _SpaceID = dHashSpaceCreate(0);
}

void PhysicsHashSpace::onDestroy()
{
	//empty
}
/*----------------------- constructors & destructors ----------------------*/

PhysicsHashSpace::PhysicsHashSpace(void) :
    Inherited()
{
}

PhysicsHashSpace::PhysicsHashSpace(const PhysicsHashSpace &source) :
    Inherited(source)
{
}

PhysicsHashSpace::~PhysicsHashSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHashSpace::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & LevelsFieldMask)
    {
	    dHashSpaceSetLevels(_SpaceID, (Int32)getLevels().x(), (Int32)getLevels().y());
    }
}

void PhysicsHashSpace::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHashSpace NI" << std::endl;
}

OSG_END_NAMESPACE
