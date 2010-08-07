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

#include "OSGConfig.h"

#include "OSGSkeletonDrawable.h"

#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGMaterial.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"

#include "OSGDrawableStatsAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonDrawableBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonDrawable.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonDrawable::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SkeletonDrawable::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            SkeletonDrawable::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionLeaveHandler));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SkeletonDrawable::drawPrimitives (DrawEnv *pEnv)
{
    if(getSkeleton() == NULL)
    {
        FWARNING(("SkeletonDrawable::drawPrimitives:: no skeleton!\n"));;
    }
    else
    {

        Pnt3f BoneStart(0.0,0.0,0.0),BoneEnd(0.0,0.0,0.0);
        Int32 ParentIndex;
        glBegin(GL_LINES);
            for(UInt32 i(0) ; i<getSkeleton()->getNumJoints() ; ++i)
            {
                //Draw all Root Joints of Skeleton
                ParentIndex = getSkeleton()->getJointParentIndex(i);
                if(ParentIndex >= 0)
                {
                    if(getDrawPose())
                    {
                        BoneStart.setValues(0.0,0.0,0.0);
                        BoneEnd.setValues(0.0,0.0,0.0);
                        getSkeleton()->getAbsoluteTransformation(i).mult(BoneEnd,BoneEnd);
                        getSkeleton()->getAbsoluteTransformation(ParentIndex).mult(BoneStart,BoneStart);
                        glColor4fv(getPoseColor().getValuesRGBA());
                        glVertex3fv(BoneStart.getValues());
                        glVertex3fv(BoneEnd.getValues());
                    }
                    if(getDrawBindPose())
                    {
                        BoneStart.setValues(0.0f,0.0f,0.0f);
                        BoneEnd.setValues(0.0f,0.0f,0.0f);
                        getSkeleton()->getAbsoluteBindTransformation(i).mult(BoneEnd,BoneEnd);
                        getSkeleton()->getAbsoluteBindTransformation(ParentIndex).mult(BoneStart,BoneStart);
                        glColor4fv(getBindPoseColor().getValuesRGBA());
                        glVertex3fv(BoneStart.getValues());
                        glVertex3fv(BoneEnd.getValues());
                    }
                }
            }
        glEnd();
    }
}

void SkeletonDrawable::adjustVolume(Volume & volume)
{
	Inherited::adjustVolume(volume);

	//Extend the volume by all the Root Joints of Skeleton
    if(getSkeleton() == NULL)
    {
        FWARNING(("SkeletonDrawable::drawPrimitives:: no skeleton!\n"));;
    }
    else
    {
        Pnt3f JointLocation(0.0,0.0,0.0);
		for(UInt32 i(0) ; i<getSkeleton()->getNumJoints() ; ++i)
		{
            JointLocation.setValues(0.0,0.0,0.0);
            if(getDrawPose())
            {
                getSkeleton()->getAbsoluteTransformation(i).mult(Pnt3f(0.0f,0.0f,0.0f),JointLocation);
                volume.extendBy(JointLocation);
            }
            if(getDrawBindPose())
            {
                getSkeleton()->getAbsoluteBindTransformation(i).mult(Pnt3f(0.0f,0.0f,0.0f),JointLocation);
                volume.extendBy(JointLocation);
            }
		}
	}

}

void SkeletonDrawable::fill(DrawableStatsAttachment *pStat)
{
    if(pStat == NULL)
    {
        FINFO(("SkeletonDrawable::fill(DrawableStatsAttachment *): "
                          "No attachment given.\n"));
        return;
    }
    if(getSkeleton() == NULL)
    {
        FWARNING(("SkeletonDrawable::fill:: no skeleton!\n"));;
        return;
    }

    UInt32 NumLines(0);
    if(getDrawPose())
    {
        NumLines += getSkeleton()->getNumJoints()-1;
    }
    if(getDrawBindPose())
    {
        NumLines += getSkeleton()->getNumJoints()-1;
    }
    pStat->setLines    (NumLines);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonDrawable::SkeletonDrawable(void) :
    Inherited()
{
}

SkeletonDrawable::SkeletonDrawable(const SkeletonDrawable &source) :
    Inherited(source)
{
}

SkeletonDrawable::~SkeletonDrawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonDrawable::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if((whichField & DrawBindPoseFieldMask) || (whichField & DrawPoseFieldMask) || (whichField & SkeletonFieldMask))
	{
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }
	}
}

void SkeletonDrawable::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonDrawable NI" << std::endl;
}

OSG_END_NAMESPACE
