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

#include "OSGAbstractComboBoxModel.h"
#include "OSGListDataListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractComboBoxModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractComboBoxModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractComboBoxModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractComboBoxModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
    return EventConnection(
            boost::bind(&AbstractComboBoxModel::isListDataListenerAttached, this, l),
            boost::bind(&AbstractComboBoxModel::removeListDataListener, this, l));
}

void AbstractComboBoxModel::removeListDataListener(ListDataListenerPtr l)
{
    ListDataListenerSetIter EraseIter(_DataListeners.find(l));
    if(EraseIter != _DataListeners.end())
    {
        _DataListeners.erase(EraseIter);
    }
}

void AbstractComboBoxModel::produceListDataContentsChanged(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventUnrecPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsChanged(e);
    }
    _Producer.produceEvent(ListDataContentsChangedMethodId,e);
}

void AbstractComboBoxModel::produceListDataIntervalAdded(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventUnrecPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalAdded(e);
    }
    _Producer.produceEvent(ListDataIntervalAddedMethodId,e);
}

void AbstractComboBoxModel::produceListDataIntervalRemoved(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventUnrecPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalRemoved(e);
    }
    _Producer.produceEvent(ListDataIntervalRemovedMethodId,e);
}

EventConnection AbstractComboBoxModel::addSelectionListener(ComboBoxSelectionListenerPtr l)
{
    _SelectionListeners.insert(l);
    return EventConnection(
            boost::bind(&AbstractComboBoxModel::isSelectionListenerAttached, this, l),
            boost::bind(&AbstractComboBoxModel::removeSelectionListener, this, l));
}

void AbstractComboBoxModel::removeSelectionListener(ComboBoxSelectionListenerPtr l)
{
    ComboBoxSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
    if(EraseIter != _SelectionListeners.end())
    {
        _SelectionListeners.erase(EraseIter);
    }
}

void AbstractComboBoxModel::produceSelectionChanged(FieldContainerRefPtr Source, const Int32& CurrentIndex, const Int32& PreviousIndex)
{
    const ComboBoxSelectionEventUnrecPtr e = ComboBoxSelectionEvent::create(Source, getSystemTime(), CurrentIndex, PreviousIndex);
    ComboBoxSelectionListenerSet SelectionListenerSet(_SelectionListeners);
    for(ComboBoxSelectionListenerSetConstIter SetItor(SelectionListenerSet.begin()) ; SetItor != SelectionListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->selectionChanged(e);
    }
    _Producer.produceEvent(SelectionChangedMethodId,e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractComboBoxModel::AbstractComboBoxModel(void) :
    Inherited()
{
}

AbstractComboBoxModel::AbstractComboBoxModel(const AbstractComboBoxModel &source) :
    Inherited(source)
{
}

AbstractComboBoxModel::~AbstractComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractComboBoxModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractComboBoxModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractComboBoxModel NI" << std::endl;
}

OSG_END_NAMESPACE
