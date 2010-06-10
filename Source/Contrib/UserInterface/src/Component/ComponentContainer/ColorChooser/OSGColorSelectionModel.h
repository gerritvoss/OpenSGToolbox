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

#ifndef _OSG_UI_COLOR_SELECTION_MODEL_H_
#define _OSG_UI_COLOR_SELECTION_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGColor.h"
#include "OSGChangeListener.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ColorSelectionModel
{
private:
protected:
public:
	virtual EventConnection addChangeListener(ChangeListenerPtr Listener) = 0;
	virtual bool isChangeListenerAttached(ChangeListenerPtr Listener) const = 0;

	virtual void removeChangeListener(ChangeListenerPtr Listener) = 0;

	virtual Color4f getSelectedColor(void) const = 0;

	virtual void setSelectedColor(const Color4f& Value, bool isValueAdjusting) = 0;
};

typedef boost::shared_ptr<ColorSelectionModel> ColorSelectionModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_COLOR_SELECTION_MODEL_H_ */

