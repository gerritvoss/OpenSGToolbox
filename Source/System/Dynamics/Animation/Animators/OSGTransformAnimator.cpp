/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGTransformAnimator.h"
#include "OSGMathFieldTraits.h"
#include "OSGMathFields.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTransformAnimatorBase.cpp file.
// To modify it, please change the .fcd file (OSGTransformAnimator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TransformAnimator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool TransformAnimator::animate(UInt32 InterpType,
                                UInt32 ReplacementPolicy,
                                bool Cycling,
                                Real32 time,
                                Real32 prevTime,
                                EditFieldHandlePtr Result,
                                UInt32 Index)
{
    Matrix MatResult;
    if(Result->getCardinality() == FieldType::SingleField)
    {
        MatResult = static_cast<SFMatrix&>(*Result->getField()).getValue();
    }
    else
    {
        MatResult =  static_cast<MFMatrix&>(*Result->getField())[Index];
    }


    Vec3f Translation, ScaleMagnitude;
    Quaternion Rotation,ScaleOrientation;
    MatResult.getTransform(Translation,Rotation,ScaleMagnitude,ScaleOrientation);

    //Tranlations
	if(getTranslationSequence() != NULL)
	{
		getTranslationSequence()->interpolate(  InterpType, time, prevTime,
												ReplacementPolicy, Cycling,
												Translation, 1.0f);
	}
	else
	{
		if( getXTranslationSequence() != NULL)
		{
			getXTranslationSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   Translation[0], 1.0f);
		}
		if( getYTranslationSequence() != NULL)
		{
			getYTranslationSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   Translation[1], 1.0f);
		}
		if( getZTranslationSequence() != NULL)
		{
			getZTranslationSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   Translation[2], 1.0f);
		}
	}


    //Rotations
    if( getXRotationSequence() ||
        getYRotationSequence() ||
        getZRotationSequence())
    {
        Vec3f EulerRot;
        Rotation.getEulerAngleDeg(EulerRot);
        if( getXRotationSequence() != NULL)
        {
            getXRotationSequence()->interpolate(InterpType, time, prevTime,
                                                ReplacementPolicy, Cycling,
                                                EulerRot[0], 1.0f);
        }
        if( getYRotationSequence() != NULL)
        {
            getYRotationSequence()->interpolate(InterpType, time, prevTime,
                                                ReplacementPolicy, Cycling,
                                                EulerRot[1], 1.0f);
        }
        if( getZRotationSequence() != NULL)
        {
            getZRotationSequence()->interpolate(InterpType, time, prevTime,
                                                ReplacementPolicy, Cycling,
                                                EulerRot[2], 1.0f);
        }
        Rotation.setValue(osgDegree2Rad(EulerRot.x()),
                          osgDegree2Rad(EulerRot.y()),
                          osgDegree2Rad(EulerRot.z()));
    }
    //Scales
	if(getScaleSequence() != NULL)
	{
		getScaleSequence()->interpolate(InterpType, time, prevTime,
										ReplacementPolicy, Cycling,
										ScaleMagnitude, 1.0f);
	}
	else
	{
		if( getXScaleSequence() != NULL)
		{
			getXScaleSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   ScaleMagnitude[0], 1.0f);
		}
		if( getYScaleSequence() != NULL)
		{
			getYScaleSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   ScaleMagnitude[1], 1.0f);
		}
		if( getZScaleSequence() != NULL)
		{
			getZScaleSequence()->interpolate(InterpType, time, prevTime,
												   ReplacementPolicy, Cycling,
												   ScaleMagnitude[2], 1.0f);
		}
	}

    MatResult.setTransform(Translation,Rotation,ScaleMagnitude);

    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFMatrix&>(*Result->getField()).setValue(MatResult);
    }
    else
    {
        static_cast<MFMatrix&>(*Result->getField())[Index] = MatResult;
    }
    return true;
}

Real32 TransformAnimator::getLength(void) const
{
    //if(getKeyframeSequence()->size() > 0)
    //{
    //return getKeyframeSequence()->getKeys().back();
    //}
    //else
    //{
    return 0.0f;
    //}
}

const DataType* TransformAnimator::getDataType(void) const
{
    return &FieldTraits<Matrix>::getType();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TransformAnimator::TransformAnimator(void) :
    Inherited()
{
}

TransformAnimator::TransformAnimator(const TransformAnimator &source) :
    Inherited(source)
{
}

TransformAnimator::~TransformAnimator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TransformAnimator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TransformAnimator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TransformAnimator NI" << std::endl;
}

OSG_END_NAMESPACE
