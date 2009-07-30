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

#include "OSGDefaultListComponentGenerator.h"
#include "Component/OSGComponent.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListComponentGenerator
A UI Default List ComponentGenerator. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultListComponentGenerator::getListComponent(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return NullFC;
	}

	return getListComponentFromString(Parent, getText(Parent, Value, Index, IsSelected, HasFocus), Index, IsSelected, HasFocus);
}

ComponentPtr DefaultListComponentGenerator::getListComponentFromString(ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	ComponentPtr TheComponent = Component::Ptr::dcast(getDrawObjectPrototype()->shallowCopy());

	if(TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	{
		beginEditCP(TheComponent, TextComponent::TextFieldMask);
			TextComponent::Ptr::dcast(TheComponent)->setText(Value);
		endEditCP(TheComponent, TextComponent::TextFieldMask);

        applyTextColor(TextComponent::Ptr::dcast(TheComponent), Parent, Value, Index, IsSelected, HasFocus);
	}

    applyBordersAndBackground(TheComponent, Parent, Value, Index, IsSelected, HasFocus);

	return TheComponent;
}

std::string DefaultListComponentGenerator::getText(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
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
	
void DefaultListComponentGenerator::applyBordersAndBackground(ComponentPtr TheComponent, ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
	if(IsSelected && HasFocus)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
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
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
	}
	else if(IsSelected)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
	}
	else if(HasFocus)
	{
		beginEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
		endEditCP(TheComponent, Component::BordersFieldMask | Component::BackgroundsFieldMask);
	}
}

void DefaultListComponentGenerator::applyTextColor(TextComponentPtr TheComponent, ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
    if(IsSelected && HasFocus)
    {
	    beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
	    if(getFocusedTextColorHasPriority())
	    {
		    TheComponent->setTextColors(getFocusedTextColor());
	    }
	    else
	    {
		    TheComponent->setTextColors(getSelectedTextColor());
	    }
	    endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
    }
    else if(IsSelected)
    {
	    beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
		    TheComponent->setTextColors(getSelectedTextColor());
	    endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
    }
    else if(HasFocus)
    {
	    beginEditCP(TheComponent, TextComponent::TextColorsFieldMask);
		    TheComponent->setTextColors(getFocusedTextColor());
	    endEditCP(TheComponent, TextComponent::TextColorsFieldMask);
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

void DefaultListComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultListComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultListComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTLISTCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTLISTCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTLISTCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

