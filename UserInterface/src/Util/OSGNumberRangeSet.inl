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
bool NumberRange::operator!= (const NumberRange& right) const
{
	return !this->operator==(right);
}

inline
Int32 NumberRange::getMin(void) const
{
    return _Min;
}

inline
Int32 NumberRange::getMax(void) const
{
    return _Max;
}

inline
bool NumberRange::isEmpty(void) const
{
    return _IsEmpty;
}

inline
void NumberRange::setEmpty(void)
{
    _IsEmpty = true;
}

inline
void NumberSet::clear(void)
{
    return _List.clear();
}

inline
NumberSet::RangeListTypeConstItor NumberSet::begin(void) const
{
    return _List.begin();
}

inline
NumberSet::RangeListTypeConstItor NumberSet::end(void) const
{
    return _List.end();
}

inline
NumberRange NumberSet::front(void) const
{
    return _List.front();
}

inline
NumberRange NumberSet::back(void) const
{
    return _List.back();
}
OSG_END_NAMESPACE

#define OSGCOMPONENT_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

