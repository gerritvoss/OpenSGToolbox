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

#include "Background/OSGEmptyUIBackground.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/Text/OSGLabel.h"

#include "OSGDefaultComboBoxRenderer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultComboBoxRenderer
A DefaultComboBoxRenderer. 
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
ComponentPtr DefaultComboBoxRenderer::getListCellRendererComponent(ListPtr list, SharedFieldPtr value, UInt32 index, bool isSelected, bool cellHasFocus)
{
	if(value == SharedFieldPtr()){
		return NullFC;
	}
	LabelPtr TheLabel = Label::create();
	beginEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
		std::string tempString;
		if(value->getType() == SFString::getClassType())
		{
            tempString = dynamic_cast<SFString*>(value.get())->getValue();
		}
		else
		{
			value->getValueByStr(tempString);
		}
		TheLabel->setText(tempString);
		TheLabel->setPreferredSize(Vec2s(100,30));
	endEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

	beginEditCP(TheLabel, Label::BackgroundFieldMask | Label::BorderFieldMask);
		TheLabel->setBackground(EmptyUIBackground::create());
				TheLabel->setBorder(EmptyBorder::create());
	endEditCP(TheLabel, Label::BackgroundFieldMask | Label::BorderFieldMask);

	return Component::Ptr::dcast(TheLabel);
	
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultComboBoxRenderer::DefaultComboBoxRenderer(void)
{
}

DefaultComboBoxRenderer::~DefaultComboBoxRenderer(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

