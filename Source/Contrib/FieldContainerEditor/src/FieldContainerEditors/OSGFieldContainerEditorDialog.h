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

#ifndef _OSGFIELDCONTAINEREDITORDIALOG_H_
#define _OSGFIELDCONTAINEREDITORDIALOG_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGDialogWindow.h"
#include "OSGCommandManager.h"

OSG_BEGIN_NAMESPACE

DialogWindowTransitPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING createDefaultFCEditorDialog(FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager);

DialogWindowTransitPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING createFCEditorDialog       (FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager,
                                                                                       const std::string& editorName = "Default");


DialogWindowUnrecPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING openDefaultFCEditorDialog(FieldContainer* fc, 
                                                                                   CommandManagerPtr CmdManager,
                                                                                   UIDrawingSurfaceUnrecPtr DrawingSurface);

DialogWindowUnrecPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING openFCEditorDialog(FieldContainer* fc, 
                                                                            CommandManagerPtr CmdManager,
                                                                            const std::string& editorName,
                                                                            UIDrawingSurfaceUnrecPtr DrawingSurface);


DialogWindowTransitPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING createFCTreeEditorDialog       (FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager,
                                                                                       const std::string& editorName = "Default");

DialogWindowTransitPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING createDefaultFCTreeEditorDialog(FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager);

DialogWindowUnrecPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING openFCTreeEditorDialog(FieldContainer* fc, 
                                                                            CommandManagerPtr CmdManager,
                                                                            const std::string& editorName,
                                                                            UIDrawingSurfaceUnrecPtr DrawingSurface);


DialogWindowUnrecPtr OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING openDefaultFCTreeEditorDialog(FieldContainer* fc, 
                                                                                   CommandManagerPtr CmdManager,
                                                                                   UIDrawingSurfaceUnrecPtr DrawingSurface);

FieldContainer OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING * getFCEditedContainer(DialogWindow* const dialog);

void OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING setFCEditedContainer(DialogWindow* const dialog,
                                                                     FieldContainer* const fc);

OSG_END_NAMESPACE

#include "OSGFieldContainerEditorDialog.inl"

#endif /* _OSGFIELDCONTAINEREDITORDIALOG_H_ */
