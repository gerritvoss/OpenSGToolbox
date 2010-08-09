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

#include "OSGDialogWindowEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDialogWindowEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGDialogWindowEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogWindowEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

DialogWindowEventDetailsTransitPtr DialogWindowEventDetails::create( FieldContainer* const Source,
                                                       Time TimeStamp,
                                                       UInt32 Option,
                                                       const std::string& Input,
                                                       UInt32 InputIndex)
{
    DialogWindowEventDetails* TheEventDetails = DialogWindowEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setOption(Option);
    TheEventDetails->setInput(Input);
    TheEventDetails->setInputIndex(InputIndex);

    return DialogWindowEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogWindowEventDetails::DialogWindowEventDetails(void) :
    Inherited()
{
}

DialogWindowEventDetails::DialogWindowEventDetails(const DialogWindowEventDetails &source) :
    Inherited(source)
{
}

DialogWindowEventDetails::~DialogWindowEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogWindowEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DialogWindowEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DialogWindowEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
