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

#include "OSGPhysicsQuadTreeSpace.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsQuadTreeSpaceBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsQuadTreeSpace.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsQuadTreeSpace::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsQuadTreeSpace::initQuadTree(dSpaceID space)
{
	dVector3 c, e;
	c[0]=getCenter().x();
	c[1]=getCenter().y();
	c[2]=getCenter().z();
	e[0]=getExtent().x();
	e[1]=getExtent().y();
	e[2]=getExtent().z();
	_SpaceID = dQuadTreeSpaceCreate(space, c, e, getDepth());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsQuadTreeSpace::onCreate(const PhysicsQuadTreeSpace *id /* = NULL */)
{
    initQuadTree(0);
}

void PhysicsQuadTreeSpace::onDestroy()
{
	//empty
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsQuadTreeSpace::PhysicsQuadTreeSpace(void) :
    Inherited()
{
}

PhysicsQuadTreeSpace::PhysicsQuadTreeSpace(const PhysicsQuadTreeSpace &source) :
    Inherited(source)
{
}

PhysicsQuadTreeSpace::~PhysicsQuadTreeSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsQuadTreeSpace::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if((whichField & CenterFieldMask) ||
        (whichField & ExtentFieldMask) ||
        (whichField & DepthFieldMask))
    {
        initQuadTree(_SpaceID);
    }
}

void PhysicsQuadTreeSpace::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsQuadTreeSpace NI" << std::endl;
}

OSG_END_NAMESPACE
