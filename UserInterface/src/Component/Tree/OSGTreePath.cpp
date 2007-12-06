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

#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TreePath
A TreePath. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SharedFieldPtr TreePath::getLastPathComponent(void) const
{
	//TODO: Implement
	return SharedFieldPtr();
}

TreePath TreePath::getParentPath(void) const
{
	//TODO: Implement
	return TreePath();
}

std::vector<SharedFieldPtr> TreePath::getPath(void)
{
	//TODO: Implement
	return std::vector<SharedFieldPtr>();
}

SharedFieldPtr TreePath::getPathComponent(const UInt32& element) const
{
	//TODO: Implement
	return SharedFieldPtr();
}

UInt32 TreePath::getPathCount(void) const
{
	//TODO: Implement
	return 0;
}

bool TreePath::isDescendant(TreePath aTreePath) const
{
	//TODO: Implement
	return false;
}

TreePath TreePath::pathByAddingChild(SharedFieldPtr child) const
{
	//TODO: Implement
	return TreePath();
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreePath::TreePath(SharedFieldPtr singlePath)
{
	//TODO: Implement
}

TreePath::TreePath(std::vector<SharedFieldPtr> path)
{
	//TODO: Implement
}

TreePath::TreePath(void)
{
	//TODO: Implement
}

TreePath::TreePath(std::vector<SharedFieldPtr> path, const UInt32& length)
{
	//TODO: Implement
}

TreePath::TreePath(TreePath parent, SharedFieldPtr lastElement)
{
	//TODO: Implement
}

/*----------------------------- class specific ----------------------------*/

bool TreePath::operator=(const TreePath& Right) const
{
	//TODO: Implement
	return false;
}

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

