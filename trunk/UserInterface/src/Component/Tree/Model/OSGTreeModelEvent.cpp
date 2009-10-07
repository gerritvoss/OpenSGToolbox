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

#include "OSGTreeModelEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TreeModelEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeModelEvent::initMethod (void)
{
}

TreeModelEventPtr TreeModelEvent::create(  FieldContainerPtr Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath,
                                           const std::vector<UInt32>& childIndices,
                                           const std::vector<boost::any>& children)
{
    TreeModelEventPtr TheEvent = TreeModelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->editMFChildIndices()->setValues(childIndices);
    TheEvent->_Path     = ThePath;
    TheEvent->_Children = children;

    return TheEvent;
}

TreeModelEventPtr TreeModelEvent::create(  FieldContainerPtr Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath)
{
    TreeModelEventPtr TheEvent = TreeModelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->_Path     = ThePath;

    return TheEvent;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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

void TreeModelEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TreeModelEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TreeModelEvent NI" << std::endl;
}


OSG_END_NAMESPACE

