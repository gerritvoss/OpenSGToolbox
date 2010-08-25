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

#include "OSGDefaultTreeSelectionModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTreeSelectionModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTreeSelectionModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeSelectionModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultTreeSelectionModel::setSelectionRows(std::vector<Int32> Rows)
{
    std::vector<TreePath> Paths;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        if(Rows[i] < 0)
        {
            return;
        }
        Paths.push_back(getRowMapper()->getPathForRow(Rows[i]));
    }
    setSelectionPaths(Paths);
}

void DefaultTreeSelectionModel::setSelectionRow(Int32 Row)
{
    if(Row >=0 )
    {
        setSelectionPath(getRowMapper()->getPathForRow(Row));
    }
}

void DefaultTreeSelectionModel::removeSelectionRows(std::vector<Int32> Rows)
{
    std::vector<TreePath> Paths;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        if(Rows[i] < 0)
        {
            return;
        }
        Paths.push_back(getRowMapper()->getPathForRow(Rows[i]));
    }
    removeSelectionPaths(Paths);
}

void DefaultTreeSelectionModel::removeSelectionRow(Int32 Row)
{
    if(Row >=0 )
    {
        removeSelectionPath(getRowMapper()->getPathForRow(Row));
    }
}

Int32 DefaultTreeSelectionModel::getSelectionRow(void) const
{
    return _MinSelectionIndex;
}

void DefaultTreeSelectionModel::addSelectionRows(std::vector<Int32> Rows)
{
    std::vector<TreePath> Paths;
    for(UInt32 i(0) ; i<Rows.size() ; ++i)
    {
        if(Rows[i] < 0)
        {
            return;
        }
        Paths.push_back(getRowMapper()->getPathForRow(Rows[i]));
    }
    addSelectionPaths(Paths);
}

void DefaultTreeSelectionModel::addSelectionRow(Int32 Row)
{
    if(Row >=0 )
    {
        addSelectionPath(getRowMapper()->getPathForRow(Row));
    }
}

void DefaultTreeSelectionModel::addSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector(1, path);

	// add path using the addSelectionPaths function below
	addSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::addSelectionPaths(std::vector<TreePath> paths)
{
    if(!paths.empty())
    {
        TreePathSet PreSelectedSet(_SelectionSet);
        
        switch(getSelectionMode())
        {
        case SINGLE_TREE_SELECTION:
            {
                _SelectionSet.clear();
                _SelectionSet.insert(paths.begin(), paths.end());

                //Get the Minimum Row
                Int32 MinRow = getMinRow(_SelectionSet);

                //Set the selection to the Minimum Row
                _SelectionSet.clear();
                if(MinRow >= 0)
                {
                    _SelectionSet.insert(getRowMapper()->getPathForRow(MinRow));
                }
            }
            break;
        case CONTIGUOUS_TREE_SELECTION:
            _SelectionSet.insert(paths.begin(), paths.end());
            //Get the Minimum Contiguous Section
			_SelectionSet = getMinimumContiguousSelection(_SelectionSet);
            break;
        case DISCONTIGUOUS_TREE_SELECTION:
            _SelectionSet.insert(paths.begin(), paths.end());
            break;
        }

        updateMinMax();
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        produceEvents(PreSelectedSet, _SelectionSet, OldLeadSelectionIndex);
    }
}

//void DefaultTreeSelectionModel::changeValues(std::vector<TreePath> paths)
//{
//}

void DefaultTreeSelectionModel::clearSelection(void)
{
    TreePathSet PreSelectedSet(_SelectionSet);

    _SelectionSet.clear();

    updateMinMax();
    Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
    produceEvents(PreSelectedSet, _SelectionSet, OldLeadSelectionIndex);
}

TreePath DefaultTreeSelectionModel::getAnchorSelectionPath(void) const
{
    if(_AnchorSelectionIndex < 0)
    {
	    return TreePath();
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
	    return TreePath();
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

TreeRowMapper* DefaultTreeSelectionModel::getRowMapper(void) const
{
	return _TreeRowMapper; // returns the current row from TreeRowMapper
}

UInt32 DefaultTreeSelectionModel::getSelectionCount(void) const
{
	return _SelectionSet.size(); // returns the size of _SelectionNumberSet
}

UInt32 DefaultTreeSelectionModel::getSelectionMode(void) const
{
	return _SelectionMode;  // returns the current value of _SelectionMode, either SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION, or DISCONTIGUOUS_TREE_SELECTION
}

TreePath DefaultTreeSelectionModel::getSelectionPath(void) const
{
    if(_MinSelectionIndex < 0)
    {
	    return TreePath();
    }
    else
    {
        return _TreeRowMapper->getPathForRow(getSelectionRow());
    }
}

std::vector<TreePath> DefaultTreeSelectionModel::getSelectionPaths(void) const
{
    std::vector<TreePath> Result(_SelectionSet.begin(), _SelectionSet.end());
	return Result;  // returns the current selection paths
}

std::vector<Int32> DefaultTreeSelectionModel::getSelectionRows(void) const
{
    std::vector<Int32> Result;
    for(TreePathSet::const_iterator Itor(_SelectionSet.begin());
        Itor != _SelectionSet.end() ;
        ++Itor)
    {
        Result.push_back(getRowMapper()->getRowForPath(*Itor));
    }

	return Result;  // returns the current rows within the selection
}

bool DefaultTreeSelectionModel::isPathSelected(std::vector<TreePath> paths) const
{
    for(TreePathSet::const_iterator Itor(_SelectionSet.begin());
        Itor != _SelectionSet.end() ;
        ++Itor)
    {
        if(!isPathSelected(*Itor))
        {
            return false;
        }
    }
    return true;
}

bool DefaultTreeSelectionModel::isPathSelected(TreePath path) const
{
    return std::find(_SelectionSet.begin(),_SelectionSet.end(), path) != _SelectionSet.end();
}

bool DefaultTreeSelectionModel::isRowSelected(const Int32& row) const
{
    return isPathSelected(getRowMapper()->getPathForRow(row));
}

bool DefaultTreeSelectionModel::isSelectionEmpty(void) const
{
	return _SelectionSet.empty();  // returns true if _SelectionSet is empty
}

void DefaultTreeSelectionModel::removeSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector(1, path);

	// remove TreePathVector using the removeSelectionPaths function below
	removeSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::removeSelectionPaths(std::vector<TreePath> paths)
{
    if(!paths.empty())
    {
        TreePathSet PreSelectedSet(_SelectionSet);
        _SelectionSet.clear();
        
        TreePathSet RemoveSet(paths.begin(), paths.end());
        std::set_difference(PreSelectedSet.begin(), PreSelectedSet.end(), RemoveSet.begin(), RemoveSet.end(), std::inserter(_SelectionSet, _SelectionSet.begin()), TreePath::BreadthFirstFunctional());
        switch(getSelectionMode())
        {
        case SINGLE_TREE_SELECTION:
            {
                //Get the Minimum Row
                Int32 MinRow = getMinRow(_SelectionSet);

                //Set the selection to the Minimum Row
                _SelectionSet.clear();
                if(MinRow >= 0)
                {
                    _SelectionSet.insert(getRowMapper()->getPathForRow(MinRow));
                }
            }
            break;
        case CONTIGUOUS_TREE_SELECTION:
            //Get the Minimum Contiguous Section
			_SelectionSet = getMinimumContiguousSelection(_SelectionSet);
            break;
        }

        updateMinMax();
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        produceEvents(PreSelectedSet, _SelectionSet, OldLeadSelectionIndex);
    }
}

//void DefaultTreeSelectionModel::resetRowSelection(void)
//{
	// Not sure what this function does
//}

void DefaultTreeSelectionModel::setRowMapper(TreeRowMapper* const newMapper)
{
    _TreeRowMapper = newMapper;
}

void DefaultTreeSelectionModel::setSelectionMode(const UInt32& mode)
{
    if(_SelectionMode != static_cast<TreeSelectionMode>(mode) &&
        !_SelectionSet.empty())
    {
        TreePathSet PreSelectedSet(_SelectionSet);

        switch(mode)
        {
			case SINGLE_TREE_SELECTION:
                {
                    //Get the Minimum Row
                    Int32 MinRow = getMinRow(_SelectionSet);

                    //Set the selection to the Minimum Row
                    _SelectionSet.clear();
                    if(MinRow >= 0)
                    {
                        _SelectionSet.insert(getRowMapper()->getPathForRow(MinRow));
                    }
                }
				break;
			case CONTIGUOUS_TREE_SELECTION:
                //Get the Minimum Contiguous Section
				_SelectionSet = getMinimumContiguousSelection(_SelectionSet);
                break;
        }

	    _SelectionMode = static_cast<TreeSelectionMode>(mode);
        
		// update indices
        updateMinMax();
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        
        //Produce Events
        produceEvents(PreSelectedSet, _SelectionSet, OldLeadSelectionIndex);
    }
}

void DefaultTreeSelectionModel::setSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector(1,path);

	// remove TreePathVector using the removeSelectionPaths function below
	setSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::setSelectionPaths(std::vector<TreePath> paths)
{
    if(!paths.empty())
    {
        TreePathSet PreSelectedSet(_SelectionSet);
        Int32 OldLeadSelectionIndex(_LeadSelectionIndex);
        
        switch(getSelectionMode())
        {
        case SINGLE_TREE_SELECTION:
            {
                //Get the Minimum Row
                Int32 MinRow = getMinRow(TreePathSet(paths.begin(),paths.end()));

                //Set the selection to the Minimum Row
                _SelectionSet.clear();
                if(MinRow >= 0)
                {
                    _SelectionSet.insert(getRowMapper()->getPathForRow(MinRow));
                }
            }
            break;
        case CONTIGUOUS_TREE_SELECTION:
            //Get the Minimum Contiguous Section
			_SelectionSet.clear();
            _SelectionSet.insert(paths.begin(), paths.end());
			_SelectionSet = getMinimumContiguousSelection(_SelectionSet);
            break;
        case DISCONTIGUOUS_TREE_SELECTION:
            _SelectionSet.clear();
            _SelectionSet.insert(paths.begin(), paths.end());
            break;
        }

        updateMinMax();
        produceEvents(PreSelectedSet, _SelectionSet, OldLeadSelectionIndex);
    }
}

void DefaultTreeSelectionModel::setSelectionInterval(const Int32& index0, const Int32& index1)
{
    if(index0 >= 0 &&
        index1 >= 0)
    {
        std::vector<TreePath> Paths;
		if(index0 < index1 )
		{
			for(Int32 i(index0) ; i<=index1 ; ++i)
			{
				Paths.push_back(getRowMapper()->getPathForRow(i));
			}
		}
		else
		{
			for(Int32 i(index0) ; i>=index1 ; --i)
			{
				Paths.push_back(getRowMapper()->getPathForRow(i));
			}
		}

        setSelectionPaths(Paths);
    }
}


DefaultTreeSelectionModel::TreePathSet DefaultTreeSelectionModel::getMinimumContiguousSelection(const TreePathSet& PathSet) const
{
	TreePathSet Result;
	NumberSet RowSet;

    toRowNumberSet(RowSet, PathSet);

	if(RowSet.size() > 0)
	{
		NumberRange MinimumSection(RowSet.front());
		for(Int32 i(MinimumSection.getMin()) ; i<= MinimumSection.getMax() ; ++i)
		{
			Result.insert(getRowMapper()->getPathForRow(i));
		}
	}

	return Result;
}


void DefaultTreeSelectionModel::setLeadSelectionPath(const TreePath& path)
{
	setLeadSelectionRow(getRowMapper()->getRowForPath(path));
}

void DefaultTreeSelectionModel::setLeadSelectionRow(Int32 Row)
{
	_LeadSelectionIndex = Row;
}

void DefaultTreeSelectionModel::setAnchorSelectionPath(const TreePath& path)
{
	setAnchorSelectionRow(getRowMapper()->getRowForPath(path));
}

void DefaultTreeSelectionModel::setAnchorSelectionRow(Int32 Row)
{
	_AnchorSelectionIndex = Row;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultTreeSelectionModel::produceEvents(const TreePathSet& PreSelectedSet, const TreePathSet& PostSelectedSet, Int32 OldLeadSelectionIndex)
{
    NumberSet PreSelectedNumberSet, PostSelectedNumberSet;
    toRowNumberSet(PreSelectedNumberSet, PreSelectedSet);
    toRowNumberSet(PostSelectedNumberSet, PostSelectedSet);

    NumberSet RemovedSet = difference_NumberSet(PreSelectedNumberSet,PostSelectedNumberSet);
    NumberSet AddedSet = difference_NumberSet(PostSelectedNumberSet, PreSelectedNumberSet);
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

Int32 DefaultTreeSelectionModel::getMinRow(const TreePathSet& PathSet) const
{
    if(PathSet.empty())
    {
		return -1;
    }
    else
    {
        Int32 Min;
        TreePathSet::const_iterator Itor(PathSet.begin());
		Min = getRowMapper()->getRowForPath(*Itor);
        ++Itor;
        while(Itor != PathSet.end())
        {
            Int32 Value;
            Value = getRowMapper()->getRowForPath(*Itor);
            if(Value < Min)
            {
                Min = Value;
            }
            ++Itor;
        }
        return Min;
    }
}

Int32 DefaultTreeSelectionModel::getMaxRow(const TreePathSet& PathSet) const
{
    if(PathSet.empty())
    {
		return -1;
    }
    else
    {
        Int32 Max;
        TreePathSet::const_iterator Itor(PathSet.begin());
		Max = getRowMapper()->getRowForPath(*Itor);
        ++Itor;
        while(Itor != PathSet.end())
        {
            Int32 Value;
            Value = getRowMapper()->getRowForPath(*Itor);
            if(Value > Max)
            {
                Max = Value;
            }
            ++Itor;
        }
        return Max;
    }
}

void DefaultTreeSelectionModel::updateMinMax(void)
{
    if(_SelectionSet.empty())
    {
		// in the event of _SelectionSet being empty, just set
		// them both to -1
		_MaxSelectionIndex = _MinSelectionIndex = -1;
    }
    else
    {
        TreePathSet::const_iterator Itor(_SelectionSet.begin());
		_MaxSelectionIndex = _MinSelectionIndex = getRowMapper()->getRowForPath(*Itor);
        ++Itor;
        while(Itor != _SelectionSet.end())
        {
            Int32 Value;
            Value = getRowMapper()->getRowForPath(*Itor);
            if(Value < _MinSelectionIndex)
            {
                _MinSelectionIndex = Value;
            }
            if(Value > _MaxSelectionIndex)
            {
                _MaxSelectionIndex = Value;
            }
            ++Itor;
        }
    }
}

void DefaultTreeSelectionModel::toRowNumberSet(NumberSet& Result, const TreePathSet& PathSet) const
{
    for(TreePathSet::const_iterator Itor(PathSet.begin());
        Itor != PathSet.end() ;
        ++Itor)
    {
        Int32 Row;
        Row = getRowMapper()->getRowForPath(*Itor);
        Result.addRange(NumberRange(Row,Row));
    }
}
/*----------------------- constructors & destructors ----------------------*/

DefaultTreeSelectionModel::DefaultTreeSelectionModel(void) :
    Inherited(),
        _SelectionMode(DefaultTreeSelectionModel::SINGLE_TREE_SELECTION)
{
}

DefaultTreeSelectionModel::DefaultTreeSelectionModel(const DefaultTreeSelectionModel &source) :
    Inherited(source),
        _SelectionMode(source._SelectionMode)
{
}

DefaultTreeSelectionModel::~DefaultTreeSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTreeSelectionModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultTreeSelectionModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeSelectionModel NI" << std::endl;
}

OSG_END_NAMESPACE
