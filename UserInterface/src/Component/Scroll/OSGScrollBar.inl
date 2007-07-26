/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void ScrollBar::setModel(BoundedRangeModel* Model)
{
    _Model = Model;
}

inline
BoundedRangeModel* ScrollBar::getModel(void) const
{
    return _Model;
}

inline
bool ScrollBar::getValueIsAdjusting(void) const
{
    return _Model->getValueIsAdjusting();
}

inline
void ScrollBar::setValueIsAdjusting(bool Value)
{
    _Model->setValueIsAdjusting(Value);
}

inline
UInt32 ScrollBar::getExtent(void) const
{
    return _Model->getExtent();
}

inline
UInt32 ScrollBar::getMaximum(void) const
{
    return _Model->getMaximum();
}

inline
UInt32 ScrollBar::getMinimum(void) const
{
    return _Model->getMinimum();
}

inline
UInt32 ScrollBar::getValue(void) const
{
    return _Model->getValue();
}

inline
void ScrollBar::setExtent(UInt32 newExtent)
{
    _Model->setExtent(newExtent);
}

inline
void ScrollBar::setMaximum(UInt32 newMaximum)
{
    _Model->setMaximum(newMaximum);
}

inline
void ScrollBar::setMinimum(UInt32 newMinimum)
{
    _Model->setMinimum(newMinimum);
}

inline
void ScrollBar::setRangeProperties(UInt32 value, UInt32 extent, UInt32 min, UInt32 max, bool adjusting)
{
    _Model->setRangeProperties(value, extent, min, max, adjusting);
}

inline
void ScrollBar::setValue(UInt32 newValue)
{
    _Model->setValue(newValue);
}

inline
void ScrollBar::addAdjustmentListener(AdjustmentListenerPtr Listener)
{
   _AdjustmentListeners.insert(Listener);
}

inline
void ScrollBar::removeAdjustmentListener(AdjustmentListenerPtr Listener)
{
   AdjustmentListenerSetItor EraseIter(_AdjustmentListeners.find(Listener));
   if(EraseIter != _AdjustmentListeners.end())
   {
      _AdjustmentListeners.erase(EraseIter);
   }
}

OSG_END_NAMESPACE

#define OSGSCROLLBAR_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

