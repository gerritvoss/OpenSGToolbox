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

#include "OSGPhysicsSimpleSpace.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSimpleSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSimpleSpace::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsSimpleSpace::onCreate(const PhysicsSimpleSpace *id /* = NULL */)
{
	PhysicsSimpleSpacePtr tmpPtr(*this);
	tmpPtr->sID =  dSimpleSpaceCreate(0);
}

void PhysicsSimpleSpace::onDestroy()
{
	//empty
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSimpleSpace::PhysicsSimpleSpace(void) :
    Inherited()
{
}

PhysicsSimpleSpace::PhysicsSimpleSpace(const PhysicsSimpleSpace &source) :
    Inherited(source)
{
}

PhysicsSimpleSpace::~PhysicsSimpleSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSimpleSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsSimpleSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSimpleSpace NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsSimpleSpace.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSSIMPLESPACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSSIMPLESPACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSSIMPLESPACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

