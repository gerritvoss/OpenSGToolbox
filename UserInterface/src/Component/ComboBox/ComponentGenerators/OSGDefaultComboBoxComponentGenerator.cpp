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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultComboBoxComponentGenerator.h"
#include "Component/OSGComponent.h"
#include "Component/Text/OSGTextComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultComboBoxComponentGenerator
A UI Default ComboBox ComponentGenerator. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultComboBoxComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultComboBoxComponentGenerator::getComboBoxComponent(ComboBoxPtr Parent, SharedFieldPtr Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value == NULL){
		return NullFC;
	}

	ComponentPtr TheComponent = Component::Ptr::dcast(getDrawObjectPrototype()->shallowCopy());

	if(TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	{
		std::string ValueString;
		if(Value->getType() == SFString::getClassType())
		{
            ValueString = static_cast<SFString*>(Value.get())->getValue();
		}
		else
		{
			Value->getValueByStr(ValueString);
		}
		beginEditCP(TheComponent, TextComponent::TextFieldMask);
			TextComponent::Ptr::dcast(TheComponent)->setText(ValueString);
		endEditCP(TheComponent, TextComponent::TextFieldMask);

		if(IsSelected && HasFocus)
		{
			beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
			if(getFocusedTextColorHasPriority())
			{
				TextComponent::Ptr::dcast(TheComponent)->setTextColors(getFocusedTextColor());
			}
			else
			{
				TextComponent::Ptr::dcast(TheComponent)->setTextColors(getSelectedTextColor());
			}
			endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
		}
		else if(IsSelected)
		{
			beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
				TextComponent::Ptr::dcast(TheComponent)->setTextColors(getSelectedTextColor());
			endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
		}
		else if(HasFocus)
		{
			beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
				TextComponent::Ptr::dcast(TheComponent)->setTextColors(getFocusedTextColor());
			endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
		}
	}
	if(IsSelected && HasFocus)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
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
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
	}
	else if(IsSelected)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
			TheComponent->setForegrounds(getSelectedForeground());
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
	}
	else if(HasFocus)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
			TheComponent->setForegrounds(getFocusedForeground());
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask | Component::ForegroundsFieldMask);
	}
	return TheComponent;
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

void DefaultComboBoxComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultComboBoxComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultComboBoxComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTCOMBOBOXCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTCOMBOBOXCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTCOMBOBOXCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

