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

#include "OSGTableModelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableModelEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGTableModelEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableModelEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

TableModelEventDetailsTransitPtr TableModelEventDetails::create(  FieldContainer* const Source,
                                             Time TimeStamp,
                                             UInt32 FirstColumn,
                                             UInt32 LastColumn,
                                             UInt32 FirstRow,
                                             UInt32 LastRow)
{
    TableModelEventDetails* TheEventDetails = TableModelEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setFirstColumn(FirstColumn);
    TheEventDetails->setLastColumn(LastColumn);
    TheEventDetails->setFirstRow(FirstRow);
    TheEventDetails->setLastRow(LastRow);

    return TableModelEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableModelEventDetails::TableModelEventDetails(void) :
    Inherited()
{
}

TableModelEventDetails::TableModelEventDetails(const TableModelEventDetails &source) :
    Inherited(source)
{
}

TableModelEventDetails::~TableModelEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TableModelEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TableModelEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableModelEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
