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

#include "OSGDefaultTreeSelectionModel.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTreeSelectionModel
A DefaultTreeSelectionModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultTreeSelectionModel::addSelectionPath(TreePath path)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::addSelectionPaths(std::vector<TreePath> paths)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::clearSelection(void)
{
	//TODO: Implement
}

TreePath DefaultTreeSelectionModel::getLeadSelectionPath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

UInt32 DefaultTreeSelectionModel::getLeadSelectionRow(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 DefaultTreeSelectionModel::getMaxSelectionRow(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 DefaultTreeSelectionModel::getMinSelectionRow(void) const
{
	//TODO: Implement
	return 0;
}

TreeRowMapper DefaultTreeSelectionModel::getRowMapper(void) const
{
	//TODO: Implement
	return TreeRowMapper();
}

UInt32 DefaultTreeSelectionModel::getSelectionCount(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 DefaultTreeSelectionModel::getSelectionMode(void) const
{
	//TODO: Implement
	return 0;
}

TreePath DefaultTreeSelectionModel::getSelectionPath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

std::vector<TreePath> DefaultTreeSelectionModel::getSelectionPaths(void) const
{
	//TODO: Implement
	return std::vector<TreePath>();
}

std::vector<UInt32> DefaultTreeSelectionModel::getSelectionRows(void) const
{
	//TODO: Implement
	return std::vector<UInt32>();
}

bool DefaultTreeSelectionModel::isPathSelected(TreePath path) const
{
	//TODO: Implement
	return false;
}

bool DefaultTreeSelectionModel::isRowSelected(const UInt32& row) const
{
	//TODO: Implement
	return false;
}

bool DefaultTreeSelectionModel::isSelectionEmpty(void) const
{
	//TODO: Implement
	return false;
}

void DefaultTreeSelectionModel::removeSelectionPath(TreePath path)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::removeSelectionPaths(std::vector<TreePath> paths)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::resetRowSelection(void)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::setRowMapper(TreeRowMapper newMapper)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::setSelectionMode(const UInt32& mode)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::setSelectionPath(TreePath path)
{
	//TODO: Implement
}

void DefaultTreeSelectionModel::setSelectionPaths(std::vector<TreePath> paths)
{
	//TODO: Implement
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

