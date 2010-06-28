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

#include "OSGTreeModelEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeModelEventBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeModelEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeModelEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

TreeModelEventTransitPtr TreeModelEvent::create(  FieldContainerRefPtr Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath,
                                           const std::vector<UInt32>& childIndices,
                                           const std::vector<boost::any>& children)
{
    TreeModelEvent* TheEvent = TreeModelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->editMFChildIndices()->setValues(childIndices);
    TheEvent->_Path     = ThePath;
    TheEvent->_Children = children;

    return TreeModelEventTransitPtr(TheEvent);
}

TreeModelEventTransitPtr TreeModelEvent::create(  FieldContainerRefPtr Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath)
{
    TreeModelEvent* TheEvent = TreeModelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->_Path     = ThePath;

    return TreeModelEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TreePath TreeModelEvent::getChildPath(UInt32 index) const
{
    return TreePath(getPath(), _Children[index]);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeModelEvent::TreeModelEvent(void) :
    Inherited()
{
}

TreeModelEvent::TreeModelEvent(const TreeModelEvent &source) :
    Inherited(source)
{
}

TreeModelEvent::~TreeModelEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeModelEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeModelEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeModelEvent NI" << std::endl;
}

OSG_END_NAMESPACE
