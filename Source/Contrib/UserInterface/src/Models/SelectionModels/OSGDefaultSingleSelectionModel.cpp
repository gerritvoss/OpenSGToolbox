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

#include "OSGDefaultSingleSelectionModel.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultSingleSelectionModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultSingleSelectionModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultSingleSelectionModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultSingleSelectionModel::clearSelection(void)
{
    if(getInternalSelectedIndex() != -1)
    {
        setSelectedIndex(-1);
    }
}

Int32 DefaultSingleSelectionModel::getSelectedIndex(void)
{
    return getInternalSelectedIndex();
}

bool DefaultSingleSelectionModel::isSelected(void)
{
    return getInternalSelectedIndex() != -1;
}

void DefaultSingleSelectionModel::setSelectedIndex(Int32 index)
{
    if(getInternalSelectedIndex() != index)
    {
        Int32 PreviousSelection(getSelectedIndex());
        setInternalSelectedIndex(index);

        produceSelectionChanged(getSelectedIndex(), PreviousSelection);
    }
}

void DefaultSingleSelectionModel::produceSelectionChanged(const Int32& SelectedIndex, const Int32& PreviouslySelectedIndex)
{
    std::vector<UInt32> Selected;
    if(SelectedIndex != -1)
    {
        Selected.push_back(SelectedIndex);
    }
    std::vector<UInt32> PreviouslySelected;
    if(PreviouslySelectedIndex != -1)
    {
        PreviouslySelected.push_back(PreviouslySelectedIndex);
    }

    SelectionEventDetailsUnrecPtr Details = SelectionEventDetails::create(this, getTimeStamp(), Selected, PreviouslySelected, false);
   
    Inherited::produceSelectionChanged(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultSingleSelectionModel::DefaultSingleSelectionModel(void) :
    Inherited()
{
}

DefaultSingleSelectionModel::DefaultSingleSelectionModel(const DefaultSingleSelectionModel &source) :
    Inherited(source)
{
}

DefaultSingleSelectionModel::~DefaultSingleSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultSingleSelectionModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultSingleSelectionModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultSingleSelectionModel NI" << std::endl;
}

OSG_END_NAMESPACE
