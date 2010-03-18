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

#include "OSGAbstractTableModel.h"
#include "OSGTableModelEvent.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractTableModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractTableModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTableModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AbstractTableModel::isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const
{
    //Abstract Model defaults to not allow editing
    return false;
}

void AbstractTableModel::setValueAt(const boost::any& aValue, UInt32 rowIndex, UInt32 columnIndex)
{
    //Abstract Model defaults to not allow editing
    //So do nothing
}

EventConnection AbstractTableModel::addTableModelListener(TableModelListenerPtr l)
{
    _ModelListeners.insert(l);
    return EventConnection(
                           boost::bind(&AbstractTableModel::isTableModelListenerAttached, this, l),
                           boost::bind(&AbstractTableModel::removeTableModelListener, this, l));
}

void AbstractTableModel::removeTableModelListener(TableModelListenerPtr l)
{
    TableModelListenerSetItor EraseIter(_ModelListeners.find(l));
    if(EraseIter != _ModelListeners.end())
    {
        _ModelListeners.erase(EraseIter);
    }
}

void AbstractTableModel::produceContentsHeaderRowChanged(UInt32 FirstColumn, UInt32 LastColumn)
{
    const TableModelEventUnrecPtr TheEvent = TableModelEvent::create(TableModelRefPtr(this), getSystemTime(), FirstColumn, LastColumn, 0,0);
    TableModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsHeaderRowChanged(TheEvent);
    }
    _Producer.produceEvent(ContentsHeaderRowChangedMethodId,TheEvent);
}

void AbstractTableModel::produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
    const TableModelEventUnrecPtr TheEvent = TableModelEvent::create(TableModelRefPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
    TableModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsChanged(TheEvent);
    }
    _Producer.produceEvent(ContentsChangedMethodId,TheEvent);
}

void AbstractTableModel::produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
    const TableModelEventUnrecPtr TheEvent = TableModelEvent::create(TableModelRefPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
    TableModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalAdded(TheEvent);
    }
    _Producer.produceEvent(IntervalAddedMethodId,TheEvent);
}

void AbstractTableModel::produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
    const TableModelEventUnrecPtr TheEvent = TableModelEvent::create(TableModelRefPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
    TableModelListenerSet ModelListenerSet(_ModelListeners);
    for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalRemoved(TheEvent);
    }
    _Producer.produceEvent(IntervalRemovedMethodId,TheEvent);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTableModel::AbstractTableModel(void) :
    Inherited()
{
}

AbstractTableModel::AbstractTableModel(const AbstractTableModel &source) :
    Inherited(source)
{
}

AbstractTableModel::~AbstractTableModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTableModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractTableModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractTableModel NI" << std::endl;
}

OSG_END_NAMESPACE
