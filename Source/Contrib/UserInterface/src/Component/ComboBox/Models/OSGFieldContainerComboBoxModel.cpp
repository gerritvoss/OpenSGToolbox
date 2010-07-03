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

#include "OSGFieldContainerComboBoxModel.h"
#include "OSGFieldContainerFactory.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldContainerComboBoxModelBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldContainerComboBoxModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerComboBoxModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 FieldContainerComboBoxModel::getSize(void) const
{
	return _FieldList.size();
}

boost::any FieldContainerComboBoxModel::getElementAt(UInt32 index) const
{
   return _FieldList[index];
}

boost::any FieldContainerComboBoxModel::getSelectedItem(void) const
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
			produceSelectionChanged(this, _SelectedIndex, PreviousIndex);
		}
	}
}

void FieldContainerComboBoxModel::setSelectedItem(const boost::any& anObject)
{
	if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);

		UInt32 index(0);
        try
        {
            while(index < _FieldList.size() && 
                *boost::any_cast<FieldContainerType*>(_FieldList[index]) != *boost::any_cast<FieldContainerType*>(anObject))
		    {
			    ++index;
		    }
        }
        catch(boost::bad_any_cast &)
        {
            return;
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

void FieldContainerComboBoxModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(whichField & FieldContainerTypesFieldMask)
    {
        UInt32 PreListSize(_FieldList.size());
        _FieldList.clear();
        for(UInt32 i(0) ; i<getMFFieldContainerTypes()->size() ; ++i)
        {
            FieldContainerType* FoundType =
                FieldContainerFactory::the()->findType(getFieldContainerTypes(i).c_str());
            if(FoundType != NULL && (getIncludeAbstract() || !FoundType->isAbstract()))
            {

                _FieldList.push_back(boost::any(FoundType));
            }
        }
        produceListDataContentsChanged(this, 0, osgMax<UInt32>(PreListSize,_FieldList.size()));
        setSelectedItem(-1);
    }
}

void FieldContainerComboBoxModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerComboBoxModel NI" << std::endl;
}

OSG_END_NAMESPACE
