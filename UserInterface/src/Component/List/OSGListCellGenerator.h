/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSG_UI_LIST_CELL_GENERATOR_H_
#define _OSG_UI_LIST_CELL_GENERATOR_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGUserInterfaceConfig.h"
#include "Component/OSGComponent.h"
#include "OSGList.h"

#include <OpenSG/OSGField.h>

OSG_BEGIN_NAMESPACE
	 
class OSG_USER_INTERFACE_CLASS_API ListCellGenerator
{
private:
protected:
public:
	virtual ComponentPtr getListCellGeneratorComponent(ListPtr list, Field* value, UInt32 index, bool isSelected, bool cellHasFocus) = 0;

};

typedef ListCellGenerator* ListCellGeneratorPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_LIST_CELL_GENERATOR_H_ */