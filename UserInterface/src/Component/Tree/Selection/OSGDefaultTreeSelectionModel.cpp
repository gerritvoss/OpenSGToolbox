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

void DefaultTreeSelectionModel::addSelectionPath(TreePath path)
{
	// make a vector called TreePathVector that contains one element, path
	std::vector<TreePath> TreePathVector;

	// add path using the addSelectionPaths function below
	addSelectionPaths(TreePathVector);
}

void DefaultTreeSelectionModel::addSelectionPaths(std::vector<TreePath> paths)
{
	if(paths.size()>0)
	{
		switch (_SelectionMode) // determine if _Selection mode is SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION, or DISCONTIGUOUS_TREE_SELECTION and handle appropriately
		{
			case SINGLE_TREE_SELECTION:
				if(_Selection.empty()) // if _Selection is empty you just need to push the path onto the end
				{
					_Selection.push_back(paths.back()); // add path to _Selection
					changeValues(_Selection);
				}
				else // clear _Selection and push the path onto the end
				{
					_Selection.clear();
					_Selection.push_back(paths.back());
					changeValues(_Selection);
				}
				break;
			case CONTIGUOUS_TREE_SELECTION: 
				if(isPathSelected(paths)) // if _Selection contains the paths then nothing else is necessary
				{
					break;
				}
				else if(arePathsContiguous(paths)) // if paths is contiguous then check to see if it is contiguous with _Selection
				{
					if(_Selection.empty()) // if _Selection is empty just need to push the path onto the end
					{
						_Selection.push_back(paths.back());
						changeValues(_Selection);
						break;
					}
					if(arePathsContiguous(paths, _Selection)) // if paths is contiguous with _Selection push the path onto the appropriate portion of _Selection
					{
						std::vector<UInt32> PathsRowVector; // create a dummy UInt vector variable called PathsRowVector
						PathsRowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values of paths into the elements of PathsRowVector
						
						std::vector<UInt32> SelectionRowVector; // create a dummy UInt vector variable called SelectionRowVector
						SelectionRowVector = _TreeRowMapper->getRowsForPaths(_Selection); // assign the row values of paths into the elements of SelectionRowVector
						
						std::vector<TreePath> TempTreePathVector;
						
						bool lessthan; // dummy boolean variable that toggles to true when a value in PathsRowVector less than any value in SelectionRowVector
						bool equalto;  // dummy boolean variable that toggles to true when a value in PathsRowVector equals any value in SelectionRowVector
						bool greaterthan; // dummy boolean variable that toggles to true when a value in PathsRowVector greater than any value in SelectionRowVector
			
						lessthan = equalto = greaterthan = false; // initialize these variable to false

						for(UInt32 i1(0) ; i1<PathsRowVector.size() ; ++i1) // loop through PathRowsVector
						{
							for(UInt32 i2(0) ; i2<SelectionRowVector.size() ; ++i2) // loop through SelectionRowVector
							{
								if(PathsRowVector[i1] < SelectionRowVector[i2])
								{
									lessthan = true; // if the value in PathsRowVector < the value of SelectionRowVector toggle lessthan to true
								}
								if(PathsRowVector[i1] = SelectionRowVector[i2])
								{
									equalto = true; // if the value in PathsRowVector = the value of SelectionRowVector toggle equatlto to true
								}
								if(PathsRowVector[i1] > SelectionRowVector[i2])
								{
									greaterthan = true; // if the value in PathsRowVector > the value of SelectionRowVector toggle greaterthan to true
								}
							}
							if(lessthan && !greaterthan && !equalto)
							{
								// push the value of paths onto the back of TempTreePathVector 
								// only if the value of PathsRowVector is less than and not equal
								// to or greater than any value in SelectionRowVector
								TempTreePathVector.push_back(paths[i1]); 
							}
							if(!lessthan && greaterthan && !equalto)
							{
								// push the value of paths onto the back of _Selection 
								// only if the value of PathsRowVector is greater than and not equal
								// to or less than any value in SelectionRowVector
								_Selection.push_back(paths[i1]);
								changeValues(_Selection);
							}
							// reset the toggles for next value of TempTreePathVector
							lessthan = false;
							greaterthan = false;
							equalto = false;
						}
						// push _Selection onto the back of TempTreePathVector
						TempTreePathVector.push_back(_Selection.front());

						// _Selection now contains the old selection plus all the new paths from the contiguous path that was added
						_Selection = TempTreePathVector;
						changeValues(_Selection);
					}
					else
					{
						break;
					}
				}
				break;
			case DISCONTIGUOUS_TREE_SELECTION:
				if (isPathSelected(paths)) // if _Selection contains the paths then nothing else is necessary
				{
					break;
				}
				else // otherwise add paths to _Selection
				{
					std::vector<UInt32> PathsRowVector; // create a dummy UInt vector variable called PathsRowVector
					PathsRowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values of paths into the elements of PathsRowVector
					
					std::vector<UInt32> SelectionRowVector; // create a dummy UInt vector variable called SelectionRowVector
					SelectionRowVector = _TreeRowMapper->getRowsForPaths(_Selection); // assign the row values of paths into the elements of SelectionRowVector
					
					bool equalto;  // dummy boolean variable that toggles to true when a value in PathsRowVector equals any value in SelectionRowVector

					equalto = false; // initialize dummy boolean variable

					for(UInt32 i1(0) ; i1<PathsRowVector.size() ; ++i1) // loop through PathRowsVector
					{
						for(UInt32 i2(0) ; i2<SelectionRowVector.size() ; ++i2) // loop through SelectionRowVector
						{
							if(PathsRowVector[i1] = SelectionRowVector[i2])
							{
								equalto = true; // if the value of PathsRowVector = any value of SelectionRowVector set to true
							}
						}
						if(!equalto)
						{
							// push the value of paths on to the back of _Selection
							// only if the value of PathsRowVector != any value of SelectionRowVector
							_Selection.push_back(paths[i1]); 
							changeValues(_Selection);
						}
						equalto = false; // reset toggles for next loop
					}
				}
				break;
		}
	}
}

void DefaultTreeSelectionModel::changeValues(std::vector<TreePath> paths)
{
	std::vector<UInt32> SelectionRowVector; // create a dummy UInt vector variable called SelectionRowVector
	SelectionRowVector = _TreeRowMapper->getRowsForPaths(_Selection); // assign the row values of paths into the elements of SelectionRowVector

	_LeadSelectionIndex = SelectionRowVector.back(); // set _LeadSelectionIndex to last element of _Selection
	_MaxSelectionIndex = SelectionRowVector.front(); // set _MaxSelectionIndex to first element of _Selection
	_MinSelectionIndex = SelectionRowVector.front(); // set _MaxSelectionIndex to first element of _Selection

	if(SelectionRowVector.size() > 0) // if the vector is empty then nothing further is needed
	{
		for(UInt32 i(0) ; i< SelectionRowVector.size() ; ++i) // loop through SelectionRowVector
		{
			if(SelectionRowVector[i] > _MaxSelectionIndex)
			{
				_MaxSelectionIndex = SelectionRowVector[i]; // set _MaxSelectionIndex to current element of SelectionRowVector if it is greater than current _MaxSelectionIndex
			}
			if(SelectionRowVector[i] < _MinSelectionIndex)
			{
				_MinSelectionIndex = SelectionRowVector[i]; // set _MinSelectionIndex to current element of SelectionRowVector if it is less than current _MinSelectionIndex
			}
		}
	}
}

void DefaultTreeSelectionModel::clearSelection(void)
{
	_Selection.clear(); // empties _Selection
	changeValues(_Selection);
}

TreePath DefaultTreeSelectionModel::getLeadSelectionPath(void) const
{
	return TreePath(SharedFieldPtr()); // returns the first path in _Selection
}

UInt32 DefaultTreeSelectionModel::getLeadSelectionRow(void) const
{
	return _LeadSelectionIndex; // returns the last element in _Selection
}

UInt32 DefaultTreeSelectionModel::getMaxSelectionRow(void) const
{
	return _MaxSelectionIndex; //Returns the largest value obtained from the TreeRowMapper for the current set of selected TreePaths.
}

UInt32 DefaultTreeSelectionModel::getMinSelectionRow(void) const
{
	return _MinSelectionIndex; //Returns the smallest value obtained from the TreeRowMapper for the current set of selected TreePaths.
}

TreeRowMapperPtr DefaultTreeSelectionModel::getRowMapper(void) const
{
	return _TreeRowMapper; // returns the current row from TreeRowMapper
}

UInt32 DefaultTreeSelectionModel::getSelectionCount(void) const
{
	return _Selection.size(); // returns the size of _Selection
}

UInt32 DefaultTreeSelectionModel::getSelectionMode(void) const
{
	return _SelectionMode;  // returns the current value of _SelectionMode, either SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION, or DISCONTIGUOUS_TREE_SELECTION
}

TreePath DefaultTreeSelectionModel::getSelectionPath(void) const
{
	return TreePath(SharedFieldPtr()); // returns the current selection path
}

std::vector<TreePath> DefaultTreeSelectionModel::getSelectionPaths(void) const
{
	return std::vector<TreePath>();  // returns the current selection paths
}

std::vector<UInt32> DefaultTreeSelectionModel::getSelectionRows(void) const
{
	return std::vector<UInt32>();  // returns the current rows within the selection
}

bool DefaultTreeSelectionModel::isPathSelected(std::vector<TreePath> paths) const
{
	std::vector<UInt32> PathsRowVector; // create a dummy UInt vector variable called PathsRowVector
	PathsRowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values of paths into the elements of PathsRowVector
					
	std::vector<UInt32> SelectionRowVector; // create a dummy UInt vector variable called SelectionRowVector
	SelectionRowVector = _TreeRowMapper->getRowsForPaths(_Selection); // assign the row values of paths into the elements of SelectionRowVector
	
	if(SelectionRowVector.size() >= PathsRowVector.size()) // if SelectionRowVector is smaller than PathsRowVector, the path is not fully selected
	{
		bool equalto = false; // dummy boolean variable

		for(UInt32 i1(0) ; i1<PathsRowVector.size() ; ++i1) // loop through each element of PathsRowVector
		{
			for(UInt32 i2(2) ; i2<SelectionRowVector.size() ; ++i2)  // loop through each element of PathsRowVector
			{
				if(PathsRowVector[i1] == SelectionRowVector[i2])
				{
					equalto = true; // toggle to true if the value of PathsRowVector equals any value of SelectionRowVector
				}
			}
			if(!equalto)
			{
				return false; // return false if the value of PathsRowVector does not equal any value of SelectionRowVector
			}
			else
			{
				equalto = false; // reset dummy boolean variable
			}
		}
		return true; // return true if all the values of PathsRowVector equal a corresponding value of SelectionRowVector
	}
	else
	{
		return false; // return false if _Selection is too small to contain the path
	}
}

bool DefaultTreeSelectionModel::arePathsContiguous(const std::vector<TreePath>& paths) const
{
	if(_TreeRowMapper != NULL) // only necessary to do anything if _TreeRowMapper is not empty
	{
		if(paths.size() > 1)
		{
			std::vector<UInt32> RowVector; // create a dummy UInt vector variable called RowVector
			RowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values into the elements of RowVector
			for(UInt32 i(1) ; i<RowVector.size() ; ++i)
			{
				if(RowVector[i] != RowVector[i-1] +1)
				{
					return false; // returns false if there is any row more that is more than 1 row apart from the previous row
				}
			}
		}
		return true; // returns true if _TreeRowMapper is not empty and if the path vector contains more than one element
	}
	else
	{
		return false; // returns false if _TreeRowMapper is empty
	}
}

bool DefaultTreeSelectionModel::arePathsContiguous(const std::vector<TreePath>& paths1, const std::vector<TreePath>& paths2) const
{
	if(_TreeRowMapper != NULL) // only necessary to do anything if _TreeRowMapper is not empty
	{
		if(paths1.size() >= 1 && paths2.size() >= 1)
		{
			std::vector<UInt32> RowVector1; // create a dummy UInt vector variable called RowVector1
			std::vector<UInt32> RowVector2; // create a dummy UInt vector variable called RowVector2
			RowVector1 = _TreeRowMapper->getRowsForPaths(paths1); // assign the row values from paths1 into the elements of RowVector1
			RowVector1 = _TreeRowMapper->getRowsForPaths(paths2); // assign the row values from paths2 into the elements of RowVector2
			for(UInt32 i1(0) ; i1<RowVector1.size() ; ++i1)
			{
				for(UInt32 i2(0) ; i2<RowVector2.size() ; ++i2)
				{
					if(RowVector1[i1] == RowVector2[i2] || RowVector1[i1] == RowVector2[i2] -1 || RowVector1[i1] == RowVector2[i2] +1)
					{
						return true; // returns true if there is any row in paths1 that is within one increment of any row of paths2
					}
					else
					{
						return false; // return false if there is no row in paths1 that is within one increment of any row of paths2
					}
				}
			}
		}
		else
		{
			return false; // return false if either paths1 or paths2 is empty
		}
	}
	else
	{
		return false; // returns false if _TreeRowMapper is empty
	}
}

bool DefaultTreeSelectionModel::isRowSelected(const UInt32& row) const
{
	// make sure the mapper is not empty
	if(_TreeRowMapper == NULL)
	{
		return false;  // if the mapper is empty, then the row must not be selected
	}

	// create a dummy UInt32 variable to check
	std::vector<UInt32> ResultRowVector;

	// create a dummy TreePath vector to hold value from the TreePath Selection vector
	std::vector<TreePath> TreePathVector;
	
	// loop through TreePath Selection vector
	for(SelectionVectorConstItor Iter = _Selection.begin(); Iter != _Selection.end(); ++Iter)
	{
		// clear dummy TreePath vector for every loop cycle
		TreePathVector.clear();

		// insert value into dummy TreePath vector
		TreePathVector.push_back((*Iter));

		ResultRowVector = _TreeRowMapper->getRowsForPaths(TreePathVector);

		if(ResultRowVector.front() == row)
		{
			return true;  // return true if the value of the ResultRowVector equals the row
		}
	}

	return false;  // return false if row is not selected
}

bool DefaultTreeSelectionModel::isSelectionEmpty(void) const
{
	return _Selection.empty();  // returns true if _Selection is empty
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
	if(!_Selection.empty() && !paths.empty()) // if either _Selection or paths is empty nothing else is necessary
	{
		std::vector<UInt32> TreePathRowVector; // create a dummy UInt vector variable called RowVector1
		std::vector<UInt32> SelectionRowVector; // create a dummy UInt vector variable called RowVector2
		TreePathRowVector = _TreeRowMapper->getRowsForPaths(paths); // assign the row values from paths1 into the elements of RowVector1
		SelectionRowVector = _TreeRowMapper->getRowsForPaths(_Selection); // assign the row values from paths2 into the elements of RowVector2
		
		std::vector<TreePath> _TempSelection;  // temporary TreePath vector to store the TreePaths not to be removed from _Selection
		
		bool ToBeRemoved = false; // dummy boolean variable to toggle

		for(UInt32 i1(0) ; i1<SelectionRowVector.size() ; ++i1) // loop through all the values of SelectionRowVector
		{
			for(UInt32 i2(0) ; i2<TreePathRowVector.size() ; ++i2) // loop through all the values of TreePathRowVector
			{
				if(TreePathRowVector[i2] == SelectionRowVector[i1])
				{
					ToBeRemoved = true; // toggle to true if the value of TreePathRowVector equals the value of SelectionRowVector
				}
			}
			if(!ToBeRemoved)
			{
				_TempSelection.push_back(_Selection[i1]); // push the value of _Selection on to the back of _TempSelection only if ToBeRemoved is false
			}
			ToBeRemoved = false; // reset dummy boolean toggle to false for next value of TreePathRowVector
		}
		_Selection.clear(); // empties _Selection in preparation for next step
		_Selection = _TempSelection; // copies _TempSelection into _Selection
		changeValues(_Selection);
	}
}

//void DefaultTreeSelectionModel::resetRowSelection(void)
//{
	// Not sure what this function does
//}

void DefaultTreeSelectionModel::setRowMapper(TreeRowMapperPtr newMapper)
{
	// Not sure how to do this
}

void DefaultTreeSelectionModel::setSelectionMode(const UInt32& mode)
{
	//TODO: Implement
	_SelectionMode = static_cast<TreeSelectionMode>(mode);
	// if there were objects selected, since they might not fit into
	// the new mode, just clear them all out
	if (!_Selection.empty())
	{   // only necessary to do anything if it isn't already empty
		_Selection.clear();
		changeValues(_Selection);
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
	if(paths.size()>0)
	{
		switch (_SelectionMode) // determine if _Selection mode is SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION, or DISCONTIGUOUS_TREE_SELECTION and handle appropriately
		{
			case SINGLE_TREE_SELECTION:
			case DISCONTIGUOUS_TREE_SELECTION:
				if(_Selection.empty()) // if _Selection is empty you just need to push the paths onto the end
				{
					_Selection.push_back(paths.back()); // add paths to _Selection
					changeValues(_Selection);
				}
				else // clear _Selection and push the path onto the end
				{
					_Selection.clear(); // clear _Selection
					_Selection.push_back(paths.back()); // push the path on to the back of the now emptied _Selection
					changeValues(_Selection);
				}
				break;
			case CONTIGUOUS_TREE_SELECTION: 
				if(arePathsContiguous(paths)) // check whether the path is contiguous before continuing
				{
					if(_Selection.empty()) // if _Selection is empty you just need to push the paths onto the end
					{
						_Selection.push_back(paths.back()); // add paths to _Selection
						changeValues(_Selection);
					}
					else // clear _Selection and push the path onto the end
					{
						_Selection.clear(); // clear _Selection
						_Selection.push_back(paths.back()); // push the path on to the back of the now emptied _Selection
						changeValues(_Selection);
					}
				}				
				break;			
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

