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

#include "OSGRadioButtonGroup.h"
#include "OSGRadioButton.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRadioButtonGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGRadioButtonGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RadioButtonGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RadioButtonGroup::addButton(RadioButton* const Button)
{
    pushToGroupButtons(Button);
    if(Button->getSelected())
    {
        RadioButtonRefPtr SelectedButton(getSelectedButton());
        if(SelectedButton == NULL)
        {
            setSelectedButton(SelectedButton);
        }
        else
        {
            Button->setSelected(false);
        }
    }
}

void RadioButtonGroup::removeButton(RadioButton* const Button)
{
    MFUnrecRadioButtonPtr *curButtons = editMFGroupButtons();
    MFUnrecRadioButtonPtr::iterator ButtonIter = (*curButtons).find(Button);
    if(ButtonIter != (*curButtons).end())
    {
        (*curButtons).erase(ButtonIter);		
    }
}

void RadioButtonGroup::removeButton(UInt32 Index)
{
    MFUnrecRadioButtonPtr *curButtons = editMFGroupButtons();
    MFUnrecRadioButtonPtr::iterator ButtonIter = (*curButtons).begin();
    for(Int32 i = 0; i < Index && ButtonIter != (*curButtons).end(); i++)
    {
        ++ButtonIter;
    }
    if(ButtonIter != (*curButtons).end())
    {
        (*curButtons).erase(ButtonIter);
    }
}
UInt32 RadioButtonGroup::getButtonCount(void) const
{
    return getMFGroupButtons()->size();
}


bool RadioButtonGroup::isSelected(const RadioButton* const Button) const
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

void RadioButtonGroup::handleButtonSelected(ButtonSelectedEventDetails* const e)
{
    RadioButtonRefPtr TheButton = dynamic_cast<RadioButton*>(e->getSource());
    RadioButtonRefPtr PreviousSelected(getSelectedButton());
    if(PreviousSelected != TheButton)
    {
        setSelectedButton(TheButton);
        if(PreviousSelected != NULL)
        {
            PreviousSelected->setSelected(false);
        }
    }
}

void RadioButtonGroup::handleButtonDeselected(ButtonSelectedEventDetails* const e)
{
    if(getSelectedButton() == e->getSource())
    {
        setSelectedButton(NULL);
    }
}

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

void RadioButtonGroup::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & GroupButtonsFieldMask)
    {
        for(UInt32 i(0) ; i<_ButtonConnections.size() ; ++i)
        {
            _ButtonConnections[i].disconnect();
        }
        _ButtonConnections.clear();
        for(UInt32 i(0) ; i<getMFGroupButtons()->size() ; ++i)
        {
            _ButtonConnections.push_back(getGroupButtons(i)->connectButtonSelected(boost::bind(&RadioButtonGroup::handleButtonSelected, this, _1)));
            _ButtonConnections.push_back(getGroupButtons(i)->connectButtonDeselected(boost::bind(&RadioButtonGroup::handleButtonDeselected, this, _1)));
        }
    }

	if(whichField & SelectedButtonFieldMask)
    {
		RadioButtonRefPtr SelectedButton(getSelectedButton());
		RadioButtonRefPtr tmpButton;
		for(UInt32 i(0) ; i<getMFGroupButtons()->size() ; ++i)
        {
			tmpButton = getGroupButtons(i);
				if(tmpButton == SelectedButton)
					tmpButton->setSelected(true);
				else
					tmpButton->setSelected(false);
			
        }
    }

}

void RadioButtonGroup::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump RadioButtonGroup NI" << std::endl;
}

OSG_END_NAMESPACE
