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

#include "OSGAbstractListModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractListModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractListModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractListModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbstractListModel::produceListDataContentsChanged(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataContentsChanged(Details);
}

void AbstractListModel::produceListDataIntervalAdded(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataIntervalAdded(Details);
}

void AbstractListModel::produceListDataIntervalRemoved(FieldContainer* const Source, UInt32 index0, UInt32 index1)
{
    ListDataEventDetailsUnrecPtr Details = ListDataEventDetails::create(Source, getSystemTime(), index0, index1);

    Inherited::produceListDataIntervalRemoved(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractListModel::AbstractListModel(void) :
    Inherited()
{
}

AbstractListModel::AbstractListModel(const AbstractListModel &source) :
    Inherited(source)
{
}

AbstractListModel::~AbstractListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractListModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractListModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractListModel NI" << std::endl;
}

OSG_END_NAMESPACE
