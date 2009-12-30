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

#include "OSGDefaultMissionTreeComponentGenerator.h"

#include "Mission/OSGMission.h"

#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultMissionTreeComponentGenerator
A Default Mission Tree ComponentGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultMissionTreeComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultMissionTreeComponentGenerator::getTreeComponent(TreePtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
	LabelPtr TheLabel = Label::create();

	beginEditCP(TheLabel, Label::TextFieldMask | Label::TextColorsFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        if(IsSelected)
        {
            TheLabel->setTextColors(getSelectedTextColor());
            TheLabel->setBackgrounds(getSelectedBackground());
            TheLabel->setBorders(getSelectedBorder());
        }
        else
        {
            TheLabel->setTextColors(getNonSelectedTextColor());
            TheLabel->setBackgrounds(getNonSelectedBackground());
            TheLabel->setBorders(EmptyBorder::create());
        }
        TheLabel->setText(boost::any_cast<MissionPtr>(Value)->getDescription());
    endEditCP(TheLabel, Label::TextFieldMask | Label::TextColorsFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

    return TheLabel;
}

ComponentPtr DefaultMissionTreeComponentGenerator::getTreeExpandedComponent(TreePtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
    //If node is not a leaf expanded
   /* if(!Leaf)
    {
        UIDrawObjectCanvasPtr ExpandedCanvas;
        if(Expanded)
        {
            ExpandedCanvas = UIDrawObjectCanvas::Ptr::dcast(getExpandedDrawObjectPrototype()->shallowCopy());
        }
        else
        {
            ExpandedCanvas = UIDrawObjectCanvas::Ptr::dcast(getNotExpandedDrawObjectPrototype()->shallowCopy());
        }
        return ExpandedCanvas;
    }
    return NullFC;*/

	return getTreeComponent(Parent, Value, IsSelected, Expanded, Leaf, Row, HasFocus);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultMissionTreeComponentGenerator::DefaultMissionTreeComponentGenerator(void) :
    Inherited()
{
}

DefaultMissionTreeComponentGenerator::DefaultMissionTreeComponentGenerator(const DefaultMissionTreeComponentGenerator &source) :
    Inherited(source)
{
}

DefaultMissionTreeComponentGenerator::~DefaultMissionTreeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultMissionTreeComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultMissionTreeComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultMissionTreeComponentGenerator NI" << std::endl;
}


OSG_END_NAMESPACE

