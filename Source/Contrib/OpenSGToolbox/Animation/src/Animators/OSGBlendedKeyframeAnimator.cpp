/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#include "OSGBlendedKeyframeAnimator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BlendedKeyframeAnimator
Keyframe Animator Class.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BlendedKeyframeAnimator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool BlendedKeyframeAnimator::animate(const osg::InterpolationType& InterpType,
           const osg::ValueReplacementPolicy& ReplacementPolicy,
           bool Cycling,
           const osg::Real32& time,
           const osg::Real32& prevTime,
           osg::Field& Result,
           UInt32 Index)
{
    if( getKeyframeSequences().size() != 0)
    {
        ValueReplacementPolicy BlendRepPol;
        if(ReplacementPolicy == OVERWRITE)
        {
            //Zero out the value of the Field
            getKeyframeSequences().front()->zeroField(Result, Index);
            BlendRepPol = ADDITIVE_ABSOLUTE;
        }
        else
        {
            BlendRepPol = ReplacementPolicy;
        }
        bool RetValue(true);
        for(UInt32 i(0) ; i< getKeyframeSequences().size() ; ++i)
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
    if(getKeyframeSequences().size() > 0 && checkSequencesValidity())
    {
        Real32 MaxLength(0.0f);
        for(UInt32 i(0) ; i< getKeyframeSequences().size() ; ++i)
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

const DataType &BlendedKeyframeAnimator::getDataType(void) const
{
   if( getKeyframeSequences().size() != 0)
   {
       return getKeyframeSequences().front()->getDataType();
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

bool BlendedKeyframeAnimator::checkSequencesValidity(void) const
{
    //Check that the sizes are the same
    if(getKeyframeSequences().size() != getBlendAmounts().size())
    {
        SWARNING << "BlendedKeyframeAnimator: The number of keyframe sequences and blend amounts must be the same."  << std::endl;
        return false;
    }

    //Check that the types of the KeyframeSequences are all the same
    if(getKeyframeSequences().size() > 0)
    {
        const DataType &FrontDataType(getKeyframeSequences().front()->getDataType());
        for(UInt32 i(1) ; i< getKeyframeSequences().size() ; ++i)
        {
            if(FrontDataType != getKeyframeSequences()[i]->getDataType())
            {
                SWARNING << "BlendedKeyframeAnimator: All of the KeyframeSequences attached to a BlenededKeyframeAnimator must work on the same data type."  << std::endl;
                return false;
            }
        }
        if(!getKeyframeSequences().front()->isBlendable())
        {
            SWARNING << "BlendedKeyframeAnimator: Cannot create a blended animation for a KeyframeSequence of type: " << getKeyframeSequences().front()->getType().getCName() << "."  << std::endl;
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

void BlendedKeyframeAnimator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & KeyframeSequencesFieldMask) || (whichField & BlendAmountsFieldMask))
    {
        checkSequencesValidity();
    }
}

void BlendedKeyframeAnimator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BlendedKeyframeAnimator NI" << std::endl;
}


OSG_END_NAMESPACE

