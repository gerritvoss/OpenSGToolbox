/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Aaron Cronk                                      *
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

#include "OSGDefaultTreeSelectionModel.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTreeSelectionModel
A DefaultTreeSelectionModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultTreeSelectionModel::setSelectionRows(std::vector<Int32> Rows)
{
    NumberSet AttemptedNewSet;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        AttemptedNewSet.addRange(NumberRange(Rows[i],Rows[i]));
    }

	if (!AttemptedNewSet.isEmpty() && AttemptedNewSet.isNonNegative()) // anchor and lead are initiated to -1
	{
        NumberSet PreSelectedSet(_SelectionNumberSet);

		_SelectionNumberSet.clear();
		switch (_SelectionMode)
		{
			case SINGLE_TREE_SELECTION:
                {
                    Int32 Min;
                    AttemptedNewSet.getMin(Min);
				    _SelectionNumberSet.addRange(NumberRange(Min,Min));
                }
				break;
			case CONTIGUOUS_TREE_SELECTION:
                _SelectionNumberSet.addRange(*AttemptedNewSet.begin());
                break;
			case DISCONTIGUOUS_TREE_SELECTION:
				_SelectionNumberSet = AttemptedNewSet;
				break;
			default:
				break;
		}
		// update indices
        _SelectionNumberSet.getMin(_AnchorSelectionIndex);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _SelectionNumberSet.getMax(_LeadSelectionIndex);
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}

void DefaultTreeSelectionModel::setSelectionRow(Int32 Row)
{
    NumberSet PreSelectedSet(_SelectionNumberSet);

	_SelectionNumberSet.clear();

	if (Row >= 0)
	{
	    _SelectionNumberSet.addRange(NumberRange(Row,Row));

		// update indices
        _AnchorSelectionIndex = Row;
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _LeadSelectionIndex = Row;
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}

void DefaultTreeSelectionModel::removeSelectionRows(std::vector<Int32> Rows)
{
    NumberSet RemovedSet;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        RemovedSet.addRange(NumberRange(Rows[i],Rows[i]));
    }

	if (!RemovedSet.isEmpty() && RemovedSet.isNonNegative()) // anchor and lead are initiated to -1
	{
        NumberSet PreSelectedSet(_SelectionNumberSet);

		_SelectionNumberSet = difference_NumberSet(_SelectionNumberSet, RemovedSet);
		if(_SelectionMode == CONTIGUOUS_TREE_SELECTION)
		{
            NumberRange TheRange = _SelectionNumberSet.front();
            _SelectionNumberSet.clear();
            _SelectionNumberSet.addRange(TheRange);
		}


		// update indices
        _SelectionNumberSet.getMin(_AnchorSelectionIndex);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _SelectionNumberSet.getMax(_LeadSelectionIndex);
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}

void DefaultTreeSelectionModel::removeSelectionRow(Int32 Row)
{
    removeSelectionRows( std::vector<Int32>(Row, 1) );
}

Int32 DefaultTreeSelectionModel::getSelectionRow(void) const
{
    return _MinSelectionIndex;
}

void DefaultTreeSelectionModel::addSelectionRows(std::vector<Int32> Rows)
{
    NumberSet AddedSet;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        AddedSet.addRange(NumberRange(Rows[i],Rows[i]));
    }

	if (!AddedSet.isEmpty() && AddedSet.isNonNegative()) // anchor and lead are initiated to -1
	{
        NumberSet PreSelectedSet(_SelectionNumberSet);

		switch (_SelectionMode)
		{
			case SINGLE_TREE_SELECTION:
                {
                    Int32 Min;
                    AddedSet.getMin(Min);
                    _SelectionNumberSet.clear();
				    _SelectionNumberSet.addRange(NumberRange(Min,Min));
                }
				break;
			case CONTIGUOUS_TREE_SELECTION:
                {
                    _SelectionNumberSet = union_NumberSet(_SelectionNumberSet, AddedSet);
		            NumberRange TheRange = _SelectionNumberSet.front();
                    _SelectionNumberSet.clear();
                    _SelectionNumberSet.addRange(TheRange);
                }
                break;
			case DISCONTIGUOUS_TREE_SELECTION:
                _SelectionNumberSet = union_NumberSet(_SelectionNumberSet, AddedSet);
                break;
        }

		// update indices
        _SelectionNumberSet.getMin(_AnchorSelectionIndex);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _SelectionNumberSet.getMax(_LeadSelectionIndex);
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}

void DefaultTreeSelectionModel::addSelectionRow(Int32 Row)
{
	if (Row >= 0)
	{
        NumberSet PreSelectedSet(_SelectionNumberSet);

		switch (_SelectionMode)
		{
			case SINGLE_TREE_SELECTION:
                _SelectionNumberSet.clear();
			    _SelectionNumberSet.addRange(NumberRange(Row,Row));
				break;
			case CONTIGUOUS_TREE_SELECTION:
                {
                    _SelectionNumberSet = union_NumberSet(_SelectionNumberSet, NumberRange(Row,Row));
		            NumberRange TheRange = _SelectionNumberSet.front();
                    _SelectionNumberSet.clear();
                    _SelectionNumberSet.addRange(TheRange);
                }
                break;
			case DISCONTIGUOUS_TREE_SELECTION:
                _SelectionNumberSet = union_NumberSet(_SelectionNumberSet, NumberRange(Row,Row));
                break;
        }

		// update indices
        _SelectionNumberSet.getMin(_AnchorSelectionIndex);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _SelectionNumberSet.getMax(_LeadSelectionIndex);
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}

void DefaultTreeSelectionModel::addSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector;

	// add path using the addSelectionPaths function below
	addSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::addSelectionPaths(std::vector<TreePath> paths)
{
    std::vector<Int32> Rows;
    for(UInt32 i(0) ; i<paths.size() ; ++i)
    {
        Rows.push_back(getRowMapper()->getRowForPath(paths[i]));
    }
    addSelectionRows(Rows);
}

//void DefaultTreeSelectionModel::changeValues(std::vector<TreePath> paths)
//{
//}

void DefaultTreeSelectionModel::clearSelection(void)
{
    NumberSet PreSelectedSet(_SelectionNumberSet);
	_SelectionNumberSet.clear(); // empties _SelectionNumberSet
	// update indices
    Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
	_AnchorSelectionIndex = _LeadSelectionIndex = -1;
	updateMinMax();
    
    //Produce Events
    NumberSet PostSelectedSet(_SelectionNumberSet);
    produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
}

TreePath DefaultTreeSelectionModel::getAnchorSelectionPath(void) const
{
    if(_AnchorSelectionIndex < 0)
    {
	    return TreePath(SharedFieldPtr());
    }
    else
    {
        return _TreeRowMapper->getPathForRow(_AnchorSelectionIndex);
    }
}

Int32 DefaultTreeSelectionModel::getAnchorSelectionRow(void) const
{
	return _AnchorSelectionIndex; // returns the Anchor
}

TreePath DefaultTreeSelectionModel::getLeadSelectionPath(void) const
{
    if(_LeadSelectionIndex < 0)
    {
	    return TreePath(SharedFieldPtr());
    }
    else
    {
        return _TreeRowMapper->getPathForRow(_LeadSelectionIndex);
    }
}

Int32 DefaultTreeSelectionModel::getLeadSelectionRow(void) const
{
	return _LeadSelectionIndex; // returns the Lead in _SelectionNumberSet
}

Int32 DefaultTreeSelectionModel::getMaxSelectionRow(void) const
{
	return _MaxSelectionIndex; //Returns the largest value obtained from the TreeRowMapper for the current set of selected TreePaths.
}

Int32 DefaultTreeSelectionModel::getMinSelectionRow(void) const
{
	return _MinSelectionIndex; //Returns the smallest value obtained from the TreeRowMapper for the current set of selected TreePaths.
}

TreeRowMapperPtr DefaultTreeSelectionModel::getRowMapper(void) const
{
	return _TreeRowMapper; // returns the current row from TreeRowMapper
}

UInt32 DefaultTreeSelectionModel::getSelectionCount(void) const
{
	return _SelectionNumberSet.size(); // returns the size of _SelectionNumberSet
}

UInt32 DefaultTreeSelectionModel::getSelectionMode(void) const
{
	return _SelectionMode;  // returns the current value of _SelectionMode, either SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION, or DISCONTIGUOUS_TREE_SELECTION
}

TreePath DefaultTreeSelectionModel::getSelectionPath(void) const
{
    if(_MinSelectionIndex < 0)
    {
	    return TreePath(SharedFieldPtr());
    }
    else
    {
        return _TreeRowMapper->getPathForRow(getSelectionRow());
    }
}

std::vector<TreePath> DefaultTreeSelectionModel::getSelectionPaths(void) const
{
    std::vector<TreePath> Result;
    std::vector<Int32> SelectedRows(getSelectionRows());
    for(UInt32 i(0) ; i<SelectedRows.size(); ++i)
    {
        Result.push_back(_TreeRowMapper->getPathForRow(SelectedRows[i]));
    }
	return Result;  // returns the current selection paths
}

std::vector<Int32> DefaultTreeSelectionModel::getSelectionRows(void) const
{
    std::vector<Int32> Result;

    NumberSet::RangeListTypeConstItor RangeItor;
    for(RangeItor = _SelectionNumberSet.begin() ; RangeItor != _SelectionNumberSet.end() ; ++RangeItor)
    {
        for(Int32 i(RangeItor->getMin()) ; i<=RangeItor->getMax(); ++i)
        {
            Result.push_back(i);
        }
    }

	return Result;  // returns the current rows within the selection
}

bool DefaultTreeSelectionModel::isPathSelected(std::vector<TreePath> paths) const
{
	std::vector<Int32> PathsRowVector; // create a dummy UInt vector variable called PathsRowVector
	PathsRowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values of paths into the elements of PathsRowVector
						
	if(_SelectionNumberSet.size() >= PathsRowVector.size()) // if SelectionRowVector is smaller than PathsRowVector, the path is not fully selected
	{
		for(UInt32 i(0) ; i<PathsRowVector.size() ; ++i) // loop through each element of PathsRowVector
		{
            if(!_SelectionNumberSet.isContained(PathsRowVector[i]))
            {
                return false;
            }
		}
		return true; // return true if all the values of PathsRowVector equal a corresponding value of SelectionRowVector
	}
	else
	{
		return false; // return false if _SelectionNumberSet is too small to contain the path
	}
}

bool DefaultTreeSelectionModel::isPathSelected(TreePath path) const
{
    return _SelectionNumberSet.isContained(getRowMapper()->getRowForPath(path));
}

bool DefaultTreeSelectionModel::isRowSelected(const Int32& row) const
{
    return _SelectionNumberSet.isContained(row);
}

bool DefaultTreeSelectionModel::isSelectionEmpty(void) const
{
	return _SelectionNumberSet.isEmpty();  // returns true if _SelectionNumberSet is empty
}

void DefaultTreeSelectionModel::removeSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector;

	// remove TreePathVector using the removeSelectionPaths function below
	removeSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::removeSelectionPaths(std::vector<TreePath> paths)
{
    removeSelectionRows(getRowMapper()->getRowsForPaths(paths));
}

//void DefaultTreeSelectionModel::resetRowSelection(void)
//{
	// Not sure what this function does
//}

void DefaultTreeSelectionModel::setRowMapper(TreeRowMapperPtr newMapper)
{
    _TreeRowMapper = newMapper;
}

void DefaultTreeSelectionModel::setSelectionMode(const UInt32& mode)
{
    if(_SelectionMode != static_cast<TreeSelectionMode>(mode) &&
        !_SelectionNumberSet.isEmpty())
    {
        NumberSet PreSelectedSet(_SelectionNumberSet);

        switch(mode)
        {
			case SINGLE_TREE_SELECTION:
                {
                    Int32 Min;
                    _SelectionNumberSet.getMin(Min);
                    _SelectionNumberSet.clear();
		            _SelectionNumberSet.addRange(NumberRange(Min,Min));
                }
				break;
			case CONTIGUOUS_TREE_SELECTION:
                {
	                NumberRange TheRange = _SelectionNumberSet.front();
                    _SelectionNumberSet.clear();
                    _SelectionNumberSet.addRange(TheRange);
                }
                break;
        }

	    _SelectionMode = static_cast<TreeSelectionMode>(mode);
        
		// update indices
        _SelectionNumberSet.getMin(_AnchorSelectionIndex);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _SelectionNumberSet.getMax(_LeadSelectionIndex);
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
    }
}

void DefaultTreeSelectionModel::setSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector;

	// remove TreePathVector using the removeSelectionPaths function below
	setSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::setSelectionPaths(std::vector<TreePath> paths)
{
    setSelectionRows(getRowMapper()->getRowsForPaths(paths));
}

void DefaultTreeSelectionModel::setSelectionInterval(const Int32& index0, const Int32& index1)
{
	if (index0>=0 && index1>=0) // anchor and lead are initiated to -1
	{
        NumberSet PreSelectedSet(_SelectionNumberSet);

		_SelectionNumberSet.clear();
		switch (_SelectionMode)
		{
			case SINGLE_TREE_SELECTION:
                {
                    Int32 Min(osgMin(index0,index1));
				    _SelectionNumberSet.addRange(NumberRange(Min,Min));
                }
				break;
			case CONTIGUOUS_TREE_SELECTION:
			case DISCONTIGUOUS_TREE_SELECTION:
                _SelectionNumberSet.addRange(NumberRange(index0,index1));
				break;
			default:
				break;
		}
		// update indices
        _AnchorSelectionIndex = index0;
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        _AnchorSelectionIndex = index1;
		updateMinMax();
        
        //Produce Events
        NumberSet PostSelectedSet(_SelectionNumberSet);
        produceEvents(PreSelectedSet, PostSelectedSet, OldLeadSelectionIndex);
	}
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultTreeSelectionModel::produceEvents(const NumberSet& PreSelectedSet, const NumberSet& PostSelectedSet, Int32 OldLeadSelectionIndex)
{
    NumberSet RemovedSet = difference_NumberSet(PreSelectedSet,PostSelectedSet);
    NumberSet AddedSet = difference_NumberSet(PostSelectedSet, PreSelectedSet);
    if(!RemovedSet.isEmpty())
    {
        std::vector<NumberRange> ElementsRemoved(RemovedSet.begin(), RemovedSet.end());
        produceSelectionRemoved(ElementsRemoved, _LeadSelectionIndex, OldLeadSelectionIndex);
    }
    if(!AddedSet.isEmpty())
    {
        std::vector<NumberRange> ElementsAdded(AddedSet.begin(), AddedSet.end());
        produceSelectionAdded(ElementsAdded, _LeadSelectionIndex, OldLeadSelectionIndex);
    }
}

void DefaultTreeSelectionModel::updateMinMax(void)
{
	if (!_SelectionNumberSet.getMinMax(_MinSelectionIndex, _MaxSelectionIndex))
	{
		// in the event of _SelectionNumberSet being empty, just set
		// them both to -1
		_MaxSelectionIndex = _MinSelectionIndex = -1;
	}
}

/*----------------------- constructors & destructors ----------------------*/

DefaultTreeSelectionModel::DefaultTreeSelectionModel(void) : _TreeRowMapper(NULL)
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

