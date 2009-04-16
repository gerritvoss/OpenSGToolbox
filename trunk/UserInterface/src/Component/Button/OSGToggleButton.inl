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
bool ToggleButton::isButtonSelectedListenerAttached(ButtonSelectedListenerPtr Listener) const
{
    return _ButtonSelectedListeners.find(Listener) != _ButtonSelectedListeners.end();
}

inline
void ToggleButton::setSelectedBorder   ( const BorderPtr &value )
{
    setActiveBorder(value);
}

inline
void ToggleButton::setSelectedBackground( const LayerPtr &value )
{
    setActiveBackground(value);
}

inline
void ToggleButton::setSelectedTextColor( const Color4f &value )
{
    setActiveTextColor(value);
}

inline
void ToggleButton::setSelectedDrawObject( const UIDrawObjectCanvasPtr &value )
{
    setActiveDrawObject(value);
}

inline
void ToggleButton::setSelectedImage(ImagePtr TheImage, Vec2f Size)
{
    setActiveImage(TheImage, Size);
}

inline
void ToggleButton::setSelectedTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    setActiveTexture(TheTexture, Size);
}

inline
void ToggleButton::setSelectedImage(const std::string& Path, Vec2f Size)
{
    setActiveImage(Path, Size);
}

inline
BorderPtr &ToggleButton::getSelectedBorder(void)
{
    return getActiveBorder();
}

inline
const BorderPtr &ToggleButton::getSelectedBorder(void) const
{
    return getActiveBorder();
}

inline
LayerPtr &ToggleButton::getSelectedBackground(void)
{
    return getActiveBackground();
}

inline
const LayerPtr &ToggleButton::getSelectedBackground(void) const
{
    return getActiveBackground();
}

inline
Color4f &ToggleButton::getSelectedTextColor(void)
{
    return getActiveTextColor();
}

inline
const Color4f &ToggleButton::getSelectedTextColor(void) const
{
    return getActiveTextColor();
}

inline
UIDrawObjectCanvasPtr &ToggleButton::getSelectedDrawObject(void)
{
    return getActiveDrawObject();
}

inline
const UIDrawObjectCanvasPtr &ToggleButton::getSelectedDrawObject(void) const
{
    return getActiveDrawObject();
}

inline
void ToggleButton::removeButtonSelectedListener(ButtonSelectedListenerPtr Listener)
{
   ButtonSelectedListenerSetItor EraseIter(_ButtonSelectedListeners.find(Listener));
   if(EraseIter != _ButtonSelectedListeners.end())
   {
      _ButtonSelectedListeners.erase(EraseIter);
   }
}
OSG_END_NAMESPACE

#define OSGTOGGLEBUTTON_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

