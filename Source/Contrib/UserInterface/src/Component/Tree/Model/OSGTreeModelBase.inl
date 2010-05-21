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
 **     class TreeModel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TreeModelBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 TreeModelBase::getClassTypeId(void)
{
    return _type.getId();
}
//! access the producer type of the class
inline
const EventProducerType &TreeModelBase::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 TreeModelBase::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

inline
OSG::UInt16 TreeModelBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/



#ifdef OSG_MT_CPTR_ASPECT
inline
void TreeModelBase::execSync (      TreeModelBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);
}
#endif


inline
const Char8 *TreeModelBase::getClassname(void)
{
    return "TreeModel";
}

inline
EventConnection TreeModelBase::attachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    return _Producer.attachActivity(TheActivity, ProducedEventId);
}

inline
bool TreeModelBase::isActivityAttached(ActivityRefPtr TheActivity, UInt32 ProducedEventId) const
{
    return _Producer.isActivityAttached(TheActivity, ProducedEventId);
}

inline
UInt32 TreeModelBase::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    return _Producer.getNumActivitiesAttached(ProducedEventId);
}

inline
ActivityRefPtr TreeModelBase::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    return _Producer.getAttachedActivity(ProducedEventId,ActivityIndex);
}

inline
void TreeModelBase::detachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    _Producer.detachActivity(TheActivity, ProducedEventId);
}

inline
UInt32 TreeModelBase::getNumProducedEvents(void) const
{
    return _Producer.getNumProducedEvents();
}

inline
const MethodDescription *TreeModelBase::getProducedEventDescription(const std::string &ProducedEventName) const
{
    return _Producer.getProducedEventDescription(ProducedEventName);
}

inline
const MethodDescription *TreeModelBase::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return _Producer.getProducedEventDescription(ProducedEventId);
}

inline
UInt32 TreeModelBase::getProducedEventId(const std::string &ProducedEventName) const
{
    return _Producer.getProducedEventId(ProducedEventName);
}

inline
SFEventProducerPtr *TreeModelBase::editSFEventProducer(void)
{
    return &_sfEventProducer;
}

//! Get the value of the TreeModel::_sfEventProducer field.
inline
EventProducerPtr &TreeModelBase::editEventProducer(void)
{
    return _sfEventProducer.getValue();
}

OSG_GEN_CONTAINERPTR(TreeModel);

OSG_END_NAMESPACE
