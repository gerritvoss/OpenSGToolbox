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

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsBoxGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsBoxGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsBoxGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsBoxGeom::onCreate(const PhysicsBoxGeom *)
{
	_GeomID = dCreateBox(0, getLengths().x(), getLengths().y(), getLengths().z());
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(_GeomID));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(_GeomID));
}

void PhysicsBoxGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
Real32 PhysicsBoxGeom::getPointDepth(const Vec3f& p)
{
	return (Real32)dGeomBoxPointDepth(_GeomID, p.x(), p.y(), p.z());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsBoxGeom::PhysicsBoxGeom(void) :
    Inherited()
{
}

PhysicsBoxGeom::PhysicsBoxGeom(const PhysicsBoxGeom &source) :
    Inherited(source)
{
}

PhysicsBoxGeom::~PhysicsBoxGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsBoxGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & LengthsFieldMask)
    {
        dGeomBoxSetLengths(_GeomID, getLengths().x(),getLengths().y(),getLengths().z() );
    }
}

void PhysicsBoxGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBoxGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsBoxGeom.cpp,v 1.1 2005/10/21 15:44:24 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSBOXGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSBOXGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSBOXGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

