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

#include "OSGKeyframeAnimator.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeyframeAnimatorBase.cpp file.
// To modify it, please change the .fcd file (OSGKeyframeAnimator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeAnimator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool KeyframeAnimator::animate(UInt32 InterpType,
                               UInt32 ReplacementPolicy,
                               bool Cycling,
                               Real32 time,
                               Real32 prevTime,
                               EditFieldHandlePtr Result,
                               UInt32 Index)
{
   if( getKeyframeSequence() != NULL)
   {
      return getKeyframeSequence()->interpolate(InterpType, time, prevTime, ReplacementPolicy, Cycling, Result, Index, 1.0f);
   }
   else
   {
      return false;
   }
}
    
Real32 KeyframeAnimator::getLength(void) const
{
    if(getKeyframeSequence()->size() > 0)
    {
        return getKeyframeSequence()->getKeys().back();
    }
    else
    {
        return 0.0f;
    }
}

const DataType* KeyframeAnimator::getDataType(void) const
{
   return getKeyframeSequence()->getDataType();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeAnimator::KeyframeAnimator(void) :
    Inherited()
{
}

KeyframeAnimator::KeyframeAnimator(const KeyframeAnimator &source) :
    Inherited(source)
{
}

KeyframeAnimator::~KeyframeAnimator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeAnimator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void KeyframeAnimator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeyframeAnimator NI" << std::endl;
}

OSG_END_NAMESPACE
