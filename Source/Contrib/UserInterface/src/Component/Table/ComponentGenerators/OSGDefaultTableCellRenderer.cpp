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

#include "OSGConfig.h"

#include "OSGColorLayer.h"
#include "OSGLineBorder.h"
#include "OSGEmptyBorder.h"
#include "OSGLabel.h"

#include "OSGDefaultTableCellRenderer.h"
#include "OSGTable.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DefaultTableCellRenderer
A DefaultTableCellRenderer.
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

ComponentTransitPtr DefaultTableCellRenderer::getTableCellRendererComponent(Table* const table, const boost::any& value, bool isSelected, bool hasFocus, UInt32 row, UInt32 column)
{
    if(value.empty()){
        return ComponentTransitPtr(NULL);
    }
    LabelRefPtr TheLabel = Label::create();
    TheLabel->setText("");
    TheLabel->setPreferredSize(Vec2f(100,30));
    ColorLayerRefPtr tempBackground;
    tempBackground = ColorLayer::create();

    TheLabel->setBackgrounds(tempBackground);

    if(isSelected){
        tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
    }
    else{
        tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
    }

    if(hasFocus){
        LineBorderRefPtr tempBorder;

        tempBorder = LineBorder::create();
        TheLabel->setBorders(tempBorder);

        tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
    }
    else{
        EmptyBorderRefPtr tempBorder;

        tempBorder = EmptyBorder::create();
        TheLabel->setBorders(tempBorder);
    }
    return ComponentTransitPtr(TheLabel.get());


}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableCellRenderer::DefaultTableCellRenderer(void)
{
}

DefaultTableCellRenderer::~DefaultTableCellRenderer(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

