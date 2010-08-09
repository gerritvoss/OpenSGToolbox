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

void DefaultTableColumnModel::addColumn(TableColumn* const aColumn)
{
    pushToInternalColumns(aColumn);
    recalcWidthCache();
    produceColumnAdded(getMFInternalColumns()->size());
}

TableColumn* DefaultTableColumnModel::getColumn(const UInt32& columnIndex) const
{
	if(columnIndex < getColumnCount())
	{
        return getInternalColumns(columnIndex);
    }
    else
    {
        return NULL;
    }
}

UInt32 DefaultTableColumnModel::getColumnCount(void) const
{
    return getMFInternalColumns()->size();
}

Int32 DefaultTableColumnModel::getColumnIndexAtX(UInt32 xPosition) const
{
    UInt32 CumulativeColumnWidth = 0;

    for(UInt32 Index(0) ; Index<getMFInternalColumns()->size() ; ++Index)
    {
        CumulativeColumnWidth += getInternalColumns(Index)->getWidth();
        if(Index != getMFInternalColumns()->size()-1)
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

bool DefaultTableColumnModel::getColumnSelectionAllowed(void) const
{
    return _ColumnSelectionAllowed;
}

UInt32 DefaultTableColumnModel::getSelectedColumnCount(void) const
{
    if(_ColumnSelectionAllowed && getSelectionModel() != NULL)
    {
        UInt32 SelectedCount(0);
        for(UInt32 i(0) ; i<getMFInternalColumns()->size() ; ++i)
        {
            if(getSelectionModel()->isSelectedIndex(i))
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
        for(UInt32 i(0) ; i<getMFInternalColumns()->size() ; ++i)
        {
            if(getSelectionModel()->isSelectedIndex(i))
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

UInt32 DefaultTableColumnModel::getTotalColumnWidth(void) const
{
    return _TotalColumnWidth;
}

void DefaultTableColumnModel::moveColumn(const UInt32& columnIndex, const UInt32& newIndex)
{
    //Check the validity of the parameters
    if(columnIndex == newIndex ||
       columnIndex < getMFInternalColumns()->size() || 
       newIndex < getMFInternalColumns()->size())
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

    TableColumnUnrecPtr TempHold(getInternalColumns(columnIndex));

    for(Int32 i(columnIndex) ; (FillDirection*i)<(FillDirection*static_cast<Int32>(newIndex)) ; i+=FillDirection)
    {
        (*editMFInternalColumns())[i] = getInternalColumns(i+FillDirection);
    }

    (*editMFInternalColumns())[newIndex] = TempHold;

    produceColumnMoved(columnIndex, newIndex);
}

void DefaultTableColumnModel::removeColumn(TableColumn* const column)
{
    //Find the Column
    UInt32 FindIndex(0);
    MFInternalColumnsType::iterator Itor(editMFInternalColumns()->begin());
    while(FindIndex < getMFInternalColumns()->size() && column !=
          getInternalColumns(FindIndex))
    {
        ++FindIndex;
        ++Itor;
    }

    if(FindIndex != getMFInternalColumns()->size())
    {
        //Erase
        editMFInternalColumns()->erase(Itor);
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

void DefaultTableColumnModel::recalcWidthCache(void)
{
    _TotalColumnWidth = 0;

    for(UInt32 i(0) ; i != getMFInternalColumns()->size() ; ++i)
    {
        _TotalColumnWidth += getInternalColumns(i)->getWidth();
        if(i != 0)
        {
            _TotalColumnWidth += getColumnMargin();
        }
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultTableColumnModel::handleSelectionChanged(ListSelectionEventDetails* const e)
{
    produceColumnSelectionChanged(e);
}

/*----------------------- constructors & destructors ----------------------*/

DefaultTableColumnModel::DefaultTableColumnModel(void) :
    Inherited(),
    _ColumnMargin(1),
    _ColumnSelectionAllowed(true),
    _TotalColumnWidth(0)
{
}

DefaultTableColumnModel::DefaultTableColumnModel(const DefaultTableColumnModel &source) :
    Inherited(source),
    _ColumnMargin(source._ColumnMargin),
    _ColumnSelectionAllowed(source._ColumnSelectionAllowed),
    _TotalColumnWidth(source._TotalColumnWidth)
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

    if(whichField & SelectionModelFieldMask)
    {
        _SelectionChangedConnection.disconnect();
        if(getSelectionModel() != NULL)
        {
            _SelectionChangedConnection = getSelectionModel()->connectSelectionChanged(boost::bind(&DefaultTableColumnModel::handleSelectionChanged, this, _1));
        }
    }
}

void DefaultTableColumnModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTableColumnModel NI" << std::endl;
}

OSG_END_NAMESPACE
