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

#include "OSGDefaultComboBoxComponentGenerator.h"
#include "OSGComponent.h"
#include "OSGTextComponent.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultComboBoxComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultComboBoxComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultComboBoxComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr DefaultComboBoxComponentGenerator::getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

	ComponentRefPtr TheComponent = dynamic_pointer_cast<Component>(getDrawObjectPrototype()->shallowCopy());

	if(TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	{
		std::string ValueString;

        try
        {
            ValueString = lexical_cast(Value);
        }
        catch (boost::bad_lexical_cast &)
        {
            //Could not convert to string
        }

			dynamic_pointer_cast<TextComponent>(TheComponent)->setText(ValueString);

		if(IsSelected && HasFocus)
		{
			if(getFocusedTextColorHasPriority())
			{
				dynamic_pointer_cast<TextComponent>(TheComponent)->setTextColors(getFocusedTextColor());
			}
			else
			{
				dynamic_pointer_cast<TextComponent>(TheComponent)->setTextColors(getSelectedTextColor());
			}
		}
		else if(IsSelected)
		{
				dynamic_pointer_cast<TextComponent>(TheComponent)->setTextColors(getSelectedTextColor());
		}
		else if(HasFocus)
		{
				dynamic_pointer_cast<TextComponent>(TheComponent)->setTextColors(getFocusedTextColor());
		}
	}
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
			    TheComponent->setForegrounds(getFocusedForeground());
			}
			else
			{
				TheComponent->setBackgrounds(getSelectedBackground());
			    TheComponent->setForegrounds(getSelectedForeground());
			}
	}
	else if(IsSelected)
	{
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
			TheComponent->setForegrounds(getSelectedForeground());
	}
	else if(HasFocus)
	{
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
			TheComponent->setForegrounds(getFocusedForeground());
	}
	return ComponentTransitPtr(TheComponent.get());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultComboBoxComponentGenerator::DefaultComboBoxComponentGenerator(void) :
    Inherited()
{
}

DefaultComboBoxComponentGenerator::DefaultComboBoxComponentGenerator(const DefaultComboBoxComponentGenerator &source) :
    Inherited(source)
{
}

DefaultComboBoxComponentGenerator::~DefaultComboBoxComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultComboBoxComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultComboBoxComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultComboBoxComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
