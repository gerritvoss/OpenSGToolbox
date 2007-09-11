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
void LabelMenuItem::addActionListener(ActionListenerPtr Listener)
{
   _ActionListeners.insert(Listener);
}

inline
void LabelMenuItem::removeActionListener(ActionListenerPtr Listener)
{
   ActionListenerSetItor EraseIter(_ActionListeners.find(Listener));
   if(EraseIter != _ActionListeners.end())
   {
      _ActionListeners.erase(EraseIter);
   }
}

inline
LabelMenuItem::LabelMenuItemKeyAcceleratorListener::LabelMenuItemKeyAcceleratorListener(LabelMenuItemPtr TheLabelMenuItem) :
									_LabelMenuItem(TheLabelMenuItem)
{
}

inline
LabelMenuItem::KeyAcceleratorMenuFlashUpdateListener::KeyAcceleratorMenuFlashUpdateListener(LabelMenuItemPtr TheLabelMenuItem) :
									_LabelMenuItem(TheLabelMenuItem),
									_FlashElps(0.0)
{
}

inline
void LabelMenuItem::KeyAcceleratorMenuFlashUpdateListener::reset(void)
{
    _FlashElps = 0.0;
}


inline
void LabelMenuItem::setDrawAsThoughSelected(bool Selected)
{
    _DrawAsThoughSelected = Selected;
}

inline
bool LabelMenuItem::getDrawAsThoughSelected(void) const
{
    return _DrawAsThoughSelected;
}
OSG_END_NAMESPACE

#define OSGLABELMENUITEM_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

