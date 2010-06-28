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
    ConfirmButton->addActionListener(TheDialog->getConfirmButtonListener());

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

OSG_END_NAMESPACE
