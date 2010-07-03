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

#ifndef _OSG_UI_TABLE_CELL_RENDERER_H_
#define _OSG_UI_TABLE_CELL_RENDERER_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"
#include "OSGComponent.h"
#include "OSGTableFields.h"

#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE
	 
class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableCellRenderer
{
private:
protected:
public:
	virtual ComponentTransitPtr getTableCellRendererComponent(Table* const table, const boost::any& value, bool isSelected, bool hasFocus, UInt32 row, UInt32 column) = 0;

};

typedef boost::shared_ptr<TableCellRenderer> TableCellRendererPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TABLE_CELL_RENDERER_H_ */


