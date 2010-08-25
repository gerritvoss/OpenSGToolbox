/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGToggleButton.h"
#include "OSGUIDrawUtils.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGToggleButtonBase.cpp file.
// To modify it, please change the .fcd file (OSGToggleButton.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  ToggleButton::SelectedBorderFieldMask = 
    (TypeTraits<BitVector>::One << ToggleButton::SelectedBorderFieldId);

const OSG::BitVector  ToggleButton::SelectedBackgroundFieldMask = 
    (TypeTraits<BitVector>::One << ToggleButton::SelectedBackgroundFieldId);

const OSG::BitVector  ToggleButton::SelectedTextColorFieldMask = 
    (TypeTraits<BitVector>::One << ToggleButton::SelectedTextColorFieldId);

const OSG::BitVector  ToggleButton::SelectedDrawObjectFieldMask = 
    (TypeTraits<BitVector>::One << ToggleButton::SelectedDrawObjectFieldId);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ToggleButton::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ToggleButton::setSelected(const bool value)
{
	if(value != getSelected())
	{
		if(value)
		{
			ButtonSelectedEventDetailsUnrecPtr
				Details(ButtonSelectedEventDetails::create(this,getSystemTime()));
			produceButtonSelected(Details);    
		}
		else
		{
			ButtonSelectedEventDetailsUnrecPtr
				Details(ButtonSelectedEventDetails::create(this,getSystemTime()));
			produceButtonDeselected(Details);    
		}
		
		Inherited::setSelected(value);
	}

}

void ToggleButton::actionPreformed(ActionEventDetails* const e)
{
    setSelected(!getSelected());
}

Border* ToggleButton::getDrawnBorder(void) const
{
    if(getSelected() && getEnabled())
    {
        return getActiveBorder();
    }
    else
    {
        return Inherited::getDrawnBorder();
    }
}

Vec2f ToggleButton::getDrawnOffset(void) const
{
    if(getActive() || getSelected())
    {
        return getActiveOffset();
    }
    else
    {
        return Vec2f(0.0f,0.0f);
    }
}

Layer* ToggleButton::getDrawnBackground(void) const
{
    if(getSelected() && getEnabled())
    {
        return getActiveBackground();
    }
    else
    {
        return Inherited::getDrawnBackground();
    }
}
Layer* ToggleButton::getDrawnForeground(void) const
{
    if(getSelected() && getEnabled())
    {
        return getActiveForeground();
    }
    else
    {
        return Inherited::getDrawnForeground();
    }
}

Color4f ToggleButton::getDrawnTextColor(void) const
{
    if(getSelected() && getEnabled())
    {
        return getActiveTextColor();
    }
    else
    {
        return Inherited::getDrawnTextColor();
    }
}

void  ToggleButton::produceButtonSelected(ButtonSelectedEventDetails* const Details)
{
    Inherited::produceButtonSelected(Details);
}

void  ToggleButton::produceButtonDeselected(ButtonSelectedEventDetails* const Details)
{
    Inherited::produceButtonDeselected(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ToggleButton::ToggleButton(void) :
    Inherited()
{
}

ToggleButton::ToggleButton(const ToggleButton &source) :
    Inherited(source)
{
}

ToggleButton::~ToggleButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ToggleButton::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

}

void ToggleButton::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ToggleButton NI" << std::endl;
}

OSG_END_NAMESPACE
