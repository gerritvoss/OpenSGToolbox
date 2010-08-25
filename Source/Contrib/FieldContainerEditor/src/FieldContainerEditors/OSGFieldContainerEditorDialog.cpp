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

#include "OSGFieldContainerEditorDialog.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGButton.h"
#include "OSGScrollPanel.h"
#include "OSGUIDrawUtils.h"
#include "OSGFieldContainerTreeModel.h"
#include "OSGTree.h"
#include "OSGFieldContainerFieldPathComponentGenerator.h"
#include "OSGSplitPanel.h"
#include "OSGUIDrawingSurface.h"

OSG_BEGIN_NAMESPACE

DialogWindowTransitPtr createFCEditorDialog(FieldContainer* fc, 
                                            CommandManagerPtr CmdManager,
                                            const std::string& editorName)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();

    //Create the FieldEditorComponent
    FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(fc, CmdManager);
    ScrollPanelRefPtr EditorScrollPanel = ScrollPanel::create();
    EditorScrollPanel->setPreferredSize(Vec2f(300,400));
    EditorScrollPanel->setViewComponent(TheEditor);

    //Ok button
    ButtonRefPtr ConfirmButton = Button::create();
    ConfirmButton->setText("Ok");
    ConfirmButton->connectActionPerformed(boost::bind(&DialogWindow::handleConfirmButtonAction, TheDialog.get(), _1));

    SpringLayoutRefPtr DialogLayout = OSG::SpringLayout::create();
    
    //EditorScrollPanel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, EditorScrollPanel, 2, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, EditorScrollPanel, -15, SpringLayoutConstraints::NORTH_EDGE, ConfirmButton);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, EditorScrollPanel, 1, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, EditorScrollPanel, 2, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    
    //ConfirmButton
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ConfirmButton, -15, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, ConfirmButton, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);

    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(330.0f, 475.0f));
    TheDialog->pushToChildren(EditorScrollPanel);
    TheDialog->pushToChildren(ConfirmButton);

    return DialogWindowTransitPtr(TheDialog);
}

void setFCEditedContainer(DialogWindow* const dialog,
                         FieldContainer* const fc)
{
    if(dialog != NULL &&
       dialog->getMFChildren() > 0)
    {
        if(dialog->getChildren(0)->getType() == ScrollPanel::getClassType() &&
           dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent() != NULL &&
           dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent()->getType().isDerivedFrom(FieldContainerEditorComponent::getClassType()))
        {
            dynamic_cast<FieldContainerEditorComponent*>(dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent())->attachFieldContainer(fc);
        }
        else if(dialog->getChildren(0)->getType() == SplitPanel::getClassType() &&
           dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent() != NULL &&
           dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent()->getType() == ScrollPanel::getClassType() &&
           dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent() != NULL &&
           dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent()->getType().isDerivedFrom(FieldContainerEditorComponent::getClassType())
           )
        {
            dynamic_cast<FieldContainerEditorComponent*>(dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent())->attachFieldContainer(fc);
            dynamic_cast<FieldContainerTreeModel*>(
                dynamic_cast<Tree*>(
                    dynamic_cast<ScrollPanel*>(
                           dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMinComponent())->getViewComponent())->getModel())->setRoot(fc);
        }
    }
}

FieldContainer* getFCEditedContainer(DialogWindow* const dialog)
{
    if(dialog != NULL &&
       dialog->getMFChildren() > 0)
    {
        if(dialog->getChildren(0)->getType() == ScrollPanel::getClassType() &&
           dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent() != NULL &&
           dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent()->getType().isDerivedFrom(FieldContainerEditorComponent::getClassType()))
        {
            return dynamic_cast<FieldContainerEditorComponent*>(dynamic_cast<ScrollPanel*>(dialog->getChildren(0))->getViewComponent())->getAttachedFieldContainer();
        }
        else if(dialog->getChildren(0)->getType() == SplitPanel::getClassType() &&
           dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent() != NULL &&
           dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent()->getType() == ScrollPanel::getClassType() &&
           dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent() != NULL &&
           dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent()->getType().isDerivedFrom(FieldContainerEditorComponent::getClassType())
           )
        {
            return dynamic_cast<FieldContainerEditorComponent*>(dynamic_cast<ScrollPanel*>(dynamic_cast<SplitPanel*>(dialog->getChildren(0))->getMaxComponent())->getViewComponent())->getAttachedFieldContainer();
        }
    }
    return NULL;
}

DialogWindowUnrecPtr openFCEditorDialog(FieldContainer* fc, 
                                        CommandManagerPtr CmdManager,
                                        const std::string& editorName,
                                        UIDrawingSurfaceUnrecPtr DrawingSurface)
{
    DialogWindowUnrecPtr TheDialog = createFCEditorDialog(fc, CmdManager, editorName);

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), DrawingSurface->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setTitle(std::string("Edit ") + fc->getType().getCName());
    TheDialog->setAllwaysOnTop(true);
    TheDialog->setResizable(true);

    DrawingSurface->openWindow(TheDialog);

    return TheDialog;
}

void handleFCSelectionAdded(TreeSelectionEventDetails* const details,
                                Tree* const editorTree,
                                ScrollPanel* const editorScroll)
{
    boost::any SelectedComp(editorTree->getLastSelectedPathComponent());
    if(!SelectedComp.empty())
    {
        //Get the component
        try
        {
            FieldContainerTreeModel::ContainerFieldIdPair ThePair(boost::any_cast<FieldContainerTreeModel::ContainerFieldIdPair>(SelectedComp));

            if(ThePair._FieldID == 0)
            {
                FieldContainerEditorComponent* const editor = dynamic_cast<FieldContainerEditorComponent* const>(editorScroll->getViewComponent());
                //Check if the container is NULL
                if(ThePair._Container == NULL)
                {
                    editor->dettachFieldContainer();
                }
                else
                {
                    //Check if this editor is already the default editor for
                    //this type
                    if(*FieldContainerEditorFactory::the()->getDefaultEditorType(&ThePair._Container->getType()) != editor->getType())
                    {
                        //If not then create a default editor for this type
                        FieldContainerEditorComponentRecPtr NewEditor =
                            FieldContainerEditorFactory::the()->createDefaultEditor(ThePair._Container,
                                                                                    editor->getCommandManager());
                        editorScroll->setViewComponent(NewEditor);
                        //Attach the container to the editor
                        NewEditor->attachFieldContainer(ThePair._Container);
                    }
                    else
                    {
                        //Attach the container to the editor
                        editor->attachFieldContainer(ThePair._Container);
                    }
                }
            }
        }
        catch(boost::bad_any_cast &ex)
        {
            SWARNING << ex.what() << std::endl;
        }
    }
}

DialogWindowTransitPtr createFCTreeEditorDialog       (FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager,
                                                                                       const std::string& editorName)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();



    //Create the FieldEditorComponent
    FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(fc, CmdManager);
    ScrollPanelRefPtr EditorScrollPanel = ScrollPanel::create();
    EditorScrollPanel->setViewComponent(TheEditor);

    //Field Container Tree Model
    FieldContainerTreeModelRefPtr TheTreeModel = FieldContainerTreeModel::create();
    TheTreeModel->setRoot(fc);
    TheTreeModel->setShowInternalFields(true);
    TheTreeModel->setShowPtrFields(true);
    TheTreeModel->setShowDataFields(false);
    TheTreeModel->setShowParentPtrFields(false);
    TheTreeModel->setShowChildPtrFields(true);
    TheTreeModel->setShowAttachments(true);
    TheTreeModel->setShowCallbackFunctors(false);

    //Field Container Tree Component Generator
    FieldContainerFieldPathComponentGeneratorRefPtr TheTreeComponentGenerator = FieldContainerFieldPathComponentGenerator::create();

    //Create the Field Container Tree
    TreeRefPtr TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setRootVisible(true);
    TheTree->setModel(TheTreeModel);
    TheTree->setCellGenerator(TheTreeComponentGenerator);

    TheTree->getSelectionModel()->connectSelectionAdded(boost::bind(&handleFCSelectionAdded, _1,
        TheTree.get(),
        EditorScrollPanel.get()));
    //TheDialog->addTransientObject(boost::any(TheTreeEditorSelectionListener));

    ScrollPanelRefPtr TreeScrollPanel = ScrollPanel::create();
    TreeScrollPanel->setViewComponent(TheTree);

    //Ok button
    ButtonRefPtr ConfirmButton = Button::create();
    ConfirmButton->setText("Ok");
    ConfirmButton->connectActionPerformed(boost::bind(&DialogWindow::handleConfirmButtonAction, TheDialog.get(), _1));

    SpringLayoutRefPtr DialogLayout = OSG::SpringLayout::create();

    //SplitPanel
    SplitPanelRefPtr TheSplitPanel = SplitPanel::create();
    TheSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
    TheSplitPanel->setDividerPosition(0.4f);
    TheSplitPanel->setDividerSize(5.0f);
    TheSplitPanel->setMaxDividerPosition(0.8f);
    TheSplitPanel->setMinDividerPosition(0.2f);
    TheSplitPanel->setMinComponent(TreeScrollPanel);
    TheSplitPanel->setMaxComponent(EditorScrollPanel);
    
    //TreeScrollPanel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheSplitPanel, 2, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheSplitPanel, -15, SpringLayoutConstraints::NORTH_EDGE, ConfirmButton);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheSplitPanel, -2, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheSplitPanel, 2, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    
    //ConfirmButton
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ConfirmButton, -15, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, ConfirmButton, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);

    
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(750.0f, 600.0f));
    TheDialog->pushToChildren(TheSplitPanel);
    TheDialog->pushToChildren(ConfirmButton);

    return DialogWindowTransitPtr(TheDialog);
}

DialogWindowUnrecPtr openFCTreeEditorDialog(FieldContainer* fc, 
                                        CommandManagerPtr CmdManager,
                                        const std::string& editorName,
                                        UIDrawingSurfaceUnrecPtr DrawingSurface)
{
    DialogWindowUnrecPtr TheDialog = createFCTreeEditorDialog(fc, CmdManager, editorName);

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), DrawingSurface->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setTitle(std::string("Edit ") + fc->getType().getCName());
    TheDialog->setAllwaysOnTop(true);
    TheDialog->setResizable(true);

    DrawingSurface->openWindow(TheDialog);

    return TheDialog;
}

OSG_END_NAMESPACE
