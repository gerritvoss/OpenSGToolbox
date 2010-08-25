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
Real32 GLViewport::getYaw(void) const
{
    return _Yaw;
}

inline
Real32 GLViewport::getRoll(void) const
{
    return _Roll;
}

inline
Real32 GLViewport::getPitch(void) const
{
    return _Pitch;
}

inline
const Vec3f& GLViewport::getOffset(void) const
{
    return _Offset;
}

inline
const Vec3f& GLViewport::getOffsetMultipliers(void) const
{
    return _OffsetMultipliers;
}

inline
const Vec3f& GLViewport::getMinOffset(void) const
{
    return _MinOffset;
}

inline
const Vec3f& GLViewport::getMaxOffset(void) const
{
    return _MaxOffset;
}
 
inline
void GLViewport::setOffsetMultipliers(const Vec3f& OffsetMultipliers)
{
    _OffsetMultipliers= OffsetMultipliers;
}

inline
void GLViewport::setMinOffset(const Vec3f& MinOffset)
{
    _MinOffset = MinOffset;
}

inline
void GLViewport::setMaxOffset(const Vec3f& MaxOffset)
{
    _MaxOffset = MaxOffset;
}

inline
void GLViewport::setMode(Navigator::Mode TheMode)
{
    _Navigator.setMode(TheMode);
}

OSG_END_NAMESPACE
