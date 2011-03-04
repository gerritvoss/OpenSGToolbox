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

#include "OSGDerivedFieldContainerComboBoxModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDerivedFieldContainerComboBoxModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDerivedFieldContainerComboBoxModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DerivedFieldContainerComboBoxModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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
            produceSelectionChanged(this, _SelectedIndex, PreviousIndex);
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

DerivedFieldContainerComboBoxModel::DerivedFieldContainerComboBoxModel(void) :
    Inherited(),
    _SelectedIndex(-1)
{
}

DerivedFieldContainerComboBoxModel::DerivedFieldContainerComboBoxModel(const DerivedFieldContainerComboBoxModel &source) :
    Inherited(source),
    _SelectedIndex(-1)
{
}

DerivedFieldContainerComboBoxModel::~DerivedFieldContainerComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DerivedFieldContainerComboBoxModel::changed(ConstFieldMaskArg whichField, 
                                                 UInt32            origin,
                                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & DerivedFieldContainerTypesFieldMask)
    {
        editMFInternalFieldContainerTypes()->clear();
        for(UInt32 i(0) ; i<getMFDerivedFieldContainerTypes()->size() ; ++i)
        {
            UInt32 NumFieldContainersFound(0);
            FieldContainerType* DerivedType =
                FieldContainerFactory::the()->findType(getDerivedFieldContainerTypes(i).c_str());
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
                            editMFInternalFieldContainerTypes()->push_back(FoundType->getId());
                        }
                        ++NumFieldContainersFound;
                    }
                }
            }
        }
    }

    if(whichField & InternalFieldContainerTypesFieldMask)
    {
        UInt32 PreListSize(_FieldList.size());
        _FieldList.clear();

        for(UInt32 i(0) ; i<getMFInternalFieldContainerTypes()->size() ; ++i)
        {
            _FieldList.push_back(boost::any(FieldContainerFactory::the()->findType(getInternalFieldContainerTypes(i))));
        }

        produceListDataContentsChanged(this, 0, osgMax<UInt32>(PreListSize,_FieldList.size()));
        setSelectedItem(-1);
    }
}

void DerivedFieldContainerComboBoxModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DerivedFieldContainerComboBoxModel NI" << std::endl;
}

OSG_END_NAMESPACE
