/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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
 **     class Component!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include "OSGMouseEventDetails.h"
#include "OSGMouseWheelEventDetails.h"
#include "OSGKeyEventDetails.h"
#include "OSGFocusEventDetails.h"
#include "OSGComponentEventDetails.h"

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &ComponentBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ComponentBase::getClassTypeId(void)
{
    return _type.getId();
}
//! access the producer type of the class
inline
const EventProducerType &ComponentBase::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 ComponentBase::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

inline
OSG::UInt16 ComponentBase::getClassGroupId(void)
{
    return _type.getGroupId();
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void ComponentBase::execSync (      ComponentBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (PositionFieldMask & whichField))
        _sfPosition.syncWith(pFrom->_sfPosition);

    if(FieldBits::NoField != (ClipBoundsFieldMask & whichField))
        _sfClipBounds.syncWith(pFrom->_sfClipBounds);

    if(FieldBits::NoField != (MinSizeFieldMask & whichField))
        _sfMinSize.syncWith(pFrom->_sfMinSize);

    if(FieldBits::NoField != (MaxSizeFieldMask & whichField))
        _sfMaxSize.syncWith(pFrom->_sfMaxSize);

    if(FieldBits::NoField != (PreferredSizeFieldMask & whichField))
        _sfPreferredSize.syncWith(pFrom->_sfPreferredSize);

    if(FieldBits::NoField != (SizeFieldMask & whichField))
        _sfSize.syncWith(pFrom->_sfSize);

    if(FieldBits::NoField != (VisibleFieldMask & whichField))
        _sfVisible.syncWith(pFrom->_sfVisible);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
        _sfEnabled.syncWith(pFrom->_sfEnabled);

    if(FieldBits::NoField != (FocusedFieldMask & whichField))
        _sfFocused.syncWith(pFrom->_sfFocused);

    if(FieldBits::NoField != (ConstraintsFieldMask & whichField))
        _sfConstraints.syncWith(pFrom->_sfConstraints);

    if(FieldBits::NoField != (BorderFieldMask & whichField))
        _sfBorder.syncWith(pFrom->_sfBorder);

    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
        _sfBackground.syncWith(pFrom->_sfBackground);

    if(FieldBits::NoField != (DisabledBorderFieldMask & whichField))
        _sfDisabledBorder.syncWith(pFrom->_sfDisabledBorder);

    if(FieldBits::NoField != (DisabledBackgroundFieldMask & whichField))
        _sfDisabledBackground.syncWith(pFrom->_sfDisabledBackground);

    if(FieldBits::NoField != (DragEnabledFieldMask & whichField))
        _sfDragEnabled.syncWith(pFrom->_sfDragEnabled);

    if(FieldBits::NoField != (ScrollTrackingCharacteristicsFieldMask & whichField))
        _sfScrollTrackingCharacteristics.syncWith(pFrom->_sfScrollTrackingCharacteristics);

    if(FieldBits::NoField != (FocusedBorderFieldMask & whichField))
        _sfFocusedBorder.syncWith(pFrom->_sfFocusedBorder);

    if(FieldBits::NoField != (FocusedBackgroundFieldMask & whichField))
        _sfFocusedBackground.syncWith(pFrom->_sfFocusedBackground);

    if(FieldBits::NoField != (RolloverBorderFieldMask & whichField))
        _sfRolloverBorder.syncWith(pFrom->_sfRolloverBorder);

    if(FieldBits::NoField != (RolloverBackgroundFieldMask & whichField))
        _sfRolloverBackground.syncWith(pFrom->_sfRolloverBackground);

    if(FieldBits::NoField != (FocusedForegroundFieldMask & whichField))
        _sfFocusedForeground.syncWith(pFrom->_sfFocusedForeground);

    if(FieldBits::NoField != (RolloverForegroundFieldMask & whichField))
        _sfRolloverForeground.syncWith(pFrom->_sfRolloverForeground);

    if(FieldBits::NoField != (DisabledForegroundFieldMask & whichField))
        _sfDisabledForeground.syncWith(pFrom->_sfDisabledForeground);

    if(FieldBits::NoField != (ForegroundFieldMask & whichField))
        _sfForeground.syncWith(pFrom->_sfForeground);

    if(FieldBits::NoField != (ToolTipFieldMask & whichField))
        _sfToolTip.syncWith(pFrom->_sfToolTip);

    if(FieldBits::NoField != (OpacityFieldMask & whichField))
        _sfOpacity.syncWith(pFrom->_sfOpacity);

    if(FieldBits::NoField != (ParentContainerFieldMask & whichField))
        _sfParentContainer.syncWith(pFrom->_sfParentContainer);

    if(FieldBits::NoField != (ClippingFieldMask & whichField))
        _sfClipping.syncWith(pFrom->_sfClipping);

    if(FieldBits::NoField != (PopupMenuFieldMask & whichField))
        _sfPopupMenu.syncWith(pFrom->_sfPopupMenu);

    if(FieldBits::NoField != (CursorFieldMask & whichField))
        _sfCursor.syncWith(pFrom->_sfCursor);
}
#endif


inline
const Char8 *ComponentBase::getClassname(void)
{
    return "Component";
}

inline
UInt32 ComponentBase::getNumProducedEvents(void) const
{
    return getProducerType().getNumEventDescs();
}

inline
const EventDescription *ComponentBase::getProducedEventDescription(const std::string &ProducedEventName) const
{
    return getProducerType().findEventDescription(ProducedEventName);
}

inline
const EventDescription *ComponentBase::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getEventDescription(ProducedEventId);
}

inline
UInt32 ComponentBase::getProducedEventId(const std::string &ProducedEventName) const
{
    return getProducerType().getProducedEventId(ProducedEventName);
}

inline
boost::signals2::connection  ComponentBase::connectMouseMoved(const MouseMovedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseMovedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseMoved(const MouseMovedEventType::group_type &group,
                                                    const MouseMovedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseMovedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseMoved(const MouseMovedEventType::group_type &group)
{
    _MouseMovedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseMoved(void)
{
    _MouseMovedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseMoved(void) const
{
    return _MouseMovedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseMoved(void) const
{
    return _MouseMovedEvent.num_slots();
}

inline
void ComponentBase::produceMouseMoved(MouseMovedEventDetailsType* const e)
{
    produceEvent(MouseMovedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseDragged(const MouseDraggedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseDraggedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseDragged(const MouseDraggedEventType::group_type &group,
                                                    const MouseDraggedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseDraggedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseDragged(const MouseDraggedEventType::group_type &group)
{
    _MouseDraggedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseDragged(void)
{
    _MouseDraggedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseDragged(void) const
{
    return _MouseDraggedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseDragged(void) const
{
    return _MouseDraggedEvent.num_slots();
}

inline
void ComponentBase::produceMouseDragged(MouseDraggedEventDetailsType* const e)
{
    produceEvent(MouseDraggedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseClicked(const MouseClickedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseClickedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseClicked(const MouseClickedEventType::group_type &group,
                                                    const MouseClickedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseClickedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseClicked(const MouseClickedEventType::group_type &group)
{
    _MouseClickedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseClicked(void)
{
    _MouseClickedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseClicked(void) const
{
    return _MouseClickedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseClicked(void) const
{
    return _MouseClickedEvent.num_slots();
}

inline
void ComponentBase::produceMouseClicked(MouseClickedEventDetailsType* const e)
{
    produceEvent(MouseClickedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseEntered(const MouseEnteredEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseEnteredEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseEntered(const MouseEnteredEventType::group_type &group,
                                                    const MouseEnteredEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseEnteredEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseEntered(const MouseEnteredEventType::group_type &group)
{
    _MouseEnteredEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseEntered(void)
{
    _MouseEnteredEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseEntered(void) const
{
    return _MouseEnteredEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseEntered(void) const
{
    return _MouseEnteredEvent.num_slots();
}

inline
void ComponentBase::produceMouseEntered(MouseEnteredEventDetailsType* const e)
{
    produceEvent(MouseEnteredEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseExited(const MouseExitedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseExitedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseExited(const MouseExitedEventType::group_type &group,
                                                    const MouseExitedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseExitedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseExited(const MouseExitedEventType::group_type &group)
{
    _MouseExitedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseExited(void)
{
    _MouseExitedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseExited(void) const
{
    return _MouseExitedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseExited(void) const
{
    return _MouseExitedEvent.num_slots();
}

inline
void ComponentBase::produceMouseExited(MouseExitedEventDetailsType* const e)
{
    produceEvent(MouseExitedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMousePressed(const MousePressedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MousePressedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMousePressed(const MousePressedEventType::group_type &group,
                                                    const MousePressedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MousePressedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMousePressed(const MousePressedEventType::group_type &group)
{
    _MousePressedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMousePressed(void)
{
    _MousePressedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMousePressed(void) const
{
    return _MousePressedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMousePressed(void) const
{
    return _MousePressedEvent.num_slots();
}

inline
void ComponentBase::produceMousePressed(MousePressedEventDetailsType* const e)
{
    produceEvent(MousePressedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseReleased(const MouseReleasedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseReleasedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseReleased(const MouseReleasedEventType::group_type &group,
                                                    const MouseReleasedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseReleasedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseReleased(const MouseReleasedEventType::group_type &group)
{
    _MouseReleasedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseReleased(void)
{
    _MouseReleasedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseReleased(void) const
{
    return _MouseReleasedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseReleased(void) const
{
    return _MouseReleasedEvent.num_slots();
}

inline
void ComponentBase::produceMouseReleased(MouseReleasedEventDetailsType* const e)
{
    produceEvent(MouseReleasedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectMouseWheelMoved(const MouseWheelMovedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _MouseWheelMovedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectMouseWheelMoved(const MouseWheelMovedEventType::group_type &group,
                                                    const MouseWheelMovedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _MouseWheelMovedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectMouseWheelMoved(const MouseWheelMovedEventType::group_type &group)
{
    _MouseWheelMovedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsMouseWheelMoved(void)
{
    _MouseWheelMovedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyMouseWheelMoved(void) const
{
    return _MouseWheelMovedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsMouseWheelMoved(void) const
{
    return _MouseWheelMovedEvent.num_slots();
}

inline
void ComponentBase::produceMouseWheelMoved(MouseWheelMovedEventDetailsType* const e)
{
    produceEvent(MouseWheelMovedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectKeyPressed(const KeyPressedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _KeyPressedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectKeyPressed(const KeyPressedEventType::group_type &group,
                                                    const KeyPressedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _KeyPressedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectKeyPressed(const KeyPressedEventType::group_type &group)
{
    _KeyPressedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsKeyPressed(void)
{
    _KeyPressedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyKeyPressed(void) const
{
    return _KeyPressedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsKeyPressed(void) const
{
    return _KeyPressedEvent.num_slots();
}

inline
void ComponentBase::produceKeyPressed(KeyPressedEventDetailsType* const e)
{
    produceEvent(KeyPressedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectKeyReleased(const KeyReleasedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _KeyReleasedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectKeyReleased(const KeyReleasedEventType::group_type &group,
                                                    const KeyReleasedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _KeyReleasedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectKeyReleased(const KeyReleasedEventType::group_type &group)
{
    _KeyReleasedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsKeyReleased(void)
{
    _KeyReleasedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyKeyReleased(void) const
{
    return _KeyReleasedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsKeyReleased(void) const
{
    return _KeyReleasedEvent.num_slots();
}

inline
void ComponentBase::produceKeyReleased(KeyReleasedEventDetailsType* const e)
{
    produceEvent(KeyReleasedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectKeyTyped(const KeyTypedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _KeyTypedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectKeyTyped(const KeyTypedEventType::group_type &group,
                                                    const KeyTypedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _KeyTypedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectKeyTyped(const KeyTypedEventType::group_type &group)
{
    _KeyTypedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsKeyTyped(void)
{
    _KeyTypedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyKeyTyped(void) const
{
    return _KeyTypedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsKeyTyped(void) const
{
    return _KeyTypedEvent.num_slots();
}

inline
void ComponentBase::produceKeyTyped(KeyTypedEventDetailsType* const e)
{
    produceEvent(KeyTypedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectFocusGained(const FocusGainedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _FocusGainedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectFocusGained(const FocusGainedEventType::group_type &group,
                                                    const FocusGainedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _FocusGainedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectFocusGained(const FocusGainedEventType::group_type &group)
{
    _FocusGainedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsFocusGained(void)
{
    _FocusGainedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyFocusGained(void) const
{
    return _FocusGainedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsFocusGained(void) const
{
    return _FocusGainedEvent.num_slots();
}

inline
void ComponentBase::produceFocusGained(FocusGainedEventDetailsType* const e)
{
    produceEvent(FocusGainedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectFocusLost(const FocusLostEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _FocusLostEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectFocusLost(const FocusLostEventType::group_type &group,
                                                    const FocusLostEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _FocusLostEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectFocusLost(const FocusLostEventType::group_type &group)
{
    _FocusLostEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsFocusLost(void)
{
    _FocusLostEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyFocusLost(void) const
{
    return _FocusLostEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsFocusLost(void) const
{
    return _FocusLostEvent.num_slots();
}

inline
void ComponentBase::produceFocusLost(FocusLostEventDetailsType* const e)
{
    produceEvent(FocusLostEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentHidden(const ComponentHiddenEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentHiddenEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentHidden(const ComponentHiddenEventType::group_type &group,
                                                    const ComponentHiddenEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentHiddenEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentHidden(const ComponentHiddenEventType::group_type &group)
{
    _ComponentHiddenEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentHidden(void)
{
    _ComponentHiddenEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentHidden(void) const
{
    return _ComponentHiddenEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentHidden(void) const
{
    return _ComponentHiddenEvent.num_slots();
}

inline
void ComponentBase::produceComponentHidden(ComponentHiddenEventDetailsType* const e)
{
    produceEvent(ComponentHiddenEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentVisible(const ComponentVisibleEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentVisibleEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentVisible(const ComponentVisibleEventType::group_type &group,
                                                    const ComponentVisibleEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentVisibleEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentVisible(const ComponentVisibleEventType::group_type &group)
{
    _ComponentVisibleEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentVisible(void)
{
    _ComponentVisibleEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentVisible(void) const
{
    return _ComponentVisibleEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentVisible(void) const
{
    return _ComponentVisibleEvent.num_slots();
}

inline
void ComponentBase::produceComponentVisible(ComponentVisibleEventDetailsType* const e)
{
    produceEvent(ComponentVisibleEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentMoved(const ComponentMovedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentMovedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentMoved(const ComponentMovedEventType::group_type &group,
                                                    const ComponentMovedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentMovedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentMoved(const ComponentMovedEventType::group_type &group)
{
    _ComponentMovedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentMoved(void)
{
    _ComponentMovedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentMoved(void) const
{
    return _ComponentMovedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentMoved(void) const
{
    return _ComponentMovedEvent.num_slots();
}

inline
void ComponentBase::produceComponentMoved(ComponentMovedEventDetailsType* const e)
{
    produceEvent(ComponentMovedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentResized(const ComponentResizedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentResizedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentResized(const ComponentResizedEventType::group_type &group,
                                                    const ComponentResizedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentResizedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentResized(const ComponentResizedEventType::group_type &group)
{
    _ComponentResizedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentResized(void)
{
    _ComponentResizedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentResized(void) const
{
    return _ComponentResizedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentResized(void) const
{
    return _ComponentResizedEvent.num_slots();
}

inline
void ComponentBase::produceComponentResized(ComponentResizedEventDetailsType* const e)
{
    produceEvent(ComponentResizedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentEnabled(const ComponentEnabledEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentEnabledEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentEnabled(const ComponentEnabledEventType::group_type &group,
                                                    const ComponentEnabledEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentEnabledEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentEnabled(const ComponentEnabledEventType::group_type &group)
{
    _ComponentEnabledEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentEnabled(void)
{
    _ComponentEnabledEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentEnabled(void) const
{
    return _ComponentEnabledEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentEnabled(void) const
{
    return _ComponentEnabledEvent.num_slots();
}

inline
void ComponentBase::produceComponentEnabled(ComponentEnabledEventDetailsType* const e)
{
    produceEvent(ComponentEnabledEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectComponentDisabled(const ComponentDisabledEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ComponentDisabledEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectComponentDisabled(const ComponentDisabledEventType::group_type &group,
                                                    const ComponentDisabledEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ComponentDisabledEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectComponentDisabled(const ComponentDisabledEventType::group_type &group)
{
    _ComponentDisabledEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsComponentDisabled(void)
{
    _ComponentDisabledEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyComponentDisabled(void) const
{
    return _ComponentDisabledEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsComponentDisabled(void) const
{
    return _ComponentDisabledEvent.num_slots();
}

inline
void ComponentBase::produceComponentDisabled(ComponentDisabledEventDetailsType* const e)
{
    produceEvent(ComponentDisabledEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectToolTipActivated(const ToolTipActivatedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ToolTipActivatedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectToolTipActivated(const ToolTipActivatedEventType::group_type &group,
                                                    const ToolTipActivatedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ToolTipActivatedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectToolTipActivated(const ToolTipActivatedEventType::group_type &group)
{
    _ToolTipActivatedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsToolTipActivated(void)
{
    _ToolTipActivatedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyToolTipActivated(void) const
{
    return _ToolTipActivatedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsToolTipActivated(void) const
{
    return _ToolTipActivatedEvent.num_slots();
}

inline
void ComponentBase::produceToolTipActivated(ToolTipActivatedEventDetailsType* const e)
{
    produceEvent(ToolTipActivatedEventId, e);
}

inline
boost::signals2::connection  ComponentBase::connectToolTipDeactivated(const ToolTipDeactivatedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _ToolTipDeactivatedEvent.connect(listener, at);
}

inline
boost::signals2::connection  ComponentBase::connectToolTipDeactivated(const ToolTipDeactivatedEventType::group_type &group,
                                                    const ToolTipDeactivatedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _ToolTipDeactivatedEvent.connect(group, listener, at);
}

inline
void  ComponentBase::disconnectToolTipDeactivated(const ToolTipDeactivatedEventType::group_type &group)
{
    _ToolTipDeactivatedEvent.disconnect(group);
}

inline
void  ComponentBase::disconnectAllSlotsToolTipDeactivated(void)
{
    _ToolTipDeactivatedEvent.disconnect_all_slots();
}

inline
bool  ComponentBase::isEmptyToolTipDeactivated(void) const
{
    return _ToolTipDeactivatedEvent.empty();
}

inline
UInt32  ComponentBase::numSlotsToolTipDeactivated(void) const
{
    return _ToolTipDeactivatedEvent.num_slots();
}

inline
void ComponentBase::produceToolTipDeactivated(ToolTipDeactivatedEventDetailsType* const e)
{
    produceEvent(ToolTipDeactivatedEventId, e);
}

OSG_GEN_CONTAINERPTR(Component);

OSG_END_NAMESPACE

