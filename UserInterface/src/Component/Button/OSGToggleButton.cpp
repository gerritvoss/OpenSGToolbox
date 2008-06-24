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

const OSG::BitVector  ToggleButton::SelectedFieldMask = 
    (TypeTraits<BitVector>::One << ToggleButton::SelectedFieldId);

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

BorderPtr ToggleButton::getDrawnBorder(void) const
{
	if(getSelected())
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
	if(getSelected())
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
	if(getSelected())
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
	if(getSelected())
	{
		return getActiveTextColor();
	}
	else
	{
        return Inherited::getDrawnTextColor();
    }
}
void  ToggleButton::produceButtonSelected(const ButtonSelectedEvent& e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonSelected(e);
   }
}

void  ToggleButton::produceButtonDeselected(const ButtonSelectedEvent& e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonDeselected(e);
   }
}
/*----------------------------- class specific ----------------------------*/

void ToggleButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if( (whichField & SelectedFieldMask) )
    {
        if(getSelected())
        {
			produceButtonSelected( ButtonSelectedEvent(ComponentPtr(this),getSystemTime(),ButtonSelectedEvent::BUTTONSELECTED, ButtonPtr(this)) );    
        }
        else
        {
            produceButtonDeselected( ButtonSelectedEvent(ComponentPtr(this),getSystemTime(),ButtonSelectedEvent::BUTTONDESELECTED, ButtonPtr(this)) );    
        }
     }
}

void ToggleButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ToggleButton NI" << std::endl;
}

void ToggleButton::actionPreformed(const ActionEvent& e)
{
    beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
	    setSelected(!getSelected());
    endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGTOGGLEBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOGGLEBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOGGLEBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

