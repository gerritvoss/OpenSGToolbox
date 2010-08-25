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

#include "OSGMultiFieldListEditComponentGenerator.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGButton.h"
#include "OSGMFieldListModel.h"
#include <boost/lexical_cast.hpp>
#include "OSGFieldEditorFactory.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGenericMultiFieldEditor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiFieldListEditComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiFieldListEditComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiFieldListEditComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr MultiFieldListEditComponentGenerator::getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

    MFieldListModel::MFieldIndexed MFieldValuePair;
    try
    {
        MFieldValuePair = boost::any_cast<MFieldListModel::MFieldIndexed>(Value);
    }
    catch(boost::bad_any_cast &)
    {
        return ComponentTransitPtr(NULL);
    }


    //The Editor
    FieldEditorComponentUnrecPtr TheEditor =
        FieldEditorFactory::the()->createSingleDefaultEditor(MFieldValuePair.first->getContainer(),
                                                             MFieldValuePair.first->getDescription()->getFieldId(),
                                                             _CmdManager,
                                                             MFieldValuePair.second);

    //Index Label
    LabelRefPtr IndexLabel;
    if(getShowIndex())
    {
        IndexLabel = Label::create();
        IndexLabel->setText(boost::lexical_cast<std::string>(MFieldValuePair.second)
                            + ":");
        IndexLabel->setPreferredSize(Vec2f(30.0f,24.0f));
    }

    //Insert Button
    ButtonRefPtr InsertButton = Button::create();
    InsertButton->setPreferredSize(Vec2f(13.0f,13.0f));
    InsertButton->setBorders(NULL);
    InsertButton->setBackgrounds(NULL);
    InsertButton->setText("+");
    InsertButton->setAlignment(Vec2f(0.5f,0.5f));
    InsertButton->connectActionPerformed(boost::bind(&MultiFieldListEditComponentGenerator::handleInsertButtonAction, 
                                                     this,
                                                     _1,
                                                     MFieldValuePair.first->getContainer(),
                                                     MFieldValuePair.first->getDescription()->getFieldId(),
                                                     MFieldValuePair.second));

    //Delete Button
    ButtonRefPtr DeleteButton = Button::create();
    DeleteButton->setPreferredSize(Vec2f(13.0f,13.0f));
    DeleteButton->setBorders(NULL);
    DeleteButton->setBackgrounds(NULL);
    DeleteButton->setText("-");
    DeleteButton->setAlignment(Vec2f(0.5f,0.5f));
    DeleteButton->connectActionPerformed(boost::bind(&MultiFieldListEditComponentGenerator::handleRemoveButtonAction, 
                                                     this,
                                                     _1,
                                                     MFieldValuePair.first->getContainer(),
                                                     MFieldValuePair.first->getDescription()->getFieldId(),
                                                     MFieldValuePair.second));

    //Layout
    PanelRefPtr ThePanel = Panel::createEmpty();
    SpringLayoutRefPtr PanelLayout = OSG::SpringLayout::create();

	//Insert Button Layout    
    PanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InsertButton, 0,
                               SpringLayoutConstraints::NORTH_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InsertButton, 0,
                               SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InsertButton, 0,
                               SpringLayoutConstraints::WEST_EDGE, ThePanel);

    //Delete Button Layout    
    PanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, DeleteButton, 0,
                               SpringLayoutConstraints::SOUTH_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DeleteButton, 1,
                               SpringLayoutConstraints::VERTICAL_CENTER_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DeleteButton, 0,
                               SpringLayoutConstraints::WEST_EDGE, ThePanel);

    if(getShowIndex())
    {
        //Index Label Layout    
        PanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, IndexLabel, 0,
                                   SpringLayoutConstraints::NORTH_EDGE, ThePanel);
        PanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, IndexLabel, 0,
                                   SpringLayoutConstraints::SOUTH_EDGE, ThePanel);
        PanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, IndexLabel, 1,
                                   SpringLayoutConstraints::EAST_EDGE, DeleteButton);
    }

	//Editor Layout    
    PanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheEditor, 0,
                               SpringLayoutConstraints::NORTH_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheEditor, 0,
                               SpringLayoutConstraints::SOUTH_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheEditor, 0,
                               SpringLayoutConstraints::EAST_EDGE, ThePanel);
    PanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheEditor, 1,
                               SpringLayoutConstraints::EAST_EDGE, IndexLabel);

    ThePanel->pushToChildren(InsertButton);
    ThePanel->pushToChildren(DeleteButton);
    if(getShowIndex())
    {
        ThePanel->pushToChildren(IndexLabel);
    }
    ThePanel->pushToChildren(TheEditor);
    ThePanel->setLayout(PanelLayout);


	return ComponentTransitPtr(ThePanel);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MultiFieldListEditComponentGenerator::handleRemoveButtonAction(EventDetails* const details,
                                                       FieldContainer* const fc,
                                                       UInt32 fieldID,
                                                       UInt32 index)
{
    GenericMultiFieldEditor::removeIndex(fc,
                                         fieldID,
                                         index,
                                         dynamic_cast<Component*>(details->getSource())->getParentWindow()->getParentDrawingSurface(),
                                         _CmdManager.get());
}

void MultiFieldListEditComponentGenerator::handleInsertButtonAction(EventDetails* const details,
                                                         FieldContainer* const fc,
                                                         UInt32 fieldID,
                                                         UInt32 index)
{
    GenericMultiFieldEditor::insertAtIndex(fc,
                                         fieldID,
                                         index,
                                         dynamic_cast<Component*>(details->getSource())->getParentWindow()->getParentDrawingSurface(),
                                         _CmdManager.get());
}

/*----------------------- constructors & destructors ----------------------*/

MultiFieldListEditComponentGenerator::MultiFieldListEditComponentGenerator(void) :
    Inherited()
{
}

MultiFieldListEditComponentGenerator::MultiFieldListEditComponentGenerator(const MultiFieldListEditComponentGenerator &source) :
    Inherited(source)
{
}

MultiFieldListEditComponentGenerator::~MultiFieldListEditComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiFieldListEditComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MultiFieldListEditComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiFieldListEditComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
