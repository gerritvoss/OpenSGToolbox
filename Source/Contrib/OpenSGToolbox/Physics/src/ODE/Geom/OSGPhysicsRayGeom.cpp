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

#include "OSGPhysicsRayGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsRayGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsRayGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsRayGeom::onCreate(const PhysicsRayGeom *)
{
	_GeomID = dCreateRay(0, getLength());
    setCategoryBits(dGeomGetCategoryBits(_GeomID));
    setCollideBits(dGeomGetCollideBits(_GeomID));
}

void PhysicsRayGeom::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsRayGeom::PhysicsRayGeom(void) :
    Inherited()
{
}

PhysicsRayGeom::PhysicsRayGeom(const PhysicsRayGeom &source) :
    Inherited(source)
{
}

PhysicsRayGeom::~PhysicsRayGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsRayGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & LengthFieldMask)
	{
		dGeomRaySetLength(_GeomID, getLength());
	}
	if((whichField & RayPositionFieldMask) || (whichField & DirectionFieldMask))
	{
		dGeomRaySet(_GeomID, getRayPosition().x(), getRayPosition().y(), getRayPosition().z(), getDirection().x(), getDirection().y(), getDirection().z() );
	}
	
	if(whichField & ClosestHitFieldMask)
	{
		dGeomRaySetClosestHit(_GeomID, getClosestHit() ? 1:0);
	}
}

void PhysicsRayGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsRayGeom NI" << std::endl;
}

