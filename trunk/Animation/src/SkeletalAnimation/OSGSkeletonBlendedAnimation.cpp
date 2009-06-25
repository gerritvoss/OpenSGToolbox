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

#include "OSGSkeletonBlendedAnimation.h"
#include "OSGSkeletonAnimation.h"
#include "OSGJoint.h"

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
		std::vector<std::map<unsigned long, Matrix>> relDifTransformations;  //Each map in the vector contains the rel dif trans matrices for skeletonAnimation[i]
		std::set<JointPtr> animatedJoints;
		for (int i(0); i < getSkeletonAnimations().size(); ++i)
		{
			relDifTransformations.push_back(getSkeletonAnimations(i)->getRelDifTransformations(t, prev_t, animatedJoints));


			////Add temp values to scaledTransformations
			//std::map<unsigned long, Matrix>::iterator iter;
			//for(iter = temp.begin(); iter != temp.end(); ++iter)
			//{
			//	scaledTransformations[iter->first].add(iter->second);
			//}

			//if(scaledTransformations.size() == temp.size())
			//{
			//	//Add temps values to scaledTransformations
			//	for(int i(0); i < temp.size(); ++i)
			//	{
			//		scaledTransformations[i].add(temp[i]);
			//	}
			//}
		}

		//Apply the transformations to the joints
		std::set<JointPtr>::iterator iter;
		for (iter = animatedJoints.begin(); iter != animatedJoints.end(); ++iter)
		{
			//Find all of the rel dif transformations for this joint
			//Note that i will correspond to the skeleton animation from which these rel dif trans matrices came
			//(so it we should scale them by blendAmounts[i])
			Matrix blendedRelDifTrans;
			for(int i(0); i < relDifTransformations.size(); ++i)
			{
				int exists = relDifTransformations[i].count(iter->getFieldContainerId());
				if(exists)
				{
					Matrix scaledRelDifTrans = relDifTransformations[i][iter->getFieldContainerId()];
					blendedRelDifTrans.mult(osg::lerp(Matrix().identity(), scaledRelDifTrans, getBlendAmounts(i)));
					
					
					
					
					//scaledRelDifTrans.scale(getBlendAmounts(i));
					//blendedRelDifTrans.add(scaledRelDifTrans);

					//Real32 blend = getBlendAmounts(i);
					//int stop = 1;


					////This joint is animated by skeletonAnimations[i]
					//Matrix bindRelTrans = (*iter)->getBindRelativeTransformation();
					//Matrix relativeDifferenceMat = relDifTransformations[i][iter->getFieldContainerId()];

					//relativeDifferenceMat.scale(getBlendAmounts(i));
					//bindRelTrans.mult(relativeDifferenceMat);

					//(*iter)->getRelativeTransformation().add(bindRelTrans);
				}
			}
			//Matrix zero = (*iter)->getBindRelativeTransformation();
			//zero.scale(0);
			blendedRelDifTrans.mult((*iter)->getBindRelativeTransformation());
			(*iter)->setRelativeTransformation(blendedRelDifTrans);

			Matrix m = (*iter)->getRelativeTransformation();

			(*iter)->updateTransformations(false);

		}
		/*for (int i(0); i < getSkeletonAnimations().size(); ++i)
		{
			getSkeletonAnimations(i)->internalBlendUpdate(scaledTransformations);
		}*/
	}
}

void SkeletonBlendedAnimation::addAnimationBlending(const SkeletonAnimationPtr TheSkeletonAnimation, const Real32& BlendAmount)
{
	beginEditCP(SkeletonBlendedAnimationPtr(this), SkeletonAnimationsFieldMask | BlendAmountsFieldMask);
		getSkeletonAnimations().push_back(TheSkeletonAnimation);
		getBlendAmounts().push_back(BlendAmount);
	endEditCP(SkeletonBlendedAnimationPtr(this), SkeletonAnimationsFieldMask | BlendAmountsFieldMask);
}

void SkeletonBlendedAnimation::setBlendAmount(unsigned int Index, Real32 BlendAmount)
{
	beginEditCP(SkeletonBlendedAnimationPtr(this), BlendAmountsFieldMask);
		getBlendAmounts(Index) = BlendAmount;
	endEditCP(SkeletonBlendedAnimationPtr(this), BlendAmountsFieldMask);
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

