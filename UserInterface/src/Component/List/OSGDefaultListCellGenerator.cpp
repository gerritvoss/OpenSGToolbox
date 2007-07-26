/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "Background/OSGColorUIBackground.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/OSGLabel.h"

#include "OSGDefaultListCellGenerator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListCellGenerator
A DefaultListCellGenerator. 
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
ComponentPtr DefaultListCellGenerator::getListCellGeneratorComponent(ListPtr list, Field* value, UInt32 index, bool isSelected, bool cellHasFocus)
{
	if(value == NULL){
		return NullFC;
	}
	LabelPtr TheLabel = Label::create();
	beginEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
		std::string tempString;
		if(value->getType() == SFString::getClassType())
		{
			tempString = dynamic_cast<SFString*>(value)->getValue();
		}
		else
		{
			value->getValueByStr(tempString);
		}
		TheLabel->setText(tempString);
		TheLabel->setPreferredSize(Vec2s(100,30));
	endEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
	ColorUIBackgroundPtr tempBackground;
	if(TheLabel->getBackground()->getType() == ColorUIBackground::getClassType()){
		tempBackground = ColorUIBackground::Ptr::dcast(TheLabel->getBackground());
	}
	else{
		tempBackground = ColorUIBackground::create();
		beginEditCP(TheLabel, Label::BackgroundFieldMask);
			TheLabel->setBackground(tempBackground);
		endEditCP(TheLabel, Label::BackgroundFieldMask);
	}
	beginEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
		if(isSelected){
			tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		}
		else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		}
	endEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
	if(cellHasFocus){
		LineBorderPtr tempBorder;
		if(TheLabel->getBorder()->getType() == LineBorder::getClassType()){
			tempBorder = LineBorder::Ptr::dcast(TheLabel->getBorder());
		}
		else{
			tempBorder = LineBorder::create();
			beginEditCP(TheLabel, Label::BorderFieldMask);
				TheLabel->setBorder(tempBorder);
			endEditCP(TheLabel, Label::BorderFieldMask);
		}
		beginEditCP(tempBorder, LineBorder::ColorFieldMask);
			tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
		endEditCP(tempBorder, LineBorder::ColorFieldMask);
	}
	else{
		EmptyBorderPtr tempBorder;
		if(TheLabel->getBorder()->getType()==EmptyBorder::getClassType()){
			tempBorder = EmptyBorder::Ptr::dcast(TheLabel->getBorder());
		}
		else{
			tempBorder = EmptyBorder::create();
			beginEditCP(TheLabel, Label::BorderFieldMask);
				TheLabel->setBorder(tempBorder);
			endEditCP(TheLabel, Label::BorderFieldMask);
		}
	}
	return Component::Ptr::dcast(TheLabel);
	
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListCellGenerator::DefaultListCellGenerator(void)
{
}

DefaultListCellGenerator::~DefaultListCellGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

