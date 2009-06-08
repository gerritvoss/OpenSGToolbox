/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#define OSG_COMPILEPHYSICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsSweepAndPruneSpace.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSweepAndPruneSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSweepAndPruneSpace::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSweepAndPruneSpace::PhysicsSweepAndPruneSpace(void) :
    Inherited()
{
}

PhysicsSweepAndPruneSpace::PhysicsSweepAndPruneSpace(const PhysicsSweepAndPruneSpace &source) :
    Inherited(source)
{
}

PhysicsSweepAndPruneSpace::~PhysicsSweepAndPruneSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSweepAndPruneSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & AxisOrderFieldMask)
    {
        dSweepAndPruneSpaceCreate(_SpaceID, getAxisOrder());
    }
}

void PhysicsSweepAndPruneSpace::onCreate(const PhysicsSweepAndPruneSpace *id /* = NULL */)
{
    _SpaceID = dSweepAndPruneSpaceCreate(0, getAxisOrder());
}

void PhysicsSweepAndPruneSpace::onDestroy()
{
	//empty
}

void PhysicsSweepAndPruneSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSweepAndPruneSpace NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSSWEEPANDPRUNESPACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSSWEEPANDPRUNESPACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSSWEEPANDPRUNESPACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

