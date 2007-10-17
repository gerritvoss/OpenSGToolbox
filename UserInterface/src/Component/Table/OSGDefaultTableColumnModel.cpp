/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultTableColumnModel.h"
#include "OSGTableColumnModelListener.h"
#include "OSGTableColumnModelEvent.h"
#include "Component/List/OSGListSelectionModel.h"
#include "Component/List/OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractListModel
A AbstractListModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
ListSelectionModelPtr DefaultTableColumnModel::createSelectionModel(void)
{
    return ListSelectionModelPtr(new DefaultListSelectionModel());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultTableColumnModel::addColumn(const TableColumnPtr aColumn)
{
    _Columns.push_back(aColumn);
    recalcWidthCache();
    produceColumnAdded(_Columns.size());
}

TableColumnPtr DefaultTableColumnModel::getColumn(const UInt32& columnIndex) const
{
    return _Columns[columnIndex];
}

UInt32 DefaultTableColumnModel::getColumnCount(void) const
{
    return _Columns.size();
}

Int32 DefaultTableColumnModel::getColumnIndexAtX(UInt32 xPosition) const
{
    UInt32 CumulativeColumnWidth = 0;

    TableColumnVector::iterator Iter;
    for(UInt32 Index(0) ; Index<_Columns.size() ; ++Index)
    {
        CumulativeColumnWidth += (*Iter)->getWidth();
        if(Index != _Columns.size()-1)
        {
            CumulativeColumnWidth += getColumnMargin();
        }
        if(CumulativeColumnWidth >= xPosition)
        {
            return Index;
        }
    }

    return -1;
}

UInt32 DefaultTableColumnModel::getColumnMargin(void) const
{
    return _ColumnMargin;
}

std::vector<TableColumnPtr> DefaultTableColumnModel::getColumns(void) const
{
    return _Columns;
}

bool DefaultTableColumnModel::getColumnSelectionAllowed(void) const
{
    return _ColumnSelectionAllowed;
}

UInt32 DefaultTableColumnModel::getSelectedColumnCount(void) const
{
    if(_ColumnSelectionAllowed && _SelectionModel != NULL)
    {
        UInt32 SelectedCount(0);
        for(UInt32 i(0) ; i<_Columns.size() ; ++i)
        {
            if(_SelectionModel->isSelectedIndex(i))
            {
                ++SelectedCount;
            }
        }
        return SelectedCount;
    }
    else
    {
        return 0;
    }
}

std::vector<UInt32> DefaultTableColumnModel::getSelectedColumns(void) const
{
    if(_ColumnSelectionAllowed)
    {
        std::vector<UInt32> SelectedVector;
        for(UInt32 i(0) ; i<_Columns.size() ; ++i)
        {
            if(_SelectionModel->isSelectedIndex(i))
            {
                SelectedVector.push_back(i);
            }
        }
        return SelectedVector;
    }
    else
    {
        return std::vector<UInt32>();
    }
}

ListSelectionModelPtr DefaultTableColumnModel::getSelectionModel(void) const
{
    return _SelectionModel;
}

UInt32 DefaultTableColumnModel::getTotalColumnWidth(void) const
{
    return _TotalColumnWidth;
}

void DefaultTableColumnModel::moveColumn(const UInt32& columnIndex, const UInt32& newIndex)
{
    //Check the validity of the parameters
    if(columnIndex == newIndex ||
        columnIndex < _Columns.size() || 
        newIndex < _Columns.size())
    {
        return;
    }

    Int32 FillDirection;
    if(columnIndex < newIndex)
    {
        FillDirection = 1;
    }
    else
    {
        FillDirection = -1;
    }

    TableColumnVector::value_type TempHold(_Columns[columnIndex]);

    for(Int32 i(columnIndex) ; (FillDirection*i)<(FillDirection*static_cast<Int32>(newIndex)) ; i+=FillDirection)
    {
        _Columns[i] = _Columns[i+FillDirection];
    }

    _Columns[newIndex] = TempHold;

    produceColumnMoved(columnIndex, newIndex);
}

void DefaultTableColumnModel::removeColumn(TableColumnPtr column)
{
    //Find the Column
    UInt32 FindIndex(0);
    TableColumnVector::iterator Itor(_Columns.begin());
    while(FindIndex < _Columns.size() && column != _Columns[FindIndex])
    {
        ++FindIndex;
        ++Itor;
    }

    if(FindIndex != _Columns.size())
    {
        //Erase
        _Columns.erase(Itor);
        recalcWidthCache();
        produceColumnRemoved(FindIndex);
    }
}

void DefaultTableColumnModel::setColumnMargin(const UInt32& newMargin)
{
    _ColumnMargin = newMargin;
    recalcWidthCache();
}

void DefaultTableColumnModel::setColumnSelectionAllowed(const bool& flag)
{
    _ColumnSelectionAllowed = flag;
}

void DefaultTableColumnModel::setSelectionModel(ListSelectionModelPtr newModel)
{
    if(_SelectionModel != NULL)
    {
        _SelectionModel->removeListSelectionListener(this);
    }
    _SelectionModel = newModel;
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addListSelectionListener(this);
    }
}

void DefaultTableColumnModel::recalcWidthCache(void)
{
    _TotalColumnWidth = 0;

    TableColumnVector::iterator Iter;
    for(Iter = _Columns.begin() ; Iter != _Columns.end() ; ++Iter)
    {
        _TotalColumnWidth += (*Iter)->getWidth();
        if(Iter != _Columns.begin())
        {
            _TotalColumnWidth += getColumnMargin();
        }
    }
}

void DefaultTableColumnModel::selectionChanged(const ListSelectionEvent& e)
{
    produceColumnSelectionChanged(e);
}

void DefaultTableColumnModel::addColumnModelListener(TableColumnModelListenerPtr l)
{
   _ModelListeners.insert(l);
}

void DefaultTableColumnModel::removeColumnModelListener(TableColumnModelListenerPtr l)
{
   TableColumnModelListenerSetItor EraseIter(_ModelListeners.find(l));
   if(EraseIter != _ModelListeners.end())
   {
      _ModelListeners.erase(EraseIter);
   }
}

void DefaultTableColumnModel::produceColumnAdded(const UInt32& ToIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), 0, ToIndex, TableColumnModelEvent::COLUMN_ADDED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnAdded(TheEvent);
   }
}
void DefaultTableColumnModel::produceColumnMoved(const UInt32& ToIndex,const UInt32& FromIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), FromIndex, ToIndex, TableColumnModelEvent::COLUMN_MOVED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnMoved(TheEvent);
   }
}

void DefaultTableColumnModel::produceColumnRemoved(const UInt32& FromIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), FromIndex, 0, TableColumnModelEvent::COLUMN_REMOVED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnRemoved(TheEvent);
   }
}

void DefaultTableColumnModel::produceColumnMarginChanged(void)
{
   ChangeEvent TheEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED);
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnMarginChanged(TheEvent);
   }
}

void DefaultTableColumnModel::produceColumnSelectionChanged(const ListSelectionEvent& e)
{
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnSelectionChanged(e);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableColumnModel::DefaultTableColumnModel(void) :
    _ColumnMargin(1),
    _ColumnSelectionAllowed(true),
    _SelectionModel(),
    _TotalColumnWidth(0)
{
}
/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

