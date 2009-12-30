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
bool Slider::isChangeListenerAttached(ChangeListenerPtr l) const
{
    return getRangeModel()->isChangeListenerAttached(l);
}

inline
FieldContainerMap Slider::createStandardLabels(UInt32 increment)
{
	return createStandardLabels(increment, getMinimum());
}

inline
void Slider::removeChangeListener(ChangeListenerPtr l)
{
	getRangeModel()->removeChangeListener(l);
}

inline
UInt32 Slider::getExtent(void) const
{
	return getRangeModel()->getExtent();
}

inline
Int32 Slider::getMaximum(void) const
{
	return getRangeModel()->getMaximum();
}

inline
Int32 Slider::getMinimum(void) const
{
	return getRangeModel()->getMinimum();
}

inline
Int32 Slider::getValue(void) const
{
	return getRangeModel()->getValue();
}

inline
bool Slider::getValueIsAdjusting(void) const
{
	return getRangeModel()->getValueIsAdjusting();
}

inline
void Slider::setExtent(UInt32 extent)
{
	getRangeModel()->setExtent(extent);
}

inline
void Slider::setMaximum(Int32 maximum)
{
	getRangeModel()->setMaximum(maximum);
}

inline
void Slider::setMinimum(Int32 minimum)
{
	getRangeModel()->setMinimum(minimum);
}

inline
void Slider::setValueIsAdjusting(bool b)
{
	getRangeModel()->setValueIsAdjusting(b);
}

inline
Slider::BoundedRangeModelChangeListener::BoundedRangeModelChangeListener(SliderPtr TheSlider) :
   _Slider(TheSlider)
{
}

inline
Slider::KnobDraggedListener::KnobDraggedListener(SliderPtr TheSlider) :
   _Slider(TheSlider)
{
}

OSG_END_NAMESPACE

#define OSGSLIDER_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

