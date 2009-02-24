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

#include "OSGSkeletonAnimation.h"

#include "OSGBone.h"
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
	
    for(UInt32 i(0) ; i<getRotationAnimators().size() ; ++i)
	{
        MaxLength = osgMax(MaxLength,getRotationAnimators()[i]->getLength());
    }
    for(UInt32 i(0) ; i<getTranslationAnimators().size() ; ++i)
	{
        MaxLength = osgMax(MaxLength,getTranslationAnimators()[i]->getLength());
    }
    for(UInt32 i(0) ; i<getLengthAnimators().size() ; ++i)
	{
        MaxLength = osgMax(MaxLength,getLengthAnimators()[i]->getLength());
    }

    return MaxLength;
}

void SkeletonAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	//Apply all of the Rotation Animators
	for(UInt32 i(0) ; i<getRotationAnimators().size() ; ++i)
	{
		UInt32 RotationFieldId = Bone::getClassType().findFieldDescription("Rotation")->getFieldId();
	   osg::beginEditCP(getRotationAnimatorBones(i), getRotationAnimatorBones(i)->getType().getFieldDescription(RotationFieldId)->getFieldMask() );
	   
	   if( getRotationAnimators(i)->animate(
				   static_cast<osg::InterpolationType>(getInterpolationType()), 
				   static_cast<osg::ValueReplacementPolicy>(OVERWRITE),
				   -1, 
				   t,
				   prev_t,
				   *getRotationAnimatorBones(i)->getField( RotationFieldId )) )
	   {
		  osg::endEditCP(getRotationAnimatorBones(i), getRotationAnimatorBones(i)->getType().getFieldDescription(RotationFieldId)->getFieldMask());
	   }
	   else
	   {
		  osg::endEditNotChangedCP(getRotationAnimatorBones(i), getRotationAnimatorBones(i)->getType().getFieldDescription(RotationFieldId)->getFieldMask());
	   }
	}


    //==================================================================================================================
    //Apply all of the Length Animators
    //==================================================================================================================
	for(UInt32 i(0) ; i<getLengthAnimators().size() ; ++i)
	{
		UInt32 LengthFieldId = Bone::getClassType().findFieldDescription("Length")->getFieldId();
	   osg::beginEditCP(getLengthAnimatorBones(i), getLengthAnimatorBones(i)->getType().getFieldDescription(LengthFieldId)->getFieldMask() );
	   
	   if( getLengthAnimators(i)->animate(
				   static_cast<osg::InterpolationType>(getInterpolationType()), 
				   static_cast<osg::ValueReplacementPolicy>(OVERWRITE),
				   -1, 
				   t,
				   prev_t,
				   *getLengthAnimatorBones(i)->getField( LengthFieldId )) )
	   {
		  osg::endEditCP(getLengthAnimatorBones(i), getLengthAnimatorBones(i)->getType().getFieldDescription(LengthFieldId)->getFieldMask());
	   }
	   else
	   {
		  osg::endEditNotChangedCP(getLengthAnimatorBones(i), getLengthAnimatorBones(i)->getType().getFieldDescription(LengthFieldId)->getFieldMask());
	   }
	}

    //==================================================================================================================
    //Apply all of the Translation Animators
    //==================================================================================================================
	for(UInt32 i(0) ; i<getTranslationAnimators().size() ; ++i)
	{
		UInt32 TranslationFieldId = Bone::getClassType().findFieldDescription("Translation")->getFieldId();
	   osg::beginEditCP(getTranslationAnimatorBones(i), getTranslationAnimatorBones(i)->getType().getFieldDescription(TranslationFieldId)->getFieldMask() );
	   
	   if( getTranslationAnimators(i)->animate(
				   static_cast<osg::InterpolationType>(getInterpolationType()), 
				   static_cast<osg::ValueReplacementPolicy>(OVERWRITE),
				   -1, 
				   t,
				   prev_t,
				   *getTranslationAnimatorBones(i)->getField( TranslationFieldId )) )
	   {
		  osg::endEditCP(getTranslationAnimatorBones(i), getTranslationAnimatorBones(i)->getType().getFieldDescription(TranslationFieldId)->getFieldMask());
	   }
	   else
	   {
		  osg::endEditNotChangedCP(getTranslationAnimatorBones(i), getTranslationAnimatorBones(i)->getType().getFieldDescription(TranslationFieldId)->getFieldMask());
	   }
	}

    if(getSkeleton() != NullFC)
    {
        getSkeleton()->skeletonUpdated();
    }
}
//===============================================================================================================
// END HERE
//================================================================================================================
void SkeletonAnimation::addRotationAnimator(KeyframeAnimatorPtr TheAnimator, BonePtr TheBone)
{
	if(TheAnimator != NullFC && TheBone != NullFC && 
        TheAnimator->getDataType() == FieldDataTraits<Quaternion>::getType())
	{
		beginEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::RotationAnimatorsFieldMask | SkeletonAnimation::RotationAnimatorBonesFieldMask);
			getRotationAnimators().push_back(TheAnimator);
			getRotationAnimatorBones().push_back(TheBone);
		endEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::RotationAnimatorsFieldMask | SkeletonAnimation::RotationAnimatorBonesFieldMask);
	}
	else
	{
		SWARNING << "SkeletonAnimation::addRotationAnimator: could not add Animator" << std::endl;
	}
}


void SkeletonAnimation::addTranslationAnimator(KeyframeAnimatorPtr TheAnimator, BonePtr TheBone)
{
	if(TheAnimator != NullFC && TheBone != NullFC && 
		TheAnimator->getDataType() == FieldDataTraits<Vec3f>::getType())
	{
		beginEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::TranslationAnimatorsFieldMask | SkeletonAnimation::TranslationAnimatorBonesFieldMask);
			getTranslationAnimators().push_back(TheAnimator);
			getTranslationAnimatorBones().push_back(TheBone);
		endEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::TranslationAnimatorsFieldMask | SkeletonAnimation::TranslationAnimatorBonesFieldMask);
	}
	else
	{
		SWARNING << "SkeletonAnimation::addTranslationAnimator: could not add Animator" << std::endl;
	}
}


void SkeletonAnimation::addLengthAnimator(KeyframeAnimatorPtr TheAnimator, BonePtr TheBone)
{
	if(TheAnimator != NullFC && TheBone != NullFC && 
		TheAnimator->getDataType() == FieldDataTraits<Real32>::getType())
	{
		beginEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::LengthAnimatorsFieldMask | SkeletonAnimation::LengthAnimatorBonesFieldMask);
			getLengthAnimators().push_back(TheAnimator);
			getLengthAnimatorBones().push_back(TheBone);
		endEditCP(SkeletonAnimationPtr(this), SkeletonAnimation::LengthAnimatorsFieldMask | SkeletonAnimation::LengthAnimatorBonesFieldMask);
	}
	else
	{
		SWARNING << "SkeletonAnimation::addLengthAnimator: could not add Animator" << std::endl;
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

