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

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimatorBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimator.fcd) and
// regenerate the base file.

/*!\fn bool Animator::animate(UInt32,UInt32,bool,Real32,Real32,EditFieldHandlePtr,UInt32)
 *
 * \brief Apply the result of the animator to a Field.
 *
 * @param InterpType Type of interpolation to use. #InterpolationType are
 * valid values.
 * @param ReplacementPolicy Type of replacement policy to use.
 * #ValueReplacementPolicy are valid values.
 * @param Cycling If true, will interpolate cyclically if the time in the 
 * animation is greater than the length of the animator.
 * @param time The time,in seconds, in the animation.
 * @param PrevTime The time value,in seconds, of the previous invocation
 * of animate.
 * @param Result FieldHandle to the field to apply the result to.
 * @param Index Used for MultiFields only.  Defines which index of a
 * MultiField to apply the result to.
 *
 * @return True if the value of the animation is different from the 
 * value of the Field, false otherwise.
 */

/*!\fn Real32 Animator::getLength(void) const
 *
 * \brief Get the length, in seconds, of the animator.
 *
 * @return Length in seconds.
 */

/*!\fn const DataType* Animator::getDataType(void) const
 *
 * \brief Get the data type that this animator can be applied to.
 *
 * @return The data type that this animator can be applied to.  This will
 * be NULL if the animator can not be applied to any type.
 */
/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Animator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Animator::Animator(void) :
    Inherited()
{
}

Animator::Animator(const Animator &source) :
    Inherited(source)
{
}

Animator::~Animator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Animator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Animator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Animator NI" << std::endl;
}

OSG_END_NAMESPACE
