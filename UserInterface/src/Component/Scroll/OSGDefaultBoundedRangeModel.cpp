/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include "OSGDefaultBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultChangeModel
A DefaultChangeModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


void DefaultBoundedRangeModel::setExtent(UInt32 newExtent)
{
    _Extent= newExtent;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

void DefaultBoundedRangeModel::setMaximum(Int32 newMaximum)
{
    _Maximum= newMaximum;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

void DefaultBoundedRangeModel::setMinimum(Int32 newMinimum)
{
    _Minimum= newMinimum;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

void DefaultBoundedRangeModel::setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting)
{
    _Extent= extent;
    _Maximum= max;
    _Minimum= min;
    _Value= value;
    _ValueIsAdjusting = adjusting;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

void DefaultBoundedRangeModel::setValue(Int32 newValue)
{
    _Value= newValue;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

void DefaultBoundedRangeModel::setValueIsAdjusting(bool b)
{
    _ValueIsAdjusting = b;
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultBoundedRangeModel::produceStateChanged(const ChangeEvent& e)
{
   for(ChangeListenerSetConstItor SetItor(_ChangeListeners.begin()) ; SetItor != _ChangeListeners.end() ; ++SetItor)
   {
	   (*SetItor)->stateChanged(e);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultBoundedRangeModel::DefaultBoundedRangeModel(void) :
_Extent(0),
_Maximum(0),
_Minimum(0),
_Value(0),
_ValueIsAdjusting(false)
{
}

DefaultBoundedRangeModel::~DefaultBoundedRangeModel(void)
{
}

OSG_END_NAMESPACE

