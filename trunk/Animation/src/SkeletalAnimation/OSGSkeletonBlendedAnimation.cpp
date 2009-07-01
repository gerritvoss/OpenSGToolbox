/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
#include <OpenSG/Toolbox/OSGInterpolations.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include "OSGSkeletonBlendedAnimation.h"
#include "OSGSkeletonAnimation.h"
#include "OSGJoint.h"
#include "OSGSkeleton.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SkeletonBlendedAnimation

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonBlendedAnimation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 SkeletonBlendedAnimation::getLength(void) const
{
    return -1;
}

void SkeletonBlendedAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	if(getSkeletonAnimations().size() == getBlendAmounts().size())
	{
		//Get scaled transformations and add them together
		std::vector<std::map<unsigned long, Matrix> > relTransformations;  //Each map in the vector contains the rel trans matrices for skeletonAnimation[i]
		std::set<JointPtr> animatedJoints;
		for (int i(0); i < getSkeletonAnimations().size(); ++i)
		{
			relTransformations.push_back(getSkeletonAnimations(i)->getRelTransformations(t, prev_t, animatedJoints));
		}

		//Apply the transformations to the joints
		std::set<JointPtr>::iterator iter;
		for (iter = animatedJoints.begin(); iter != animatedJoints.end(); ++iter)
		{
			//Find all of the rel dif transformations for this joint
			//Note that i will correspond to the skeleton animation from which these rel dif trans matrices came
			//(so it we should scale them by blendAmounts[i])
			Matrix blendedRelDifTrans;
			bool firstForThisJoint = true;
			for(int i(0); i < relTransformations.size(); ++i)
			{
				int exists = relTransformations[i].count(iter->getFieldContainerId());
				if(exists)
				{
					if(getOverrideStatuses(i) && getBlendAmounts(i) != 0)
					{
						//If this skeleton animation is set to override, we don't consider any other difference transformations
						Matrix relDifTrans = (*iter)->previewRelativeDifferenceTransformation(relTransformations[i][iter->getFieldContainerId()]);
						blendedRelDifTrans = (osg::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
						break;
					}
					else
					{
						if(firstForThisJoint)
						{
							//Use the calculated relative difference transformation from bind pose to the transformation defined by
							//the skeleton animation
							Matrix relDifTrans = (*iter)->previewRelativeDifferenceTransformation(relTransformations[i][iter->getFieldContainerId()]);
							blendedRelDifTrans = (osg::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
						}
						else
						{
							//Use the difference transformation between the joint's current transformation and the transformation
							//defined by the skeleton animation
							Matrix relDifTrans = (*iter)->previewRelativeTransformation(blendedRelDifTrans);
							relDifTrans.invert();
							relDifTrans.multLeft(relTransformations[i][iter->getFieldContainerId()]);

							blendedRelDifTrans.mult(osg::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
						}
					}
					if(getBlendAmounts(i) != 0)
					{
						firstForThisJoint = false;
					}
				}
			}
			blendedRelDifTrans.mult((*iter)->getBindRelativeTransformation());
			(*iter)->setRelativeTransformation(blendedRelDifTrans);

			//Update joint, but don't tell skeleton
			(*iter)->updateTransformations(false, false);

		}

		//Tell skeleton to update
		(*animatedJoints.begin())->getParentSkeleton()->skeletonUpdated();
	}
}

void SkeletonBlendedAnimation::addAnimationBlending(const SkeletonAnimationPtr TheSkeletonAnimation, const Real32& BlendAmount, bool Override)
{
	beginEditCP(SkeletonBlendedAnimationPtr(this), SkeletonAnimationsFieldMask | BlendAmountsFieldMask | OverrideStatusesFieldMask);
		getSkeletonAnimations().push_back(TheSkeletonAnimation);
		getBlendAmounts().push_back(BlendAmount);
		getOverrideStatuses().push_back(Override);
	endEditCP(SkeletonBlendedAnimationPtr(this), SkeletonAnimationsFieldMask | BlendAmountsFieldMask | OverrideStatusesFieldMask);
}

void SkeletonBlendedAnimation::setBlendAmount(unsigned int Index, Real32 BlendAmount)
{
	beginEditCP(SkeletonBlendedAnimationPtr(this), BlendAmountsFieldMask);
		getBlendAmounts(Index) = BlendAmount;
	endEditCP(SkeletonBlendedAnimationPtr(this), BlendAmountsFieldMask);
}

bool SkeletonBlendedAnimation::getOverrideStatus(unsigned int Index)
{
	return getOverrideStatuses(Index);
}

void SkeletonBlendedAnimation::setOverrideStatus(unsigned int Index, bool Override)
{
	beginEditCP(SkeletonBlendedAnimationPtr(this), OverrideStatusesFieldMask);
		getOverrideStatuses()[Index] = Override;
	endEditCP(SkeletonBlendedAnimationPtr(this), OverrideStatusesFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonBlendedAnimation::SkeletonBlendedAnimation(void) :
    Inherited()
{
}

SkeletonBlendedAnimation::SkeletonBlendedAnimation(const SkeletonBlendedAnimation &source) :
    Inherited(source)
{
}

SkeletonBlendedAnimation::~SkeletonBlendedAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonBlendedAnimation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SkeletonBlendedAnimation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SkeletonBlendedAnimation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSKELETONBLENDEDANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSKELETONBLENDEDANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSKELETONBLENDEDANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

