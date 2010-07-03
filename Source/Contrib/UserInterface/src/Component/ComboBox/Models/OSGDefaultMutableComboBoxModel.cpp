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

#include "OSGDefaultMutableComboBoxModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultMutableComboBoxModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultMutableComboBoxModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultMutableComboBoxModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 DefaultMutableComboBoxModel::getSize(void) const
{
	return _FieldList.size();
}

boost::any DefaultMutableComboBoxModel::getElementAt(UInt32 index) const
{
   return _FieldList[index];
}

boost::any DefaultMutableComboBoxModel::getSelectedItem(void) const
{
	if(_SelectedIndex < 0 ||
	   _SelectedIndex >= _FieldList.size())
	{
        return boost::any();
	}
	else
	{
		return _FieldList[_SelectedIndex];
	}
}

Int32 DefaultMutableComboBoxModel::getSelectedItemIndex(void) const
{
	return _SelectedIndex;
}

void DefaultMutableComboBoxModel::setSelectedItem(const Int32& index)
{
	if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);
		_SelectedIndex = index;

		if(_SelectedIndex != PreviousIndex)
		{
			produceSelectionChanged(this, _SelectedIndex, PreviousIndex);
		}
	}
}

void DefaultMutableComboBoxModel::setSelectedItem(const boost::any& anObject)
{
    assert(false);
	/*if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);

		UInt32 index(0);
		while(index < _FieldList.size() && _FieldList[index] != anObject)
		{
			++index;
		}

		if(index < _FieldList.size())
		{
			_SelectedIndex = index;
		}
		else
		{
			_SelectedIndex = -1;
		}

		if(_SelectedIndex != PreviousIndex)
		{
			produceSelectionChanged(this, _SelectedIndex, PreviousIndex);
		}
	}
    */
}

void DefaultMutableComboBoxModel::addElement(const boost::any& anObject)
{
	_FieldList.push_back(anObject);
	produceListDataIntervalAdded(this,_FieldList.size()-1,_FieldList.size()-1);
}

void DefaultMutableComboBoxModel::insertElementAt(const boost::any& anObject, const UInt32& index)
{
	if(index < _FieldList.size())
	{
		_FieldList.insert(_FieldList.begin()+index, anObject);
		produceListDataIntervalAdded(this,index,index);
	}
	else
	{
		addElement(anObject);
	}
}

void DefaultMutableComboBoxModel::removeAllElements(void)
{
	UInt32 Size(_FieldList.size());
	_FieldList.clear();
	produceListDataIntervalRemoved(this,0,Size-1);
}

void DefaultMutableComboBoxModel::removeElement(const boost::any& anObject)
{
    assert(false);
	/*std::vector<boost::any>::iterator SearchItor(std::find(_FieldList.begin(), _FieldList.end(), anObject));

	if(SearchItor != _FieldList.end())
	{
		UInt32 Index(SearchItor - _FieldList.begin());
		_FieldList.erase(SearchItor);
		produceListDataIntervalRemoved(this,Index,Index);
	}*/


}

void DefaultMutableComboBoxModel::removeElementAt(const UInt32& index)
{
	if(index < _FieldList.size())
	{
		_FieldList.erase(_FieldList.begin()+index);
		produceListDataIntervalRemoved(this,index,index);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultMutableComboBoxModel::DefaultMutableComboBoxModel(void) :
    Inherited(),
    _SelectedIndex(-1)
{
}

DefaultMutableComboBoxModel::DefaultMutableComboBoxModel(const DefaultMutableComboBoxModel &source) :
    Inherited(source),
    _SelectedIndex(source._SelectedIndex)
{
}

DefaultMutableComboBoxModel::~DefaultMutableComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultMutableComboBoxModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultMutableComboBoxModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultMutableComboBoxModel NI" << std::endl;
}

OSG_END_NAMESPACE
