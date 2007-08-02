/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void Scrollbar::setModel(BoundedRangeModel* Model)
{
    _Model = Model;
}

inline
BoundedRangeModel* Scrollbar::getModel(void) const
{
    return _Model;
}

inline
bool Scrollbar::getValueIsAdjusting(void) const
{
    return _Model->getValueIsAdjusting();
}

inline
void Scrollbar::setValueIsAdjusting(bool Value)
{
    _Model->setValueIsAdjusting(Value);
}

inline
UInt32 Scrollbar::getExtent(void) const
{
    return _Model->getExtent();
}

inline
UInt32 Scrollbar::getMaximum(void) const
{
    return _Model->getMaximum();
}

inline
UInt32 Scrollbar::getMinimum(void) const
{
    return _Model->getMinimum();
}

inline
UInt32 Scrollbar::getValue(void) const
{
    return _Model->getValue();
}

inline
void Scrollbar::setExtent(UInt32 newExtent)
{
    _Model->setExtent(newExtent);
}

inline
void Scrollbar::setMaximum(UInt32 newMaximum)
{
    _Model->setMaximum(newMaximum);
}

inline
void Scrollbar::setMinimum(UInt32 newMinimum)
{
    _Model->setMinimum(newMinimum);
}

inline
void Scrollbar::setRangeProperties(UInt32 value, UInt32 extent, UInt32 min, UInt32 max, bool adjusting)
{
    _Model->setRangeProperties(value, extent, min, max, adjusting);
}

inline
void Scrollbar::setValue(UInt32 newValue)
{
    _Model->setValue(newValue);
}

inline
void Scrollbar::addAdjustmentListener(AdjustmentListenerPtr Listener)
{
   _AdjustmentListeners.insert(Listener);
}

inline
void Scrollbar::removeAdjustmentListener(AdjustmentListenerPtr Listener)
{
   AdjustmentListenerSetItor EraseIter(_AdjustmentListeners.find(Listener));
   if(EraseIter != _AdjustmentListeners.end())
   {
      _AdjustmentListeners.erase(EraseIter);
   }
}

OSG_END_NAMESPACE

#define OSGSCROLLBAR_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

