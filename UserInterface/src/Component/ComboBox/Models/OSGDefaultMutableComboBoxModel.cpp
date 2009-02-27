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

#include "OSGDefaultMutableComboBoxModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultMutableComboBoxModel
A UI DefaultMutableComboBoxModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultMutableComboBoxModel::initMethod (void)
{
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
			produceSelectionChanged(DefaultMutableComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
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
			produceSelectionChanged(DefaultMutableComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
		}
	}
    */
}

void DefaultMutableComboBoxModel::addElement(const boost::any& anObject)
{
	_FieldList.push_back(anObject);
	produceListDataIntervalAdded(DefaultMutableComboBoxModelPtr(this),_FieldList.size()-1,_FieldList.size()-1);
}

void DefaultMutableComboBoxModel::insertElementAt(const boost::any& anObject, const UInt32& index)
{
	if(index < _FieldList.size())
	{
		_FieldList.insert(_FieldList.begin()+index, anObject);
		produceListDataIntervalAdded(DefaultMutableComboBoxModelPtr(this),index,index);
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
	produceListDataIntervalRemoved(DefaultMutableComboBoxModelPtr(this),0,Size-1);
}

void DefaultMutableComboBoxModel::removeElement(const boost::any& anObject)
{
    assert(false);
	/*std::vector<boost::any>::iterator SearchItor(std::find(_FieldList.begin(), _FieldList.end(), anObject));

	if(SearchItor != _FieldList.end())
	{
		UInt32 Index(SearchItor - _FieldList.begin());
		_FieldList.erase(SearchItor);
		produceListDataIntervalRemoved(DefaultMutableComboBoxModelPtr(this),Index,Index);
	}*/


}

void DefaultMutableComboBoxModel::removeElementAt(const UInt32& index)
{
	if(index < _FieldList.size())
	{
		_FieldList.erase(_FieldList.begin()+index);
		produceListDataIntervalRemoved(DefaultMutableComboBoxModelPtr(this),index,index);
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

void DefaultMutableComboBoxModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultMutableComboBoxModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultMutableComboBoxModel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDEFAULTMUTABLECOMBOBOXMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTMUTABLECOMBOBOXMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTMUTABLECOMBOBOXMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

