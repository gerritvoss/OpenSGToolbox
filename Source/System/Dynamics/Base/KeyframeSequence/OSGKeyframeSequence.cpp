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

/*!\fn UInt32  KeyframeSequence::size(void) const
 * \brief Get the number of keyframes
 *
 * \returns The number of keyframes
 */

/*!\fn bool KeyframeSequence::isBlendable(void) const
 * \brief Query if this KeyframeSequence is blendable.
 *
 * KeyframeSequences that are blendable must have a +, -, and * operator
 * defined.  This is true for all math types, but not for most other types.
 * OSG::KeyframeBasicSequenceGLenum is an example of a KeyframeSequence that is
 * not blendable.
 *
 * \returns True, if this KeyframeSequence can be used by an OSG::Animator that
 * uses blending.  OSG::BlendedKeyframeAnimator is an animator that can only be
 * used with blendable KeyframeSequences.
 */

/*!\fn const Field& KeyframeSequence::getKeyValues(void) const
 * \brief Get a reference to the field storing the Key values.
 *
 * \returns reference to the field storing the Key values
 */

/*!\fn const DataType* KeyframeSequence::getDataType(void) const
 * \brief Get the OSG::DataType that this KeyframeSequence can be applied to
 *
 * \returns OSG::DataType that this KeyframeSequence can be applied to
 */

/*!\fn void KeyframeSequence::clear(void)
 * \brief Remove all of the keyframes
 *
 */

/*!\fn bool KeyframeSequence::interpolate(UInt32 Type,
 *                                        Real32 time,
 *                                        Real32 prevTime,
 *                                        UInt32 ReplacePolicy,
 *                                        bool isCyclic,
 *                                        EditFieldHandlePtr Result,
 *                                        UInt32 Index,
 *                                        Real32 Blend)
 * \brief Apply the result of interpolating this KeyframeSequence to the given
 * field.
 *
 * \param[in] Type Interpolation type to use. #OSG::Animator::InterpolationType are
 * valid values.
 * \param[in] time Current time in the animation
 * \param[in] prevTime Previous time in the animation
 * \param[in] ReplacePolicy Policy to use when replacing the value present in
 * the field.  #OSG::Animator::ValueReplacementPolicy are valid values.
 * \param[in] isCyclic Whether this sequence should be applied as a cyclic
 * animation
 * \param[in,out] Result The field to apply the interpolation to
 * \param[in] Index The index of the field to change.  This is only relevant if
 * Result is a MultiField
 * \param[in] Blend The blend amount to apply.  This is only relevant if
 * isBlendable()
 *
 * \returns True if the value of the animation is different from the 
 * value of the Field, false otherwise.
 */

/*!\fn void KeyframeSequence::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
 * \brief Apply a "zeroing" operation to the given Field at the given index
 *
 * "Zeroing" the value of a Field replaces the value with a value defined as 
 * zero for that type.  For most numbers the zero value is 0, for Matrices it
 * is the identity matrix, for strings it is the empty string, for pointers it
 * is NULL, etc.
 *
 * \param[out] Result The field to apply the zeroing to
 * \param[in] Index The index of the field to change.  This is only relevant if
 * Result is a MultiField
 */

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
