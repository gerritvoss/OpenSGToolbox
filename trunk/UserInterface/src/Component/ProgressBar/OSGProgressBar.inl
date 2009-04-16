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
EventConnection ProgressBar::addChangeListener(ChangeListenerPtr Listener)
{
	return _Model->addChangeListener(Listener);
}

inline
bool ProgressBar::isChangeListenerAttached(ChangeListenerPtr Listener) const
{
	return _Model->isChangeListenerAttached(Listener);
}

inline
Int32 ProgressBar::getMaximum(void) const
{
	return _Model->getMaximum();
}

inline
Int32 ProgressBar::getMinimum(void) const
{
	return _Model->getMinimum();
}

inline
BoundedRangeModel* ProgressBar::getModel(void) const
{
	return _Model;
}

inline
Real32 ProgressBar::getPercentComplete(void) const
{
	return (static_cast<Real32>(getValue()) - static_cast<Real32>(getMinimum()))/(static_cast<Real32>(getMaximum()) - static_cast<Real32>(getMinimum()));
}

inline
Int32 ProgressBar::getValue(void) const
{
	return _Model->getValue();
}

inline
void ProgressBar::setMaximum(const Int32& n)
{
	_Model->setMaximum(n);
}

inline
void ProgressBar::setMinimum(const Int32& n)
{
	_Model->setMinimum(n);
}

inline
void ProgressBar::setModel(BoundedRangeModel* newModel)
{
	_Model = newModel;
	_Model->addChangeListener(&_ModelChangeListener);
}

inline
void ProgressBar::setValue(const Int32& n)
{
	_Model->setValue(n);
}

inline
void ProgressBar::removeChangeListener(ChangeListenerPtr Listener)
{
	_Model->removeChangeListener(Listener);
}

inline
ProgressBar::ModelChangeListener::ModelChangeListener(ProgressBarPtr TheProgressBar) :
   _ProgressBar(TheProgressBar)
{
}
   
inline
ProgressBar::IndeterminateUpdateListener::IndeterminateUpdateListener(ProgressBarPtr TheProgressBar) :
   _ProgressBar(TheProgressBar)
{
}

OSG_END_NAMESPACE

#define OSGPROGRESSBAR_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

