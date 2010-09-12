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

#include "OSGWindowEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGWindowEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGWindowEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

WindowEventDetailsTransitPtr WindowEventDetails::create(FieldContainer* const Source,
                                                        Time TimeStamp)
{
    WindowEventDetails* TheEventDetails = WindowEventDetails::createUnregistered();

    TheEventDetails->setSource   (Source   );
    TheEventDetails->setTimeStamp(TimeStamp);

    return WindowEventDetailsTransitPtr(TheEventDetails);
}

WindowEventDetailsTransitPtr WindowEventDetails::create(WindowEventDetails* const Details,
                                                        FieldContainer*     const NewSource)
{
    WindowEventDetails* TheEventDetails = WindowEventDetails::createUnregistered();

    TheEventDetails->setSource   (NewSource              );
    TheEventDetails->setTimeStamp(Details->getTimeStamp());

    return WindowEventDetailsTransitPtr(TheEventDetails);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowEventDetails::WindowEventDetails(void) :
    Inherited()
{
}

WindowEventDetails::WindowEventDetails(const WindowEventDetails &source) :
    Inherited(source)
{
}

WindowEventDetails::~WindowEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WindowEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void WindowEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump WindowEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
