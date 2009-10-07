/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *					Authors: David Kabala, Eric Langkamp					 *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGMiniMapTransformation.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MiniMapTransformation
A MiniMapTransformation. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MiniMapTransformation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MiniMapTransformation::removeChangeListener(ChangeListenerPtr Listener)
{
   ChangeListenerSetItor EraseIter(_ChangeListeners.find(Listener));
   if(EraseIter != _ChangeListeners.end())
   {
      _ChangeListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void MiniMapTransformation::produceStateChanged(const ChangeEventPtr e)
{
    ChangeListenerSet ListenerSet(_ChangeListeners);
    for(ChangeListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
	    (*SetItor)->stateChanged(e);
    }
    produceEvent(StateChangedMethodId,e);
}

/*----------------------- constructors & destructors ----------------------*/

MiniMapTransformation::MiniMapTransformation(void) :
    Inherited()
{
}

MiniMapTransformation::MiniMapTransformation(const MiniMapTransformation &source) :
    Inherited(source)
{
}

MiniMapTransformation::~MiniMapTransformation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MiniMapTransformation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MiniMapTransformation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MiniMapTransformation NI" << std::endl;
}

OSG_END_NAMESPACE

