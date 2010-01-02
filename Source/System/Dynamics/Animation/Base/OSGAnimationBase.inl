/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class Animation!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &AnimationBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 AnimationBase::getClassTypeId(void)
{
    return _type.getId();
}
//! access the producer type of the class
inline
const EventProducerType &AnimationBase::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 AnimationBase::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

inline
OSG::UInt16 AnimationBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the Animation::_sfCycling field.

inline
Int32 &AnimationBase::editCycling(void)
{
    editSField(CyclingFieldMask);

    return _sfCycling.getValue();
}

//! Get the value of the Animation::_sfCycling field.
inline
      Int32  AnimationBase::getCycling(void) const
{
    return _sfCycling.getValue();
}

//! Set the value of the Animation::_sfCycling field.
inline
void AnimationBase::setCycling(const Int32 value)
{
    editSField(CyclingFieldMask);

    _sfCycling.setValue(value);
}
//! Get the value of the Animation::_sfScale field.

inline
Real32 &AnimationBase::editScale(void)
{
    editSField(ScaleFieldMask);

    return _sfScale.getValue();
}

//! Get the value of the Animation::_sfScale field.
inline
      Real32  AnimationBase::getScale(void) const
{
    return _sfScale.getValue();
}

//! Set the value of the Animation::_sfScale field.
inline
void AnimationBase::setScale(const Real32 value)
{
    editSField(ScaleFieldMask);

    _sfScale.setValue(value);
}
//! Get the value of the Animation::_sfOffset field.

inline
Real32 &AnimationBase::editOffset(void)
{
    editSField(OffsetFieldMask);

    return _sfOffset.getValue();
}

//! Get the value of the Animation::_sfOffset field.
inline
      Real32  AnimationBase::getOffset(void) const
{
    return _sfOffset.getValue();
}

//! Set the value of the Animation::_sfOffset field.
inline
void AnimationBase::setOffset(const Real32 value)
{
    editSField(OffsetFieldMask);

    _sfOffset.setValue(value);
}
//! Get the value of the Animation::_sfSpan field.

inline
Real32 &AnimationBase::editSpan(void)
{
    editSField(SpanFieldMask);

    return _sfSpan.getValue();
}

//! Get the value of the Animation::_sfSpan field.
inline
      Real32  AnimationBase::getSpan(void) const
{
    return _sfSpan.getValue();
}

//! Set the value of the Animation::_sfSpan field.
inline
void AnimationBase::setSpan(const Real32 value)
{
    editSField(SpanFieldMask);

    _sfSpan.setValue(value);
}
//! Get the value of the Animation::_sfCycles field.

inline
Real32 &AnimationBase::editCycles(void)
{
    editSField(CyclesFieldMask);

    return _sfCycles.getValue();
}

//! Get the value of the Animation::_sfCycles field.
inline
      Real32  AnimationBase::getCycles(void) const
{
    return _sfCycles.getValue();
}

//! Set the value of the Animation::_sfCycles field.
inline
void AnimationBase::setCycles(const Real32 value)
{
    editSField(CyclesFieldMask);

    _sfCycles.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void AnimationBase::execSync (      AnimationBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (CyclingFieldMask & whichField))
        _sfCycling.syncWith(pFrom->_sfCycling);

    if(FieldBits::NoField != (ScaleFieldMask & whichField))
        _sfScale.syncWith(pFrom->_sfScale);

    if(FieldBits::NoField != (OffsetFieldMask & whichField))
        _sfOffset.syncWith(pFrom->_sfOffset);

    if(FieldBits::NoField != (SpanFieldMask & whichField))
        _sfSpan.syncWith(pFrom->_sfSpan);

    if(FieldBits::NoField != (CyclesFieldMask & whichField))
        _sfCycles.syncWith(pFrom->_sfCycles);
}
#endif


inline
const Char8 *AnimationBase::getClassname(void)
{
    return "Animation";
}

inline
EventConnection AnimationBase::attachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    return _Producer.attachActivity(TheActivity, ProducedEventId);
}

inline
bool AnimationBase::isActivityAttached(ActivityRefPtr TheActivity, UInt32 ProducedEventId) const
{
    return _Producer.isActivityAttached(TheActivity, ProducedEventId);
}

inline
UInt32 AnimationBase::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    return _Producer.getNumActivitiesAttached(ProducedEventId);
}

inline
ActivityRefPtr AnimationBase::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    return _Producer.getAttachedActivity(ProducedEventId,ActivityIndex);
}

inline
void AnimationBase::detachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    _Producer.detachActivity(TheActivity, ProducedEventId);
}

inline
UInt32 AnimationBase::getNumProducedEvents(void) const
{
    return _Producer.getNumProducedEvents();
}

inline
const MethodDescription *AnimationBase::getProducedEventDescription(const std::string &ProducedEventName) const
{
    return _Producer.getProducedEventDescription(ProducedEventName);
}

inline
const MethodDescription *AnimationBase::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return _Producer.getProducedEventDescription(ProducedEventId);
}

inline
UInt32 AnimationBase::getProducedEventId(const std::string &ProducedEventName) const
{
    return _Producer.getProducedEventId(ProducedEventName);
}

inline
SFEventProducerPtr *AnimationBase::editSFEventProducer(void)
{
    return &_sfEventProducer;
}

//! Get the value of the Animation::_sfEventProducer field.
inline
EventProducerPtr &AnimationBase::editEventProducer(void)
{
    return _sfEventProducer.getValue();
}

OSG_GEN_CONTAINERPTR(Animation);

OSG_END_NAMESPACE

