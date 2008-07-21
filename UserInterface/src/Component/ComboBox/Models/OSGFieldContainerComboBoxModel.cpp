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
#include <OpenSG/OSGFieldContainerFactory.h>

#include "OSGFieldContainerComboBoxModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FieldContainerComboBoxModel
A UI FieldContainerComboBoxModel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerComboBoxModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 FieldContainerComboBoxModel::getSize(void) const
{
	return _FieldList.size();
}

SharedFieldPtr FieldContainerComboBoxModel::getElementAt(UInt32 index) const
{
   return _FieldList[index];
}

SharedFieldPtr FieldContainerComboBoxModel::getSelectedItem(void) const
{
	if(_SelectedIndex < 0 ||
	   _SelectedIndex >= _FieldList.size())
	{
		return SharedFieldPtr();
	}
	else
	{
		return _FieldList[_SelectedIndex];
	}
}

Int32 FieldContainerComboBoxModel::getSelectedItemIndex(void) const
{
	return _SelectedIndex;
}

void FieldContainerComboBoxModel::setSelectedItem(const Int32& index)
{
	if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);
		_SelectedIndex = index;

		if(_SelectedIndex != PreviousIndex)
		{
			produceSelectionChanged(FieldContainerComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
		}
	}
}

void FieldContainerComboBoxModel::setSelectedItem(SharedFieldPtr anObject)
{
	if(getSize() != 0)
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
			produceSelectionChanged(FieldContainerComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldContainerComboBoxModel::FieldContainerComboBoxModel(void) :
    Inherited()
{
}

FieldContainerComboBoxModel::FieldContainerComboBoxModel(const FieldContainerComboBoxModel &source) :
    Inherited(source)
{
}

FieldContainerComboBoxModel::~FieldContainerComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldContainerComboBoxModel::changed(BitVector whichField, UInt32 origin)
{

    Inherited::changed(whichField, origin);
    if(whichField & FieldContainerTypesFieldMask)
    {
        _FieldList.clear();
        for(UInt32 i(0) ; i<getFieldContainerTypes().size() ; ++i)
        {
            FieldContainerType* FoundType = FieldContainerFactory::the()->findType(getFieldContainerTypes()[i].c_str());
            if(FoundType != NULL && (getIncludeAbstract() || !FoundType->isAbstract()))
            {

                 _FieldList.push_back(SharedFieldPtr(new SFString(FoundType->getCName())));
            }
        }
        produceListDataContentsChanged(FieldContainerComboBoxModelPtr(this), 0, _FieldList.size());
        setSelectedItem(-1);
    }
}



void FieldContainerComboBoxModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerComboBoxModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFIELDCONTAINERCOMBOBOXMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFIELDCONTAINERCOMBOBOXMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFIELDCONTAINERCOMBOBOXMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

