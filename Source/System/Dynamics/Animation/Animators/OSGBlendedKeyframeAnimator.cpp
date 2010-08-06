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

#include "OSGBlendedKeyframeAnimator.h"
#include "OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBlendedKeyframeAnimatorBase.cpp file.
// To modify it, please change the .fcd file (OSGBlendedKeyframeAnimator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BlendedKeyframeAnimator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool BlendedKeyframeAnimator::animate(UInt32 InterpType,
                         UInt32 ReplacementPolicy,
                                      bool Cycling,
                                      Real32 time,
                                      Real32 prevTime,
                                      EditFieldHandlePtr Result,
                                      UInt32 Index)
{
    if( getMFKeyframeSequences()->size() != 0)
    {
        ValueReplacementPolicy BlendRepPol;
        if(ReplacementPolicy == OVERWRITE)
        {
            //Zero out the value of the Field
            getMFKeyframeSequences()->front()->zeroField(Result, Index);
            BlendRepPol = ADDITIVE_ABSOLUTE;
        }
        else
        {
            BlendRepPol = static_cast<ValueReplacementPolicy>(ReplacementPolicy);
        }
        bool RetValue(true);
        for(UInt32 i(0) ; i< getMFKeyframeSequences()->size() ; ++i)
        {
            RetValue = RetValue && getKeyframeSequences(i)->interpolate(InterpType, time, prevTime, BlendRepPol, Cycling, Result, Index, getBlendAmounts(i));
        }
        return RetValue;
    }
    else
    {
        return false;
    }
}
    
Real32 BlendedKeyframeAnimator::getLength(void) const
{
    if(getMFKeyframeSequences()->size() > 0 && checkSequencesValidity())
    {
        Real32 MaxLength(0.0f);
        for(UInt32 i(0) ; i< getMFKeyframeSequences()->size() ; ++i)
        {
            MaxLength = osgMax(MaxLength, getKeyframeSequences(i)->getKeys().back());
        }
        return MaxLength;
    }
    else
    {
        return 0.0f;
    }
}

const DataType* BlendedKeyframeAnimator::getDataType(void) const
{
   if( getMFKeyframeSequences()->size() != 0)
   {
       return getMFKeyframeSequences()->front()->getDataType();
   }
   else
   {
       return NULL;
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

bool BlendedKeyframeAnimator::checkSequencesValidity(void) const
{
    //Check that the sizes are the same
    if(getMFKeyframeSequences()->size() != getMFBlendAmounts()->size())
    {
        SWARNING << "BlendedKeyframeAnimator: The number of keyframe sequences and blend amounts must be the same."  << std::endl;
        return false;
    }

    //Check that the types of the KeyframeSequences are all the same
    if(getMFKeyframeSequences()->size() > 0)
    {
        const DataType &FrontDataType(*getMFKeyframeSequences()->front()->getDataType());
        for(UInt32 i(1) ; i< getMFKeyframeSequences()->size() ; ++i)
        {
            if(FrontDataType != *getKeyframeSequences(i)->getDataType())
            {
                SWARNING << "BlendedKeyframeAnimator: All of the KeyframeSequences attached to a BlenededKeyframeAnimator must work on the same data type."  << std::endl;
                return false;
            }
        }
        if(!getMFKeyframeSequences()->front()->isBlendable())
        {
            SWARNING << "BlendedKeyframeAnimator: Cannot create a blended animation for a KeyframeSequence of type: " << getMFKeyframeSequences()->front()->getType().getCName() << "."  << std::endl;
            return false;
        }
    }

    return true;
}

/*----------------------- constructors & destructors ----------------------*/

BlendedKeyframeAnimator::BlendedKeyframeAnimator(void) :
    Inherited()
{
}

BlendedKeyframeAnimator::BlendedKeyframeAnimator(const BlendedKeyframeAnimator &source) :
    Inherited(source)
{
}

BlendedKeyframeAnimator::~BlendedKeyframeAnimator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BlendedKeyframeAnimator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BlendedKeyframeAnimator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BlendedKeyframeAnimator NI" << std::endl;
}

OSG_END_NAMESPACE
