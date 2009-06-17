/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, John Morales                     *
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

#define OSG_COMPILEANIMATIONLIB

#include <OpenSG/OSGConfig.h>

#include "OSGSkeleton.h"
#include "OSGSkeletonBlendedGeometry.h"

#include "OSGJoint.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Skeleton

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Skeleton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Skeleton::skeletonUpdated(void)
{
	produceChangedEvent();
}

void Skeleton::updateJointTransformations(void)
{
	//Loop through bone hierarchy and update their transformations
	for(UInt32 i(0); i < getRootJoints().size(); ++i)
	{
		getRootJoints(i)->updateTransformations(false);
	}
}


EventConnection Skeleton::addSkeletonListener(SkeletonListenerPtr Listener)
{
   _SkeletonListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Skeleton::isSkeletonListenerAttached, this, Listener),
       boost::bind(&Skeleton::removeSkeletonListener, this, Listener));
}


void Skeleton::removeSkeletonListener(SkeletonListenerPtr Listener)
{
   SkeletonListenerSetItor EraseIter(_SkeletonListeners.find(Listener));
   if(EraseIter != _SkeletonListeners.end())
   {
      _SkeletonListeners.erase(EraseIter);
   }
}

void Skeleton::produceChangedEvent(void)
{
	SkeletonEvent TheEvent( SkeletonPtr(this), getTimeStamp(), SkeletonPtr(this));

	SkeletonListenerSet ListenerSet(_SkeletonListeners);
	for(SkeletonListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
	{
	   (*SetItor)->changed(TheEvent);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Skeleton::Skeleton(void) :
    Inherited()
{
}

Skeleton::Skeleton(const Skeleton &source) :
    Inherited(source)
{
}

Skeleton::~Skeleton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Skeleton::setJointParentSkeleton(JointPtr theJoint)
{
	beginEditCP(theJoint, Joint::ParentSkeletonFieldMask);
		theJoint->setParentSkeleton(SkeletonPtr(this));
	endEditCP(theJoint, Joint::ParentSkeletonFieldMask);


	for (UInt32 i(0); i < theJoint->getChildJoints().size() ; ++i)
	{
		setJointParentSkeleton(theJoint->getChildJoints(i));
	}
}

void Skeleton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & RootJointsFieldMask)
	{
		//Loop through bone hierarchy and set their parent Skeleton this instance
		MFJointPtr CurrentJoints = getRootJoints();
		for(UInt32 i(0); i < CurrentJoints.size(); ++i)
		{
			setJointParentSkeleton(CurrentJoints[i]);
		}
	}
}

void Skeleton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Skeleton NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSKELETONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSKELETONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSKELETONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

