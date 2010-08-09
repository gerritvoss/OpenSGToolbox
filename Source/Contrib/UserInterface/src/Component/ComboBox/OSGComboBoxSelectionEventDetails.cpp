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

#include "OSGComboBoxSelectionEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComboBoxSelectionEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGComboBoxSelectionEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComboBoxSelectionEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ComboBoxSelectionEventDetailsTransitPtr ComboBoxSelectionEventDetails::create(FieldContainer* const Source,
                                                                Time TimeStamp,
                                                                Int32 CurrentIndex,
                                                                Int32 PreviousIndex)
{
    ComboBoxSelectionEventDetails* TheEventDetails = ComboBoxSelectionEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setCurrentIndex(CurrentIndex);
    TheEventDetails->setPreviousIndex(PreviousIndex);

    return ComboBoxSelectionEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComboBoxSelectionEventDetails::ComboBoxSelectionEventDetails(void) :
    Inherited()
{
}

ComboBoxSelectionEventDetails::ComboBoxSelectionEventDetails(const ComboBoxSelectionEventDetails &source) :
    Inherited(source)
{
}

ComboBoxSelectionEventDetails::~ComboBoxSelectionEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComboBoxSelectionEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ComboBoxSelectionEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComboBoxSelectionEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
