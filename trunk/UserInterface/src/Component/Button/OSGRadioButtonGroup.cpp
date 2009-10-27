/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGRadioButtonGroup.h"
#include "OSGRadioButton.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RadioButtonGroup
A UI Radio Button Group. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RadioButtonGroup::initMethod (void)
{
}

void RadioButtonGroup::addButton(RadioButtonPtr Button)
{
	getGroupButtons().push_back(Button);
    if(Button->getSelected())
    {
		RadioButtonPtr SelectedButton(getSelectedButton());
        if(SelectedButton == NullFC)
        {
            setSelectedButton(SelectedButton);
        }
        else
        {
            beginEditCP(Button, RadioButton::SelectedFieldMask);
                Button->setSelected(false);
            endEditCP(Button, RadioButton::SelectedFieldMask);
        }
    }
	Button->addButtonSelectedListener(this);
}

void RadioButtonGroup::removeButton(RadioButtonPtr Button)
{
	MFRadioButtonPtr *curButtons = editMFGroupButtons();
	std::vector<RadioButtonPtr>::iterator ButtonIter = std::find((*curButtons).begin(),(*curButtons).end(),Button);
	if(ButtonIter != (*curButtons).end())
	{
		(*curButtons).erase(ButtonIter);		
		Button->removeButtonSelectedListener(this);
	}
}

void RadioButtonGroup::removeButton(UInt32 Index)
{
	MFRadioButtonPtr *curButtons = editMFGroupButtons();
	std::vector<RadioButtonPtr>::iterator ButtonIter = (*curButtons).begin();
	for(Int32 i = 0; i < Index && ButtonIter != (*curButtons).end(); i++)
	{
		++ButtonIter;
	}
	if(ButtonIter != (*curButtons).end())
	{
		(*curButtons).erase(ButtonIter);
		(*ButtonIter)->removeButtonSelectedListener(this);
	}
}
UInt32 RadioButtonGroup::getButtonCount(void) const
{
	return getGroupButtons().size();
}


bool RadioButtonGroup::isSelected(const RadioButtonPtr Button) const
{
	if(Button == getSelectedButton())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RadioButtonGroup::buttonSelected(const ButtonSelectedEventPtr e)
{
	RadioButtonPtr TheButton = RadioButton::Ptr::dcast(e->getSource());
    RadioButtonPtr PreviousSelected(getSelectedButton());
	if(PreviousSelected != TheButton)
	{
		setSelectedButton(TheButton);
		if(PreviousSelected != NullFC)
		{
            beginEditCP(PreviousSelected, RadioButton::SelectedFieldMask);
			    PreviousSelected->setSelected(false);
            endEditCP(PreviousSelected, RadioButton::SelectedFieldMask);
		}
	}
}

void RadioButtonGroup::buttonDeselected(const ButtonSelectedEventPtr e)
{
	if(getSelectedButton() == RadioButton::Ptr::dcast(e->getSource()))
	{
		setSelectedButton(NullFC);
	}
}



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RadioButtonGroup::RadioButtonGroup(void) :
    Inherited()
{
}

RadioButtonGroup::RadioButtonGroup(const RadioButtonGroup &source) :
    Inherited(source)
{
}

RadioButtonGroup::~RadioButtonGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RadioButtonGroup::changed(BitVector whichField, UInt32 origin)
{
	if(whichField & GroupButtonsFieldMask)
    {
        for(UInt32 i(0) ; i<getGroupButtons().size() ; ++i)
        {
			getGroupButtons(i)->addButtonSelectedListener(this);
        }
    }

	if(whichField & SelectedButtonFieldMask)
    {
		RadioButtonPtr SelectedButton(getSelectedButton());
		RadioButtonPtr tmpButton;
		for(UInt32 i(0) ; i<getGroupButtons().size() ; ++i)
        {
			tmpButton = getGroupButtons(i);
			beginEditCP(tmpButton, RadioButton::SelectedFieldMask);
				if(tmpButton == SelectedButton)
					tmpButton->setSelected(true);
				else
					tmpButton->setSelected(false);
			endEditCP(tmpButton, RadioButton::SelectedFieldMask);
			
        }
    }

    Inherited::changed(whichField, origin);
}

void RadioButtonGroup::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RadioButtonGroup NI" << std::endl;
}


OSG_END_NAMESPACE

