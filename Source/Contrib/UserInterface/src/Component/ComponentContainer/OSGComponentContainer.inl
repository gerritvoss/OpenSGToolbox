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
Real32 &ComponentContainer::getLeftInset (void)
{
	return editInset()[0];
}

inline
const Real32 &ComponentContainer::getLeftInset (void) const
{
	return getInset()[0];
}

inline
Real32 &ComponentContainer::getRightInset (void)
{
	return editInset()[1];
}

inline
const Real32 &ComponentContainer::getRightInset (void) const
{
	return getInset()[1];
}

inline
Real32 &ComponentContainer::getTopInset (void)
{
	return editInset()[2];
}

inline
const Real32 &ComponentContainer::getTopInset (void) const
{
	return getInset()[2];
}

inline
Real32 &ComponentContainer::getBottomInset (void)
{
	return editInset()[3];
}

inline
const Real32 &ComponentContainer::getBottomInset (void) const
{
	return getInset()[3];
}

OSG_END_NAMESPACE
