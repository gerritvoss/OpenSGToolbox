/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGComboBoxSelectionEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComboBoxSelectionEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComboBoxSelectionEvent::initMethod (void)
{
}

ComboBoxSelectionEventPtr ComboBoxSelectionEvent::create(  FieldContainerPtr Source,
                                                           Time TimeStamp,
                                                           Int32 CurrentIndex,
                                                           Int32 PreviousIndex)
{
    ComboBoxSelectionEventPtr TheEvent = ComboBoxSelectionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setCurrentIndex(CurrentIndex);
    TheEvent->setPreviousIndex(PreviousIndex);

    return TheEvent;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComboBoxSelectionEvent::ComboBoxSelectionEvent(void) :
    Inherited()
{
}

ComboBoxSelectionEvent::ComboBoxSelectionEvent(const ComboBoxSelectionEvent &source) :
    Inherited(source)
{
}

ComboBoxSelectionEvent::~ComboBoxSelectionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComboBoxSelectionEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ComboBoxSelectionEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComboBoxSelectionEvent NI" << std::endl;
}


OSG_END_NAMESPACE

