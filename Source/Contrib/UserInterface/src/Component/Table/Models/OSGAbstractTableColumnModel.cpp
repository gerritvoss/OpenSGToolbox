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

#include "OSGAbstractTableColumnModel.h"
#include "OSGTableColumnModelEvent.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractTableColumnModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractTableColumnModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTableColumnModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractTableColumnModel::addColumnModelListener(TableColumnModelListenerPtr l)
{
    _ModelListeners.insert(l);
    return EventConnection(
                           boost::bind(&AbstractTableColumnModel::isColumnModelListenerAttached, this, l),
                           boost::bind(&AbstractTableColumnModel::removeColumnModelListener, this, l));
}

void AbstractTableColumnModel::removeColumnModelListener(TableColumnModelListenerPtr l)
{
    TableColumnModelListenerSetItor EraseIter(_ModelListeners.find(l));
    if(EraseIter != _ModelListeners.end())
    {
        _ModelListeners.erase(EraseIter);
    }
}

void AbstractTableColumnModel::produceColumnAdded(const UInt32& ToIndex)
{
    const TableColumnModelEventUnrecPtr TheEvent = TableColumnModelEvent::create(this, getSystemTime(), 0, ToIndex);
    TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->columnAdded(TheEvent);
    }
    _Producer.produceEvent(ColumnAddedMethodId,TheEvent);
}
void AbstractTableColumnModel::produceColumnMoved(const UInt32& ToIndex,const UInt32& FromIndex)
{
    const TableColumnModelEventUnrecPtr TheEvent = TableColumnModelEvent::create(this, getSystemTime(), FromIndex, ToIndex);
    TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->columnMoved(TheEvent);
    }
    _Producer.produceEvent(ColumnMovedMethodId,TheEvent);
}

void AbstractTableColumnModel::produceColumnRemoved(const UInt32& FromIndex)
{
    const TableColumnModelEventUnrecPtr TheEvent = TableColumnModelEvent::create(this, getSystemTime(), FromIndex, 0);
    TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->columnRemoved(TheEvent);
    }
    _Producer.produceEvent(ColumnRemovedMethodId,TheEvent);
}

void AbstractTableColumnModel::produceColumnMarginChanged(void)
{
    const ChangeEventUnrecPtr TheEvent = ChangeEvent::create(this, getSystemTime());
    TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->columnMarginChanged(TheEvent);
    }
    _Producer.produceEvent(ColumnMarginChangedMethodId,TheEvent);
}

void AbstractTableColumnModel::produceColumnSelectionChanged(const ListSelectionEventUnrecPtr e)
{
    TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->columnSelectionChanged(e);
    }
    _Producer.produceEvent(ColumnSelectionChangedMethodId,e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTableColumnModel::AbstractTableColumnModel(void) :
    Inherited()
{
}

AbstractTableColumnModel::AbstractTableColumnModel(const AbstractTableColumnModel &source) :
    Inherited(source)
{
}

AbstractTableColumnModel::~AbstractTableColumnModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTableColumnModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractTableColumnModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractTableColumnModel NI" << std::endl;
}

OSG_END_NAMESPACE
