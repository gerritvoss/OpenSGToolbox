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
#include "OSGPhysicsDef.h"

#include "OSGPhysicsHashSpace.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsHashSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHashSpace::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsHashSpace::onCreate(const PhysicsHashSpace *id /* = NULL */)
{
	PhysicsHashSpacePtr tmpPtr(*this);
	    tmpPtr->sID = dHashSpaceCreate(0);
}

void PhysicsHashSpace::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec2f PhysicsHashSpace::getLevels(void)
{
	PhysicsHashSpacePtr tmpPtr(*this);
	Int32 i,j;
	dHashSpaceGetLevels(tmpPtr->sID, &i, &j);
	return Vec2f(i, j);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsHashSpace::setLevels(const Vec2f &value )
{
	PhysicsHashSpacePtr tmpPtr(*this);
	dHashSpaceSetLevels(tmpPtr->sID, (Int32)value.x(), (Int32)value.y());
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsHashSpace::initHashSpace()
{
    setLevels(PhysicsHashSpaceBase::getLevels());
    initSpace();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void PhysicsHashSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsHashSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHashSpace NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsHashSpace.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSHASHSPACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSHASHSPACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSHASHSPACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

