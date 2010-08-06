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

#include "OSGKeyframeFCPtrSequence.h"
#include "OSGAnimator.h"
#include "OSGTypeFactory.h"
#include "OSGKeyframeInterpolations.h"
#include "OSGPointerSFieldBase.h"
#include "OSGFieldContainerSFieldHandle.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeyframeFCPtrSequenceBase.cpp file.
// To modify it, please change the .fcd file (OSGKeyframeFCPtrSequence.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeFCPtrSequence::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
FieldContainer* KeyframeFCPtrSequence::getKeyValue (const UInt32 index )
{
    return getValues(index);
}

FieldContainer* KeyframeFCPtrSequence::getKeyValue (const UInt32 index ) const
{
    return getValues(index);
}


void KeyframeFCPtrSequence::setKeyframe (FieldContainer* const val,
                                         const Real32 &key,
                                         const UInt32       index )
{
    if(!isTypeSameAsValues(val->getType()))
    {
        SWARNING << "Cannot add FieldContainer with type "
                 << val->getType().getName()               << ", because this KeyframeSequence is made up of "
                 << getValues(0)->getType().getName()      << " FieldContainers"
                 << std::endl;
        return;
    }
    if(getMFValues()->size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    (*editMFValues())[index] = val;
    (*editMFInternalKeys())[index] = key;
}

void KeyframeFCPtrSequence::addKeyframe (FieldContainer* const val,
                                         const Real32 &key   )
{
    if(!isTypeSameAsValues(val->getType()))
    {
        SWARNING << "Cannot add FieldContainer with type "
                 << val->getType().getName()               << ", because this KeyframeSequence is made up of "
                 << getValues(0)->getType().getName()      << " FieldContainers"
                 << std::endl;
        return;
    }
    pushToValues(val);
    editMFInternalKeys()->push_back(key);
}

void KeyframeFCPtrSequence::insertKeyframe(FieldContainer* const val,
                                           const Real32 &key,
                                           const UInt32 index)
{
    if(!isTypeSameAsValues(val->getType()))
    {
        SWARNING << "Cannot add FieldContainer with type "
                 << val->getType().getName()               << ", because this KeyframeSequence is made up of "
                 << getValues(0)->getType().getName()      << " FieldContainers"
                 << std::endl;
        return;
    }
    if(getMFValues()->size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(getMFValues()->size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(ValuesFieldMask, _mfValues);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _mfValues.insert(_mfValues.begin() + index, val);
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

void KeyframeFCPtrSequence::push_back(FieldContainer* const val,
                                      const Real32 &key   )
{
    addKeyframe(val, key);
}

UInt32 KeyframeFCPtrSequence::size(void) const
{
    return getMFValues()->size();
}

bool KeyframeFCPtrSequence::isBlendable(void) const
{
    return false;
}

const Field& KeyframeFCPtrSequence::getKeyValues(void) const
{
    return *getMFValues();
}

const DataType* KeyframeFCPtrSequence::getDataType(void) const
{
    return _SequenceDataType;
}

void KeyframeFCPtrSequence::clear (void)
{
    clearValues();
    editMFInternalKeys()->clear();
}

bool KeyframeFCPtrSequence::interpolate(UInt32 Type,
                                        Real32 time,
                                        Real32 prevTime,
                                        UInt32 ReplacePolicy,
                                        bool isCyclic,
                                        EditFieldHandlePtr Result,
                                        UInt32 Index,
                                        Real32 Blend)
{
    if(Type != Animator::STEP_INTERPOLATION)
    {
        SWARNING << "Interpolation type " << Type<< " not supported for FCPtrs" << std::endl;
        return false;
    }
    if(ReplacePolicy != Animator::OVERWRITE)
    {
        SWARNING << "Replacement policy " << ReplacePolicy << " not supported for FCPtrs" << std::endl;
        return false;
    }

    FieldContainer* ResultValue(NULL);
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;

    if( getInterpolationIndexes(*getMFInternalKeys(), time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        ResultValue = getMFValues()->back();
    }
    else
    {
        //Return the floor
        ResultValue = getValues(LastKeyframeIndex);
    }

    if(Result->getCardinality() == FieldType::SingleField)
    {
        dynamic_cast<EditSFieldHandle<FieldContainerPtrSFieldBase>*>(Result.get())->set(ResultValue);
    }
    else
    {
        dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(Result.get())->replace(Index, ResultValue);
    }
    return true;
}

void KeyframeFCPtrSequence::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
       dynamic_cast<EditSFieldHandle<FieldContainerPtrSFieldBase>*>(Result.get())->set(NULL);
    }
    else
    {
        dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(Result.get())->replace(Index, NULL);
    }
}

bool KeyframeFCPtrSequence::isTypeSameAsValues(const DataType& type) const
{
    for(UInt32 i(0) ; i<getMFValues()->size() ; ++i)
    {
        if(type != getValues(i)->getType())
        {
            return false;
        }
    }
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeFCPtrSequence::KeyframeFCPtrSequence(void) :
    Inherited()
{
}

KeyframeFCPtrSequence::KeyframeFCPtrSequence(const KeyframeFCPtrSequence &source) :
    Inherited(source)
{
}

KeyframeFCPtrSequence::~KeyframeFCPtrSequence(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeFCPtrSequence::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    if(whichField & ValuesFieldMask)
    {
        if(size() > 0)
        {
            std::string PtrName(getValues(0)->getType().getName() + "Ptr");
            _SequenceDataType = dynamic_cast<DataType*>(TypeFactory::the()->findType(PtrName.c_str()));
        }
        else
        {
            _SequenceDataType = NULL;
        }
    }
}

void KeyframeFCPtrSequence::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeyframeFCPtrSequence NI" << std::endl;
}

OSG_END_NAMESPACE
