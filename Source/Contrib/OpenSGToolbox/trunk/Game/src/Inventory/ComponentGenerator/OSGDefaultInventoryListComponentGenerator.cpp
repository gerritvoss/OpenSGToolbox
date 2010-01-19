/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OpenSG/UserInterface/OSGComponent.h"
#include "OpenSG/UserInterface/OSGPanel.h"

#include "OSGDefaultInventoryListComponentGenerator.h"

#include "OpenSG/UserInterface/OSGImageComponent.h"
#include "OpenSG/UserInterface/OSGLabel.h"

#include "Inventory/OSGInventoryItem.h"
#include <boost/any.hpp>
#include "OpenSG/UserInterface/OSGSpringLayout.h"
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>

#include <OpenSG/UserInterface/OSGColorLayer.h>

#include <OpenSG/UserInterface/OSGMatteBorder.h>



OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultInventoryListComponentGenerator
A UI Default Inventory List ComponentGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultInventoryListComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultInventoryListComponentGenerator::getListComponent(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	PanelPtr ListItem = Panel::createEmpty();
	InventoryItemPtr Item;
	ImageComponentPtr Icon = ImageComponent::create();
	LabelPtr ItemName = Label::create();
	MatteBorderPtr GenBorder = MatteBorder::create();

	ColorLayerPtr BackgroundLayer = osg::ColorLayer::create();

	beginEditCP(BackgroundLayer, ColorLayer::ColorFieldMask);
		BackgroundLayer->setColor(Color4f(100,100,100,1));
	endEditCP(BackgroundLayer, ColorLayer::ColorFieldMask);

	if(IsSelected)
	{
		beginEditCP(BackgroundLayer, ColorLayer::ColorFieldMask);
			BackgroundLayer->setColor(Color4f(0,0,100,1));
		endEditCP(BackgroundLayer, ColorLayer::ColorFieldMask);
	}

	if(HasFocus)
	{
		beginEditCP(GenBorder, MatteBorder::ColorFieldMask);
			GenBorder->setColor(Color4f(0,0,100,1));
		endEditCP(GenBorder, MatteBorder::ColorFieldMask);

		beginEditCP(ListItem, Panel::BordersFieldMask);
			ListItem->setBorders(GenBorder);
		endEditCP(ListItem, Panel::BordersFieldMask);
	}

	beginEditCP(ListItem, Panel::BackgroundsFieldMask);
		ListItem->setBackgrounds(BackgroundLayer);
	endEditCP(ListItem, Panel::BackgroundsFieldMask);

	beginEditCP(Icon, ImageComponent::BackgroundsFieldMask);
		Icon->setBackgrounds(BackgroundLayer);
	endEditCP(Icon, ImageComponent::BackgroundsFieldMask);

	beginEditCP(ItemName, Label::BackgroundsFieldMask);
		ItemName->setBackgrounds(BackgroundLayer);
	endEditCP(ItemName, Label::BackgroundsFieldMask);

	try
	{
		Item = boost::any_cast<InventoryItemPtr>(Value);
	}
	catch(boost::bad_any_cast&)
    {
        Item = NullFC;
		return ListItem;
    }



	beginEditCP(Icon , ImageComponent::ScaleFieldMask | ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::DisabledTextureFieldMask | ImageComponent::FocusedTextureFieldMask);
        Icon->setTexture(Item->getIcon());
        Icon->setRolloverTexture(Item->getIcon());
        Icon->setDisabledTexture(Item->getIcon());
        Icon->setFocusedTexture(Item->getIcon());
		Icon->setScale(ImageComponent::SCALE_MIN_AXIS);
    endEditCP(Icon , ImageComponent::ScaleFieldMask | ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::DisabledTextureFieldMask | ImageComponent::FocusedTextureFieldMask);
	

	beginEditCP(ItemName , Label::TextFieldMask);
		ItemName->setText(Item->getName());
	endEditCP(ItemName , Label::TextFieldMask);

	SpringLayoutPtr GenLayout = SpringLayout::create();

	GenLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, Icon, 0, SpringLayoutConstraints::NORTH_EDGE, ListItem);  // The North edge of ExampleButton1 is 25 pixels below the North edge of the MainInternalWindow.
    GenLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, Icon, 0, SpringLayoutConstraints::SOUTH_EDGE, ListItem);  // The South edge of ExampleButton1 is 5 pixels above the Vertical Center of the MainInternalWindow.
    GenLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, Icon, 5, SpringLayoutConstraints::WEST_EDGE, ListItem);  // The East edge of ExampleButton1 is 25 pixels to the left of the East edge of the MainInternalWindow.
	GenLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, Icon, 0, SpringLayoutConstraints::HEIGHT_EDGE, Icon);  // The West edge of ExampleButton1 is 25 pixels to the right of the West edge of the MainInternalWindow.

	GenLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ItemName, 0, SpringLayoutConstraints::NORTH_EDGE, ListItem);  // The North edge of ExampleButton1 is 25 pixels below the North edge of the MainInternalWindow.
    GenLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ItemName, 0, SpringLayoutConstraints::SOUTH_EDGE, ListItem);  // The South edge of ExampleButton1 is 5 pixels above the Vertical Center of the MainInternalWindow.
    GenLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ItemName, -5, SpringLayoutConstraints::EAST_EDGE, ListItem);  // The East edge of ExampleButton1 is 25 pixels to the left of the East edge of the MainInternalWindow.
    GenLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ItemName, 1, SpringLayoutConstraints::EAST_EDGE, Icon);  // The West edge of ExampleButton1 is 25 pixels to the right of the West edge of the MainInternalWindow.


	beginEditCP(ListItem , Panel::ChildrenFieldMask | Panel::ConstraintsFieldMask);
		ListItem->getChildren().push_back(Icon);
		ListItem->getChildren().push_back(ItemName);
		ListItem->setLayout(GenLayout);
	endEditCP(ListItem , Panel::ChildrenFieldMask | Panel::ConstraintsFieldMask);

    return ListItem;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultInventoryListComponentGenerator::DefaultInventoryListComponentGenerator(void) :
    Inherited()
{
}

DefaultInventoryListComponentGenerator::DefaultInventoryListComponentGenerator(const DefaultInventoryListComponentGenerator &source) :
    Inherited(source)
{
}

DefaultInventoryListComponentGenerator::~DefaultInventoryListComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultInventoryListComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultInventoryListComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultInventoryListComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

