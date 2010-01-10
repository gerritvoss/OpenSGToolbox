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

#include "OSGSkeletonAnimation.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonAnimationBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonAnimation.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonAnimation::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 SkeletonAnimation::getCycleLength(void) const
{
    Real32 MaxLength(0.0f);
	
    for(UInt32 i(0) ; i<getMFTransformationAnimators()->size() ; ++i)
	{
        MaxLength = osgMax(MaxLength,getTransformationAnimators(i)->getLength());
    }

    return MaxLength;
}

std::map<unsigned long, Matrix> SkeletonAnimation::getRelTransformations(const Real32& t, const Real32& prev_t, std::set<JointUnrecPtr>& AnimatedJoints)
{
	std::map<unsigned long, Matrix> relTransformations;
	for(UInt32 i(0); i < getMFTransformationAnimators()->size(); ++i)
	{
	   
	   if( getTransformationAnimators(i)->animate(
				   getInterpolationType(), 
				   Animator::OVERWRITE,
				   -1, 
				   t,
				   prev_t,
				   getAnimatorJoints(i)->editField( Joint::RelativeTransformationFieldId )) )
	   {
	   }

	   relTransformations[getAnimatorJoints(i)->getId()] = getAnimatorJoints(i)->getRelativeTransformation();
	   AnimatedJoints.insert(getAnimatorJoints(i));
	}

	return relTransformations;
}

void SkeletonAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	//Apply all of the Transformation Animators
	for(UInt32 i(0) ; i<getMFTransformationAnimators()->size() ; ++i)
	{
		//UInt32 TransformationFieldId = Joint::getClassType().findFieldDescription("Transformation")->getFieldId();
	   
	   if( getTransformationAnimators(i)->animate(
				   getInterpolationType(), 
				   Animator::OVERWRITE,
				   -1, 
				   t,
				   prev_t,
				   getAnimatorJoints(i)->editField( Joint::RelativeTransformationFieldId )) )
	   {
	   }
	}

    if(getSkeleton() != NULL)
    {
        getSkeleton()->updateJointTransformations();
    }
}

void SkeletonAnimation::addTransformationAnimator(KeyframeAnimatorUnrecPtr TheAnimator, JointUnrecPtr TheJoint)
{
	if(TheAnimator != NULL && TheJoint != NULL && 
        TheAnimator->getDataType() == FieldTraits<Matrix>::getType())
	{
        pushToTransformationAnimators(TheAnimator);
        pushToAnimatorJoints(TheJoint);
	}
	else
	{
		SWARNING << "SkeletonAnimation::addTransformationAnimator(): could not add Animator, because it animates "
                 << TheAnimator->getDataType().getCName() << " data types.  Expecting an animator that animated Matrix data types." << std::endl;
	}
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonAnimation::SkeletonAnimation(void) :
    Inherited()
{
}

SkeletonAnimation::SkeletonAnimation(const SkeletonAnimation &source) :
    Inherited(source)
{
}

SkeletonAnimation::~SkeletonAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonAnimation::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SkeletonAnimation::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonAnimation NI" << std::endl;
}

OSG_END_NAMESPACE
