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

#include "OSGAnimator.h"
#include "OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeyframeSequenceBase.cpp file.
// To modify it, please change the .fcd file (OSGKeyframeSequence.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequence::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool KeyframeSequence::interpolate(const UInt32& Type, const Real32& time, const Real32& prevTime, const UInt32& ReplacePolicy, bool isCyclic, Field& Result, UInt32 Index, Real32 Blend)
{
    RawInterpFuncion InterpFunc(getRawInterpFuncion(Type));
    if(InterpFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Interpolation function of type: " << Type << std::endl;
        return false;
    }
    ReplacementFuncion ReplaceFunc(getReplacementFuncion());
    if(ReplaceFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Replacement function." << std::endl;
        return false;
    }

    return ReplaceFunc(InterpFunc, time, prevTime, ReplacePolicy, isCyclic, Result, Index, Blend);
}

RawInterpFuncion KeyframeSequence::getRawInterpFuncion(const UInt32& Type)
{
    switch(Type)
    {
    case Animator::STEP_INTERPOLATION:
        return getStepInterpFuncion();
        break;
    case Animator::LINEAR_INTERPOLATION:
        return getLinearInterpFuncion();
        break;
    case Animator::LINEAR_NORMAL_INTERPOLATION:
        return getLinearNormalInterpFuncion();
        break;
    case Animator::CUBIC_INTERPOLATION:
        return getCubicInterpFuncion();
        break;
    default:
        return RawInterpFuncion();
        break;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeSequence::KeyframeSequence(void) :
    Inherited()
{
}

KeyframeSequence::KeyframeSequence(const KeyframeSequence &source) :
    Inherited(source)
{
}

KeyframeSequence::~KeyframeSequence(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequence::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void KeyframeSequence::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequence NI" << std::endl;
}

OSG_END_NAMESPACE
