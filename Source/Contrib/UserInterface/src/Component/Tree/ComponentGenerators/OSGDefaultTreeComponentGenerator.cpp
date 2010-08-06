/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDefaultTreeComponentGenerator.h"
#include "OSGDefaultTreeComponentGenerator.h"
#include "OSGTree.h"
#include "OSGModelTreeNode.h"
#include "OSGLabel.h"
#include "OSGComponent.h"

#include "OSGPanel.h"
#include "OSGBoxLayout.h"
#include "OSGEmptyBorder.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTreeComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTreeComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr DefaultTreeComponentGenerator::getTreeComponent(Tree* const Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
    boost::any ValueToUse;
    try
    {
        ModelTreeNodeRefPtr TheNode = boost::any_cast<ModelTreeNodeRefPtr>(Value);
        if(TheNode != NULL)
        {
            ValueToUse = TheNode->getUserObject();
        }
        else
        {
            ValueToUse = Value;
        }
    }
    catch (boost::bad_any_cast &)
    {
        //Could not convert to ModelTreeNodeRefPtr
        ValueToUse = Value;
    }

    //Setup the layout
    /*BoxLayoutRefPtr TheLayout = BoxLayout::create();
		TheLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
        TheLayout->setComponentAlignment(0.5f);
        TheLayout->setMinorAxisAlignment(0.5f);
*/
    //Get the text for the label
    std::string LabelText("");
    try
    {
        LabelText = lexical_cast(ValueToUse);
    }
    catch (boost::bad_lexical_cast &)
    {
        //Could not convert to string
    }
    if(LabelText.empty())
    {
        LabelText = "[Unnamed]";
    }

    return getTreeComponentText(Parent, LabelText, IsSelected, Expanded, Leaf, Row, HasFocus);
}

ComponentTransitPtr DefaultTreeComponentGenerator::getTreeComponentText(Tree* const Parent, const std::string& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
    LabelRefPtr TheLabel = dynamic_pointer_cast<Label>(getNodeLabelPrototype()->shallowCopy());
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
        EmptyBorderUnrecPtr TheBorder(EmptyBorder::create());
        TheLabel->setBorders(TheBorder);
    }
    TheLabel->setText(Value);

    //Create the panel, set its children and layout
    /*PanelRefPtr ThePanel = dynamic_pointer_cast<Panel>(getNodePanelPrototype()->shallowCopy());


        ThePanel->setLayout(TheLayout);
        ThePanel->pushToChildren(TheLabel);*/

    return ComponentTransitPtr(TheLabel.get());
}

ComponentTransitPtr DefaultTreeComponentGenerator::getTreeExpandedComponent(Tree* const Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
{
    //If node is not a leaf expanded
    if(!Leaf)
    {
        UIDrawObjectCanvasRefPtr ExpandedCanvas;
        if(Expanded)
        {
            ExpandedCanvas = dynamic_pointer_cast<UIDrawObjectCanvas>(getExpandedDrawObjectPrototype()->shallowCopy());
        }
        else
        {
            ExpandedCanvas = dynamic_pointer_cast<UIDrawObjectCanvas>(getNotExpandedDrawObjectPrototype()->shallowCopy());
        }
        return ComponentTransitPtr(ExpandedCanvas.get());
    }
    return ComponentTransitPtr(NULL);
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

void DefaultTreeComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultTreeComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
