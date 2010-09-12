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

#include "OSGMouseWheelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMouseWheelEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGMouseWheelEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MouseWheelEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

MouseWheelEventDetailsTransitPtr MouseWheelEventDetails::create(FieldContainer* const Source,
                                                                Time TimeStamp,
                                                                Int32 WheelRotation,
                                                                UInt8 TheScrollType,
                                                                UInt8 ScrollOrientation,
                                                                Pnt2f Location,
                                                                Viewport* const TheViewport)
{
    MouseWheelEventDetails* TheEventDetails = MouseWheelEventDetails::createUnregistered();

    TheEventDetails->setSource           (Source           );
    TheEventDetails->setTimeStamp        (TimeStamp        );
    TheEventDetails->setWheelRotation    (WheelRotation    );
    TheEventDetails->setScrollType       (TheScrollType    );
    TheEventDetails->setScrollOrientation(ScrollOrientation);
    TheEventDetails->setLocation         (Location         );
    TheEventDetails->setViewport         (TheViewport      );

    return MouseWheelEventDetailsTransitPtr(TheEventDetails);
}
MouseWheelEventDetailsTransitPtr MouseWheelEventDetails::create(MouseWheelEventDetails* const Details,
                                                                FieldContainer*         const NewSource)
{
    MouseWheelEventDetails* TheEventDetails = MouseWheelEventDetails::createUnregistered();

    TheEventDetails->setSource           (NewSource                      );
    TheEventDetails->setTimeStamp        (Details->getTimeStamp()        );
    TheEventDetails->setWheelRotation    (Details->getWheelRotation()    );
    TheEventDetails->setScrollType       (Details->getScrollType()       );
    TheEventDetails->setScrollOrientation(Details->getScrollOrientation());
    TheEventDetails->setLocation         (Details->getLocation()         );
    TheEventDetails->setViewport         (Details->getViewport()         );

    return MouseWheelEventDetailsTransitPtr(TheEventDetails);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MouseWheelEventDetails::MouseWheelEventDetails(void) :
    Inherited()
{
}

MouseWheelEventDetails::MouseWheelEventDetails(const MouseWheelEventDetails &source) :
    Inherited(source)
{
}

MouseWheelEventDetails::~MouseWheelEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MouseWheelEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MouseWheelEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MouseWheelEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
