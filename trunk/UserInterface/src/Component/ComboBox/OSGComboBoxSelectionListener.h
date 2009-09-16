/*---------------------------------------------------------------------------*\
 *                            OpenSGUserInterface                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSG_UI_COMBOBOX_SELECTION_COMBOBOXENER_H_
#define _OSG_UI_COMBOBOX_SELECTION_COMBOBOXENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComboBoxSelectionEvent.h"

#include <OpenSG/Toolbox/OSGEventListener.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ComboBoxSelectionListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void selectionChanged(const ComboBoxSelectionEvent& e) = 0;
};

typedef ComboBoxSelectionListener* ComboBoxSelectionListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_COMBOBOX_SELECTION_COMBOBOXENER_H_ */
