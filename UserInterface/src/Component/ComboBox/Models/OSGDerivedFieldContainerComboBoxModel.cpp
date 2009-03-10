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

#include "OSGDerivedFieldContainerComboBoxModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DerivedFieldContainerComboBoxModel
A UI DerivedFieldContainerComboBoxModel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DerivedFieldContainerComboBoxModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 DerivedFieldContainerComboBoxModel::getSize(void) const
{
	return _FieldList.size();
}

boost::any DerivedFieldContainerComboBoxModel::getElementAt(UInt32 index) const
{
   return _FieldList[index];
}

boost::any DerivedFieldContainerComboBoxModel::getSelectedItem(void) const
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

Int32 DerivedFieldContainerComboBoxModel::getSelectedItemIndex(void) const
{
	return _SelectedIndex;
}

void DerivedFieldContainerComboBoxModel::setSelectedItem(const Int32& index)
{
	if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);
		_SelectedIndex = index;

		if(_SelectedIndex != PreviousIndex)
		{
			produceSelectionChanged(DerivedFieldContainerComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
		}
	}
}

void DerivedFieldContainerComboBoxModel::setSelectedItem(const boost::any& anObject)
{
	if(getSize() != 0)
	{
		Int32 PreviousIndex(_SelectedIndex);

		UInt32 index(0);
        try
        {
            while(index < _FieldList.size() && 
                *boost::any_cast<FieldContainerType*>(_FieldList[index]) == *boost::any_cast<FieldContainerType*>(anObject))
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
			produceSelectionChanged(DerivedFieldContainerComboBoxModelPtr(this), _SelectedIndex, PreviousIndex);
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DerivedFieldContainerComboBoxModel::DerivedFieldContainerComboBoxModel(void) :
    Inherited()
{
}

DerivedFieldContainerComboBoxModel::DerivedFieldContainerComboBoxModel(const DerivedFieldContainerComboBoxModel &source) :
    Inherited(source)
{
}

DerivedFieldContainerComboBoxModel::~DerivedFieldContainerComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DerivedFieldContainerComboBoxModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if(whichField & DerivedFieldContainerTypesFieldMask)
    {
        beginEditCP(DerivedFieldContainerComboBoxModelPtr(this), InternalFieldContainerTypesFieldMask);
            getInternalFieldContainerTypes().clear();
            for(UInt32 i(0) ; i<getDerivedFieldContainerTypes().size() ; ++i)
            {
                UInt32 NumFieldContainersFound(0);
                FieldContainerType* DerivedType = FieldContainerFactory::the()->findType(getDerivedFieldContainerTypes()[i].c_str());
                FieldContainerType* FoundType = NULL;
                if(DerivedType != NULL)
                {
                    for(UInt32 j(0) ; NumFieldContainersFound<FieldContainerFactory::the()->getNumTypes(); ++j)
                    {
                        FoundType = FieldContainerFactory::the()->findType(j);
                        if(FoundType != NULL)
                        {
                            if(FoundType->isDerivedFrom(*DerivedType)  && (getIncludeAbstract() || !FoundType->isAbstract()))
                            {
                                getInternalFieldContainerTypes().push_back(FoundType->getId());
                            }
                            ++NumFieldContainersFound;
                        }
                    }
                }
            }
        endEditCP(DerivedFieldContainerComboBoxModelPtr(this), InternalFieldContainerTypesFieldMask);
    }
    
    if(whichField & InternalFieldContainerTypesFieldMask)
    {
        UInt32 PreListSize(_FieldList.size());
        _FieldList.clear();

        for(UInt32 i(0) ; i<getInternalFieldContainerTypes().size() ; ++i)
        {
            _FieldList.push_back(boost::any(FieldContainerFactory::the()->findType(getInternalFieldContainerTypes()[i])));
        }

        produceListDataContentsChanged(DerivedFieldContainerComboBoxModelPtr(this), 0, osgMax(PreListSize,_FieldList.size()));
        setSelectedItem(-1);
    }
}

void DerivedFieldContainerComboBoxModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DerivedFieldContainerComboBoxModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

