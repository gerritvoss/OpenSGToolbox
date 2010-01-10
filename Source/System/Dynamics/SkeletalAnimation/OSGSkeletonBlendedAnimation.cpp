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

#include "OSGSkeletonBlendedAnimation.h"
#include "OSGInterpolations.h"

#include "OSGSkeletonBlendedAnimation.h"
#include "OSGJoint.h"
#include "OSGSkeleton.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonBlendedAnimationBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonBlendedAnimation.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonBlendedAnimation::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 SkeletonBlendedAnimation::getCycleLength(void) const
{
    return -1;
}

void SkeletonBlendedAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	if(getMFSkeletonAnimations()->size() == getMFBlendAmounts()->size())
	{
		//Get scaled transformations and add them together
		std::vector<std::map<unsigned long, Matrix> > relTransformations;  //Each map in the vector contains the rel trans matrices for skeletonAnimation[i]
		std::set<JointUnrecPtr> animatedJoints;
		for (int i(0); i < getMFSkeletonAnimations()->size(); ++i)
		{
			relTransformations.push_back(getSkeletonAnimations(i)->getRelTransformations(t, prev_t, animatedJoints));
		}

		//Apply the transformations to the joints
		std::set<JointUnrecPtr>::iterator iter;
		for (iter = animatedJoints.begin(); iter != animatedJoints.end(); ++iter)
		{
			//Find all of the rel dif transformations for this joint
			//Note that i will correspond to the skeleton animation from which these rel dif trans matrices came
			//(so it we should scale them by blendAmounts[i])
			Matrix blendedRelDifTrans;
			bool firstForThisJoint = true;
			for(int i(0); i < relTransformations.size(); ++i)
			{
				int exists = relTransformations[i].count((*iter)->getId());
				if(exists)
				{
					if(getOverrideStatuses(i) && getBlendAmounts(i) != 0)
					{
						//If this skeleton animation is set to override, we don't consider any other difference transformations
						Matrix relDifTrans = (*iter)->previewRelativeDifferenceTransformation(relTransformations[i][(*iter)->getId()]);
						blendedRelDifTrans = (OSG::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
						break;
					}
					else
					{
						if(firstForThisJoint)
						{
							//Use the calculated relative difference transformation from bind pose to the transformation defined by
							//the skeleton animation
							Matrix relDifTrans = (*iter)->previewRelativeDifferenceTransformation(relTransformations[i][(*iter)->getId()]);
							blendedRelDifTrans = (OSG::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
						}
						else
						{
							//Use the difference transformation between the joint's current transformation and the transformation
							//defined by the skeleton animation
							Matrix relDifTrans = (*iter)->previewRelativeTransformation(blendedRelDifTrans);
							relDifTrans.invert();
							relDifTrans.multLeft(relTransformations[i][(*iter)->getId()]);

							blendedRelDifTrans.mult(OSG::lerp(Matrix().identity(), relDifTrans, getBlendAmounts(i)));
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

void SkeletonBlendedAnimation::addAnimationBlending(const SkeletonAnimationUnrecPtr TheSkeletonAnimation, const Real32& BlendAmount, bool Override)
{
    pushToSkeletonAnimations(TheSkeletonAnimation);
    editMFBlendAmounts()->push_back(BlendAmount);
    editMFOverrideStatuses()->push_back(Override);
}

void SkeletonBlendedAnimation::setBlendAmount(unsigned int Index, Real32 BlendAmount)
{
    editBlendAmounts(Index) = BlendAmount;
}

bool SkeletonBlendedAnimation::getOverrideStatus(unsigned int Index)
{
    return getOverrideStatuses(Index);
}

void SkeletonBlendedAnimation::setOverrideStatus(unsigned int Index, bool Override)
{
    (*editMFOverrideStatuses())[Index] = Override;
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

void SkeletonBlendedAnimation::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SkeletonBlendedAnimation::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonBlendedAnimation NI" << std::endl;
}

OSG_END_NAMESPACE
