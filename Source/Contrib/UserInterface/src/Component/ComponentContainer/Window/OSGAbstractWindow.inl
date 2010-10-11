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
void AbstractWindow::vetoWindowClose(void)
{
	_VetoWindowClose = true;
}

inline
bool AbstractWindow::isAlignableInDrawingSurface(void) const
{
	return getAlignmentInDrawingSurface().x() >= 0.0f &&
		getAlignmentInDrawingSurface().x() <= 1.0f &&
		getAlignmentInDrawingSurface().y() >= 0.0f &&
		getAlignmentInDrawingSurface().y() <= 1.0f;
}

inline
bool AbstractWindow::isScalableInDrawingSurface(void) const
{
	return getScalingInDrawingSurface().x() >= 0.0f &&
		getScalingInDrawingSurface().x() <= 1.0f &&
		getScalingInDrawingSurface().y() >= 0.0f &&
		getScalingInDrawingSurface().y() <= 1.0f;
}
    
inline
bool AbstractWindow::operator<(const AbstractWindow& right) const
{
    return (!getModal() && right.getModal()) ||
           (!getAllwaysOnTop() && right.getAllwaysOnTop());
}

inline
bool AbstractWindow::isOpen(void) const
{
    return getParentDrawingSurface() != NULL;
}

OSG_END_NAMESPACE
