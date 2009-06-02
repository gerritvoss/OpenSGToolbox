/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
#include "OSGPhysicsConfig.h"

#include "OSGPhysicsQuadTreeSpace.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsQuadTreeSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsQuadTreeSpace::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsQuadTreeSpace::onCreate(const PhysicsQuadTreeSpace *id /* = NULL */)
{
	PhysicsQuadTreeSpacePtr tmpPtr(*this);
	//call initQuadTree
}

void PhysicsQuadTreeSpace::onDestroy()
{
	//empty
}

void PhysicsQuadTreeSpace::initQuadTree(dSpaceID space, Vec3f center, Vec3f ex, Int32 depth)
{
	PhysicsQuadTreeSpacePtr tmpPtr(*this);
	dVector3 c, e;
	c[0]=center.x();
	c[1]=center.y();
	c[2]=center.z();
	e[0]=ex.x();
	e[1]=ex.y();
	e[2]=ex.z();
	tmpPtr->sID = dQuadTreeSpaceCreate(space, c, e, depth);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void PhysicsQuadTreeSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsQuadTreeSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsQuadTreeSpace NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsQuadTreeSpace.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSQUADTREESPACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSQUADTREESPACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSQUADTREESPACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

