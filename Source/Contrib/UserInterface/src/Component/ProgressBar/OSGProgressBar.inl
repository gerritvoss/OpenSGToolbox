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
Int32 ProgressBar::getMaximum(void) const
{
	return getRangeModel()->getMaximum();
}

inline
Int32 ProgressBar::getMinimum(void) const
{
	return getRangeModel()->getMinimum();
}

inline
Real32 ProgressBar::getPercentComplete(void) const
{
	return (static_cast<Real32>(getValue()) - static_cast<Real32>(getMinimum()))/(static_cast<Real32>(getMaximum()) - static_cast<Real32>(getMinimum()));
}

inline
Int32 ProgressBar::getValue(void) const
{
	return getRangeModel()->getValue();
}

inline
void ProgressBar::setMaximum(const Int32& n)
{
	getRangeModel()->setMaximum(n);
}

inline
void ProgressBar::setMinimum(const Int32& n)
{
	getRangeModel()->setMinimum(n);
}

inline
void ProgressBar::setValue(const Int32& n)
{
	getRangeModel()->setValue(n);
}

OSG_END_NAMESPACE
