/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
bool ToggleButton::isButtonSelectedListenerAttached(ButtonSelectedListenerPtr Listener) const
{
    return _ButtonSelectedListeners.find(Listener) != _ButtonSelectedListeners.end();
}

    inline
void ToggleButton::setSelectedBorder   ( const BorderRefPtr &value )
{
    setActiveBorder(value);
}

    inline
void ToggleButton::setSelectedBackground( const LayerRefPtr &value )
{
    setActiveBackground(value);
}

    inline
void ToggleButton::setSelectedTextColor( const Color4f &value )
{
    setActiveTextColor(value);
}

    inline
void ToggleButton::setSelectedDrawObject( const UIDrawObjectCanvasRefPtr &value )
{
    setActiveDrawObject(value);
}

    inline
void ToggleButton::setSelectedImage(ImageRefPtr TheImage, Vec2f Size)
{
    setActiveImage(TheImage, Size);
}

    inline
void ToggleButton::setSelectedTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size)
{
    setActiveTexture(TheTexture, Size);
}

    inline
void ToggleButton::setSelectedImage(const std::string& Path, Vec2f Size)
{
    setActiveImage(Path, Size);
}

inline
Border * ToggleButton::getSelectedBorder   (void) const
{
    return getActiveBorder();
}

inline
Layer * ToggleButton::getSelectedBackground(void) const
{
    return getActiveBackground();
}

inline
Layer * ToggleButton::getSelectedForeground(void) const
{
    return getActiveForeground();
}

inline
UIDrawObjectCanvas * ToggleButton::getSelectedDrawObject(void) const
{
    return getActiveDrawObject();
}

inline
Color4f &ToggleButton::editSelectedTextColor(void)
{
    return editActiveTextColor();
}

inline
const Color4f &ToggleButton::getSelectedTextColor(void) const
{
    return getActiveTextColor();
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
