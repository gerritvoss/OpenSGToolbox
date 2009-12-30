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

#include "OSGPhysicsJoint.h"
#include "ODE/OSGPhysicsBody.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsJoint::onCreate(const PhysicsJoint *)
{
	//will be created in subclasses
}

void PhysicsJoint::onDestroy()
{
	if(_JointID)
    {
        //dJointDestroy(_JointID);
        _JointID = 0;
    }
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
dJointID PhysicsJoint::getJointID()
{
    return _JointID;
}

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsJoint::setJointID(const dJointID &value)
{
    _JointID = value;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/

void PhysicsJoint::setData( void* someData)
{
	dJointSetData(_JointID, someData);
}

void* PhysicsJoint::getData( void)
{
	return dJointGetData(_JointID);
}

Int32 PhysicsJoint::getJointType(void)
{
	return dJointGetType(_JointID);
}

dBodyID PhysicsJoint::getBody( Int32 i)
{
	return dJointGetBody(_JointID, i);
}

void PhysicsJoint::setFeedback( dJointFeedback* feed)
{
	dJointSetFeedback(_JointID, feed);
}

dJointFeedback* PhysicsJoint::getFeedback( void)
{
	return dJointGetFeedback(_JointID);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsJoint::PhysicsJoint(void) :
    Inherited(),
        _JointID(NULL)
{
}

PhysicsJoint::PhysicsJoint(const PhysicsJoint &source) :
    Inherited(source),
        _JointID(NULL)
{
}

PhysicsJoint::~PhysicsJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(((whichField & FirstBodyFieldMask) || (whichField & WorldFieldMask)) ||
       ((whichField & SecondBodyFieldMask) || (whichField & WorldFieldMask)))
    {
        dBodyID First(NULL);
        dBodyID Second(NULL);
        if(getFirstBody() != NullFC)
        {
            First = getFirstBody()->getBodyID();
        }
        if(getSecondBody() != NullFC)
        {
            Second = getSecondBody()->getBodyID();
        }
        dJointAttach(_JointID, First, Second);
    }
}

void PhysicsJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsJoint NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs _JointID's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

