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

#include "OSGDefaultTreeComponentGenerator.h"
#include "Component/Tree/OSGTree.h"
#include "Component/Text/OSGLabel.h"
#include "Component/OSGComponent.h"

#include "Component/Container/OSGPanel.h"
#include "Layout/OSGBoxLayout.h"
#include "Border/OSGEmptyBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTreeComponentGenerator
A UI Default Tree ComponentGenerator. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultTreeComponentGenerator::getTreeComponent(TreePtr Parent, SharedFieldPtr Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
    //Setup the layout
    BoxLayoutPtr TheLayout = BoxLayout::create();
    beginEditCP(TheLayout, BoxLayout::OrientationFieldMask | BoxLayout::ComponentAlignmentFieldMask | BoxLayout::MinorAxisAlignmentFieldMask);
		TheLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
        TheLayout->setComponentAlignment(0.0f);
        TheLayout->setMinorAxisAlignment(0.5f);
    endEditCP(TheLayout, BoxLayout::OrientationFieldMask | BoxLayout::ComponentAlignmentFieldMask | BoxLayout::MinorAxisAlignmentFieldMask);

    //Get the text for the label
    std::string LabelText("");
    if(Value->getType() == SFString::getClassType())
    {
        LabelText = static_cast<SFString*>(Value.get())->getValue();
    }
    else
    {
        Value->getValueByStr(LabelText);
    }

    //Create the Label
    LabelPtr TheLabel = Label::Ptr::dcast(getNodeLabelPrototype()->shallowCopy());
    beginEditCP(TheLabel, Label::TextFieldMask | Label::TextColorFieldMask | Label::BorderFieldMask | Label::BackgroundFieldMask);
        if(IsSelected)
        {
            TheLabel->setTextColor(getSelectedTextColor());
            TheLabel->setBackground(getSelectedBackground());
            TheLabel->setBorder(getSelectedBorder());
        }
        else
        {
            TheLabel->setTextColor(getNonSelectedTextColor());
            TheLabel->setBackground(getNonSelectedBackground());
            TheLabel->setBorder(EmptyBorder::create());
        }
        TheLabel->setText(LabelText);
    endEditCP(TheLabel, Label::TextFieldMask | Label::TextColorFieldMask | Label::BorderFieldMask | Label::BackgroundFieldMask);


    //Create the panel, set its children and layout
    PanelPtr ThePanel = Panel::Ptr::dcast(getNodePanelPrototype()->shallowCopy());
    beginEditCP(ThePanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        ThePanel->setLayout(TheLayout);
        ThePanel->getChildren().push_back(TheLabel);
    endEditCP(ThePanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

    //TODO: Implement
    return ThePanel;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTreeComponentGenerator::DefaultTreeComponentGenerator(void) :
    Inherited()
{
}

DefaultTreeComponentGenerator::DefaultTreeComponentGenerator(const DefaultTreeComponentGenerator &source) :
    Inherited(source)
{
}

DefaultTreeComponentGenerator::~DefaultTreeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTreeComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultTreeComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTTREECOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTTREECOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTTREECOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

