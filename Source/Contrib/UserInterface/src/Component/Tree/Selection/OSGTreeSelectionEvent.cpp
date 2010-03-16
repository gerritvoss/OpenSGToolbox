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

#include "OSGTreeSelectionEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeSelectionEventBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeSelectionEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeSelectionEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

TreeSelectionEventTransitPtr TreeSelectionEvent::create(  FieldContainerRefPtr Source,
                                                          Time TimeStamp,
                                                          const std::vector<NumberRange>& ElementsChanged,
                                                          Int32 NewLeadSelectionPath,
                                                          Int32 OldLeadSelectionPath)
{
    TreeSelectionEvent* TheEvent = TreeSelectionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setNewLeadSelectionPath(NewLeadSelectionPath);
    TheEvent->setOldLeadSelectionPath(OldLeadSelectionPath);
    TheEvent->editMFElementsChanged()->resize(ElementsChanged.size());
    for(UInt32 i(0) ; i<ElementsChanged.size() ; ++i)
    {
        (*TheEvent->editMFElementsChanged())[i] = Vec2s(ElementsChanged[i].getMin(), ElementsChanged[i].getMax());
    }

    return TreeSelectionEventTransitPtr(TheEvent);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeSelectionEvent::TreeSelectionEvent(void) :
    Inherited()
{
}

TreeSelectionEvent::TreeSelectionEvent(const TreeSelectionEvent &source) :
    Inherited(source)
{
}

TreeSelectionEvent::~TreeSelectionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeSelectionEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeSelectionEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeSelectionEvent NI" << std::endl;
}

OSG_END_NAMESPACE
