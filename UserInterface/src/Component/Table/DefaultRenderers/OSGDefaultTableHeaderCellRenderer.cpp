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

#include "Border/OSGBevelBorder.h"
#include "Component/OSGLabel.h"

#include "OSGDefaultTableHeaderCellRenderer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTableHeaderCellRenderer
A DefaultTableHeaderCellRenderer.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultTableHeaderCellRenderer::getTableCellRendererComponent(TablePtr table, Field* value, bool isSelected, bool hasFocus, UInt32 row, UInt32 column)
{
	if(value == NULL){
		return NullFC;
	}
	BevelBorderPtr DefaultBorder = BevelBorder::create();
	beginEditCP(DefaultBorder);
		DefaultBorder->setRaised(true);
		DefaultBorder->setWidth(1);
		DefaultBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultBorder);

	LabelPtr TheLabel = Label::create();
	beginEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BorderFieldMask);
		std::string tempString;
		tempString = dynamic_cast<SFString*>(value)->getValue();
		TheLabel->setText(tempString);
		TheLabel->setPreferredSize(Vec2s(100,30));
		TheLabel->setBorder(DefaultBorder);
	endEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::BorderFieldMask);

	return Component::Ptr::dcast(TheLabel);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableHeaderCellRenderer::DefaultTableHeaderCellRenderer(void)
{
}

DefaultTableHeaderCellRenderer::~DefaultTableHeaderCellRenderer(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

