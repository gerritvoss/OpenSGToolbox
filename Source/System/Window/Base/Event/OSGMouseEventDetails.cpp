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

#include "OSGMouseEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMouseEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGMouseEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MouseEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

MouseEventDetailsTransitPtr MouseEventDetails::create(FieldContainer* const Source,
                                                      Time TimeStamp,
                                                      UInt16 Button,
                                                      UInt16 ClickCount,
                                                      Pnt2f Location,
                                                      Viewport* const TheViewport,
                                                      Vec2f Delta)
{
    MouseEventDetails* TheEventDetails = MouseEventDetails::createUnregistered();

    TheEventDetails->setSource    (Source     );
    TheEventDetails->setTimeStamp (TimeStamp  );
    TheEventDetails->setButton    (Button     );
    TheEventDetails->setClickCount(ClickCount );
    TheEventDetails->setLocation  (Location   );
    TheEventDetails->setViewport  (TheViewport);
    TheEventDetails->setDelta     (Delta      );

    return MouseEventDetailsTransitPtr(TheEventDetails);
}

MouseEventDetailsTransitPtr MouseEventDetails::create(MouseEventDetails* const Details,
                                                      FieldContainer*    const NewSource)
{
    MouseEventDetails* TheEventDetails = MouseEventDetails::createUnregistered();

    TheEventDetails->setSource    (NewSource               );
    TheEventDetails->setTimeStamp (Details->getTimeStamp() );
    TheEventDetails->setButton    (Details->getButton()    );
    TheEventDetails->setClickCount(Details->getClickCount());
    TheEventDetails->setLocation  (Details->getLocation()  );
    TheEventDetails->setViewport  (Details->getViewport()  );
    TheEventDetails->setDelta     (Details->getDelta()     );

    return MouseEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MouseEventDetails::MouseEventDetails(void) :
    Inherited()
{
}

MouseEventDetails::MouseEventDetails(const MouseEventDetails &source) :
    Inherited(source)
{
}

MouseEventDetails::~MouseEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MouseEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MouseEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MouseEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
