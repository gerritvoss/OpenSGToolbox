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

#include "OSGBevelBorder.h"
#include "OSGLabel.h"

#include "OSGDefaultTableHeaderCellRenderer.h"
#include "OSGStringUtils.h"
#include "OSGTable.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DefaultTableHeaderCellRenderer
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

ComponentTransitPtr DefaultTableHeaderCellRenderer::getTableCellRendererComponent(Table* const table, const boost::any& value, bool isSelected, bool hasFocus, UInt32 row, UInt32 column)
{
    if(value.empty()){
        return ComponentTransitPtr(NULL);
    }
    BevelBorderRefPtr DefaultBorder = BevelBorder::create();
    DefaultBorder->setRaised(true);
    DefaultBorder->setWidth(1);
    DefaultBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    LabelRefPtr TheLabel = Label::create();
    std::string tempString;
    try
    {
        tempString = lexical_cast(value);
    }
    catch (boost::bad_lexical_cast &)
    {
        //Could not convert to string
    }
    TheLabel->setText(tempString);
    TheLabel->setPreferredSize(Vec2f(100,30));
    TheLabel->setBorders(DefaultBorder);

    return ComponentTransitPtr(TheLabel.get());
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

