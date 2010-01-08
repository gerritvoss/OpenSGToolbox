/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#include "OSGJoint.h"
#include "OSGSkeleton.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeleton.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Skeleton::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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
	for(UInt32 i(0); i < getMFRootJoints()->size(); ++i)
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
	const SkeletonEventUnrecPtr TheEvent = SkeletonEvent::create( SkeletonUnrecPtr(this), getTimeStamp());

	SkeletonListenerSet ListenerSet(_SkeletonListeners);
	for(SkeletonListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
	{
	   (*SetItor)->skeletonChanged(TheEvent);
	}
    _Producer.produceEvent(SkeletonChangedMethodId,TheEvent);
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

void Skeleton::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & RootJointsFieldMask)
	{
		//Loop through bone hierarchy and set their parent Skeleton to this instance
        for (UInt32 i(0); i < getMFRootJoints()->size() ; ++i)
		{
			setJointParentSkeleton(getRootJoints(i));
		}
	}
}

void Skeleton::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Skeleton NI" << std::endl;
}

void Skeleton::setJointParentSkeleton(JointUnrecPtr theJoint)
{
    theJoint->setParentSkeleton(this);


	for (UInt32 i(0); i < theJoint->getMFChildJoints()->size() ; ++i)
	{
		setJointParentSkeleton(theJoint->getChildJoints(i));
	}
}

OSG_END_NAMESPACE
