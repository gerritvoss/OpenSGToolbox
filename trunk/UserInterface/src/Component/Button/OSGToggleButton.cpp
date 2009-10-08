/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGToggleButton.h"
#include "Util/OSGUIDrawUtils.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ToggleButton
A UI Button. 
*/

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

void ToggleButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection ToggleButton::addButtonSelectedListener(ButtonSelectedListenerPtr Listener)
{
   _ButtonSelectedListeners.insert(Listener);
   return EventConnection(
       boost::bind(&ToggleButton::isButtonSelectedListenerAttached, this, Listener),
       boost::bind(&ToggleButton::removeButtonSelectedListener, this, Listener));
}

void ToggleButton::actionPreformed(const ActionEventPtr e)
{
    beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
	    setSelected(!getSelected());
    endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
}

BorderPtr ToggleButton::getDrawnBorder(void) const
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

LayerPtr ToggleButton::getDrawnBackground(void) const
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
LayerPtr ToggleButton::getDrawnForeground(void) const
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
void  ToggleButton::produceButtonSelected(const ButtonSelectedEventPtr e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonSelected(e);
   }
   _Producer.produceEvent(ButtonSelectedMethodId,e);
}

void  ToggleButton::produceButtonDeselected(const ButtonSelectedEventPtr e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonDeselected(e);
   }
   _Producer.produceEvent(ButtonDeselectedMethodId,e);
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

void ToggleButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if( (whichField & SelectedFieldMask) )
    {
        if(getSelected())
        {
			produceButtonSelected( ButtonSelectedEvent::create(ComponentPtr(this),getSystemTime()) );    
        }
        else
        {
            produceButtonDeselected( ButtonSelectedEvent::create(ComponentPtr(this),getSystemTime()) );    
        }
     }
}

void ToggleButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ToggleButton NI" << std::endl;
}

OSG_END_NAMESPACE

