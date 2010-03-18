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

#include "OSGDefaultTableColumnModel.h"
#include "OSGListSelectionModel.h"
#include "OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTableColumnModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTableColumnModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTableColumnModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultTableColumnModel::addColumn(const TableColumnRefPtr aColumn)
{
    _Columns.push_back(aColumn);
    recalcWidthCache();
    //aColumn->addFieldChangeListener(&_TableFieldChangeListener);
    produceColumnAdded(_Columns.size());
}

TableColumnRefPtr DefaultTableColumnModel::getColumn(const UInt32& columnIndex) const
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

std::vector<TableColumnUnrecPtr> DefaultTableColumnModel::getColumns(void) const
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

void DefaultTableColumnModel::removeColumn(TableColumnRefPtr column)
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
        //column->removeFieldChangeListener(&_TableFieldChangeListener);
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
        _SelectionModel->removeListSelectionListener(&_TableSelectionListener);
    }
    _SelectionModel = newModel;
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addListSelectionListener(&_TableSelectionListener);
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableColumnModel::DefaultTableColumnModel(void) :
    Inherited(),
    _ColumnMargin(1),
    _ColumnSelectionAllowed(true),
    _SelectionModel(),
    _TotalColumnWidth(0),
    _TableSelectionListener(this)
{
}

DefaultTableColumnModel::DefaultTableColumnModel(const DefaultTableColumnModel &source) :
    Inherited(source),
    _ColumnMargin(source._ColumnMargin),
    _ColumnSelectionAllowed(source._ColumnSelectionAllowed),
    _SelectionModel(source._SelectionModel),
    _TableSelectionListener(this)
{
}

DefaultTableColumnModel::~DefaultTableColumnModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTableColumnModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultTableColumnModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTableColumnModel NI" << std::endl;
}

void DefaultTableColumnModel::TableSelectionListener::selectionChanged(const ListSelectionEventUnrecPtr e)
{
    _DefaultTableColumnModel->produceColumnSelectionChanged(e);
}

/*void DefaultTableColumnModel::TableFieldChangeListener::fieldChanged(const FieldChangeEventUnrecPtr e)
{
    if(e->getFieldDescription()->getFieldId() == TableColumn::PreferredWidthFieldId ||
        e->getFieldDescription()->getFieldId() == TableColumn::WidthFieldId)
    {
        _DefaultTableColumnModel->recalcWidthCache();
    }
}*/

OSG_END_NAMESPACE
