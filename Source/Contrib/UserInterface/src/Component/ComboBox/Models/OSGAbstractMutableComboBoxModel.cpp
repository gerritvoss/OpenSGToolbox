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

#include "OSGAbstractMutableComboBoxModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractMutableComboBoxModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractMutableComboBoxModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractMutableComboBoxModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbstractMutableComboBoxModel::produceListDataContentsChanged(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataContentsChanged(Details);
}

void AbstractMutableComboBoxModel::produceListDataIntervalAdded(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataIntervalAdded(Details);
}

void AbstractMutableComboBoxModel::produceListDataIntervalRemoved(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataIntervalRemoved(Details);
}

void AbstractMutableComboBoxModel::produceSelectionChanged(FieldContainer* const Source, const Int32& CurrentIndex, const Int32& PreviousIndex)
{
    ComboBoxSelectionEventDetailsUnrecPtr Details = ComboBoxSelectionEventDetails::create(Source, getSystemTime(), CurrentIndex, PreviousIndex);

    Inherited::produceSelectionChanged(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractMutableComboBoxModel::AbstractMutableComboBoxModel(void) :
    Inherited()
{
}

AbstractMutableComboBoxModel::AbstractMutableComboBoxModel(const AbstractMutableComboBoxModel &source) :
    Inherited(source)
{
}

AbstractMutableComboBoxModel::~AbstractMutableComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractMutableComboBoxModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractMutableComboBoxModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractMutableComboBoxModel NI" << std::endl;
}

OSG_END_NAMESPACE
