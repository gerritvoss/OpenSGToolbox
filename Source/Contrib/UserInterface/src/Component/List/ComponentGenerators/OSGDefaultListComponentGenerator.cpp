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

#include "OSGDefaultListComponentGenerator.h"
#include "OSGComponent.h"
#include "OSGLabel.h"
#include "OSGStringUtils.h"
#include "OSGList.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultListComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultListComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr DefaultListComponentGenerator::getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

    std::string Text(getText(Parent, Value, Index, IsSelected, HasFocus));
	return getListComponentFromString(Parent, Text, Index, IsSelected, HasFocus);
}

ComponentTransitPtr DefaultListComponentGenerator::getListComponentFromString(List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	ComponentRefPtr TheComponent;

	if(getDrawObjectPrototype() != NULL)
	{
		TheComponent = dynamic_pointer_cast<Component>(getDrawObjectPrototype()->shallowCopy());
	}
	else
	{
		TheComponent = Label::create();
	}

	if(TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	{
			dynamic_pointer_cast<TextComponent>(TheComponent)->setText(Value);

        applyTextColor(dynamic_pointer_cast<TextComponent>(TheComponent), Parent, Value, Index, IsSelected, HasFocus);
	}

    applyBordersAndBackground(TheComponent, Parent, Value, Index, IsSelected, HasFocus);

	return ComponentTransitPtr(TheComponent.get());
}

std::string DefaultListComponentGenerator::getText(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
	if(Value.empty()){
		return std::string("");
	}

	std::string ValueString;
    try
    {
        ValueString = lexical_cast(Value);
    }
    catch (boost::bad_lexical_cast &)
    {
        //Could not convert to string
    }
    return ValueString;
}
	
void DefaultListComponentGenerator::applyBordersAndBackground(Component* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
	if(IsSelected && HasFocus)
	{
			if(getFocusedBorderHasPriority())
			{
				TheComponent->setBorders(getFocusedBorder());
			}
			else
			{
				TheComponent->setBorders(getSelectedBorder());
			}
			if(getFocusedBackgroundHasPriority())
			{
				TheComponent->setBackgrounds(getFocusedBackground());
			}
			else
			{
				TheComponent->setBackgrounds(getSelectedBackground());
			}
	}
	else if(IsSelected)
	{
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
	}
	else if(HasFocus)
	{
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
	}
}

void DefaultListComponentGenerator::applyTextColor(TextComponent* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
    if(IsSelected && HasFocus)
    {
	    if(getFocusedTextColorHasPriority())
	    {
		    TheComponent->setTextColors(getFocusedTextColor());
	    }
	    else
	    {
		    TheComponent->setTextColors(getSelectedTextColor());
	    }
    }
    else if(IsSelected)
    {
		    TheComponent->setTextColors(getSelectedTextColor());
    }
    else if(HasFocus)
    {
		    TheComponent->setTextColors(getFocusedTextColor());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListComponentGenerator::DefaultListComponentGenerator(void) :
    Inherited()
{
}

DefaultListComponentGenerator::DefaultListComponentGenerator(const DefaultListComponentGenerator &source) :
    Inherited(source)
{
}

DefaultListComponentGenerator::~DefaultListComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultListComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultListComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultListComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
