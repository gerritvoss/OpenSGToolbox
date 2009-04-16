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

#include "Layer/OSGColorLayer.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/Text/OSGLabel.h"

#include "OSGDefaultUInt32TableCellRenderer.h"
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultUInt32TableCellRenderer
A DefaultUInt32TableCellRenderer.
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

ComponentPtr DefaultUInt32TableCellRenderer::getTableCellRendererComponent(TablePtr table, const boost::any& value, bool isSelected, bool hasFocus, UInt32 row, UInt32 column)
{
	if(value.empty()){
		return NullFC;
	}
	LabelPtr TheLabel = Label::create();
	beginEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
		std::string tempString;
        try
        {
            tempString = boost::lexical_cast<std::string>(boost::any_cast<UInt32>(value));
        }
        catch (boost::bad_any_cast &)
        {
            //Not a UInt32
        }
        catch (boost::bad_lexical_cast &)
        {
            //Bad Cast to string
        }
		TheLabel->setText(tempString);
		TheLabel->setPreferredSize(Vec2f(100,30));
	endEditCP(TheLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
	ColorLayerPtr tempBackground;
	tempBackground = ColorLayer::create();

	beginEditCP(TheLabel, Label::BackgroundsFieldMask);
		TheLabel->setBackgrounds(tempBackground);
	endEditCP(TheLabel, Label::BackgroundsFieldMask);

	beginEditCP(tempBackground, ColorLayer::ColorFieldMask);
		if(isSelected){
			tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		}
		else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		}
	endEditCP(tempBackground, ColorLayer::ColorFieldMask);

	if(hasFocus){
		LineBorderPtr tempBorder;

			tempBorder = LineBorder::create();
			beginEditCP(TheLabel, Label::BordersFieldMask);
				TheLabel->setBorders(tempBorder);
			endEditCP(TheLabel, Label::BordersFieldMask);

		beginEditCP(tempBorder, LineBorder::ColorFieldMask);
			tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
		endEditCP(tempBorder, LineBorder::ColorFieldMask);
	}
	else{
		EmptyBorderPtr tempBorder;

			tempBorder = EmptyBorder::create();
			beginEditCP(TheLabel, Label::BordersFieldMask);
				TheLabel->setBorders(tempBorder);
			endEditCP(TheLabel, Label::BordersFieldMask);
	}
	return Component::Ptr::dcast(TheLabel);
	
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultUInt32TableCellRenderer::DefaultUInt32TableCellRenderer(void)
{
}

DefaultUInt32TableCellRenderer::~DefaultUInt32TableCellRenderer(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

