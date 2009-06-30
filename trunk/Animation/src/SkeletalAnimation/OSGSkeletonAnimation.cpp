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
#include <OpenSG/OSGSimpleAttachments.h>

#include "OSGSkeletonAnimation.h"

#include "OSGJoint.h"
#include "OSGSkeleton.h"
#include "Animators/OSGKeyframeAnimator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SkeletonAnimation
Field Animation Class. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonAnimation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 SkeletonAnimation::getLength(void) const
{
    Real32 MaxLength(0.0f);
	
    for(UInt32 i(0) ; i<getTransformationAnimators().size() ; ++i)
	{
        MaxLength = osgMax(MaxLength,getTransformationAnimators()[i]->getLength());
    }

    return MaxLength;
}

std::map<unsigned long, Matrix> SkeletonAnimation::getRelTransformations(const Real32& t, const Real32& prev_t, std::set<JointPtr>& AnimatedJoints)
{
	std::map<unsigned long, Matrix> relTransformations;
	for(UInt32 i(0); i < getTransformationAnimators().size(); ++i)
	{
	   osg::beginEditCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask() );
	   
	   if( getTransformationAnimators(i)->animate(
				   static_cast<osg::InterpolationType>(getInterpolationType()), 
				   static_cast<osg::ValueReplacementPolicy>(OVERWRITE),
				   -1, 
				   t,
				   prev_t,
				   *getAnimatorJoints(i)->getField( Joint::RelativeTransformationFieldId )) )
	   {
		   osg::endEditNotChangedCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask());
	   }
	   else
	   {
		  osg::endEditNotChangedCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask());
	   }

	   relTransformations[getAnimatorJoints(i).getFieldContainerId()] = getAnimatorJoints(i)->getRelativeTransformation();
	   AnimatedJoints.insert(getAnimatorJoints(i));
	}

	return relTransformations;
}

void SkeletonAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	std::cout << "SkeletonAnimation: internalUpdate" << std::endl;

	//Apply all of the Transformation Animators
	for(UInt32 i(0) ; i<getTransformationAnimators().size() ; ++i)
	{
		//UInt32 TransformationFieldId = Joint::getClassType().findFieldDescription("Transformation")->getFieldId();
	   osg::beginEditCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask() );
	   
	   if( getTransformationAnimators(i)->animate(
				   static_cast<osg::InterpolationType>(getInterpolationType()), 
				   static_cast<osg::ValueReplacementPolicy>(OVERWRITE),
				   -1, 
				   t,
				   prev_t,
				   *getAnimatorJoints(i)->getField( Joint::RelativeTransformationFieldId )) )
	   {
		   //std::cout << "Change " << i << std::endl;
		  osg::endEditNotChangedCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask());
	   }
	   else
	   {
		   //std::cout << "No Change" << i << std::endl;
		  osg::endEditNotChangedCP(getAnimatorJoints(i), getAnimatorJoints(i)->getType().getFieldDescription(Joint::RelativeTransformationFieldId)->getFieldMask());
	   }
	}

    if(getSkeleton() != NullFC)
    {
        getSkeleton()->updateJointTransformations();
        //getSkeleton()->skeletonUpdated();
    }
}


//===============================================================================================================
// END HERE
//================================================================================================================
void SkeletonAnimation::addTransformationAnimator(KeyframeAnimatorPtr TheAnimator, JointPtr TheJoint)
{
	if(TheAnimator != NullFC && TheJoint != NullFC && 
        TheAnimator->getDataType() == FieldDataTraits<Matrix>::getType())
	{
		beginEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::TransformationAnimatorsFieldMask | SkeletonAnimation::AnimatorJointsFieldMask);
			getTransformationAnimators().push_back(TheAnimator);
			getAnimatorJoints().push_back(TheJoint);
		endEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::TransformationAnimatorsFieldMask | SkeletonAnimation::AnimatorJointsFieldMask);
	}
	else
	{
		SWARNING << "SkeletonAnimation::addTransformationAnimator: could not add Animator" << std::endl;
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

void SkeletonAnimation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SkeletonAnimation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SkeletonAnimation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSKELETONANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSKELETONANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSKELETONANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

