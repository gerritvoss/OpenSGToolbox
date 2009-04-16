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

#include "OSGFileSystemTreeModel.h"
#include <boost/filesystem/operations.hpp>
#include "Component/Tree/OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FileSystemTreeModel
A FileSystemTreeModel. 
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

boost::any FileSystemTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(parent);

        if(!ThePath.empty() &&
			boost::filesystem::exists(ThePath))
        {
			boost::filesystem::directory_iterator end_iter;
			UInt32 Count(0);
			for ( boost::filesystem::directory_iterator dir_itr( ThePath ); dir_itr != end_iter; ++dir_itr )
			{
				if(Count == index)
				{
					return boost::any(dir_itr->path());
				}
				++Count;
			}
        }
        return boost::any();
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

boost::any FileSystemTreeModel::getParent(const boost::any& node) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(node);

        if(!ThePath.empty() || 
            boost::filesystem::equivalent(ThePath, _Root))
        {
            return boost::any(ThePath.parent_path());
        }

    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

UInt32 FileSystemTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(parent);

		UInt32 Count(0);
        if(!ThePath.empty() &&
			boost::filesystem::exists(ThePath))
        {
			boost::filesystem::directory_iterator end_iter;
			for ( boost::filesystem::directory_iterator dir_itr( ThePath ); dir_itr != end_iter; ++dir_itr )
			{
				++Count;
			}
        }
        return Count;
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

UInt32 FileSystemTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    try
    {
		Path ParentPath = boost::any_cast<Path>(parent);
		Path ChildPath = boost::any_cast<Path>(child);

        if(!ParentPath.empty() &&
			boost::filesystem::exists(ParentPath))
        {
			boost::filesystem::directory_iterator end_iter;
			UInt32 Count(0);
			for ( boost::filesystem::directory_iterator dir_itr( ParentPath ); dir_itr != end_iter; ++dir_itr )
			{
				if(boost::filesystem::equivalent(dir_itr->path(), ChildPath))
				{
					return Count;
				}
				++Count;
			}
        }
        return 0;
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

boost::any FileSystemTreeModel::getRoot(void) const
{
    return boost::any(_Root);
}

bool FileSystemTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(node);

		return !boost::filesystem::is_directory(ThePath);
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

void FileSystemTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
	//Do Nothing
}

void FileSystemTreeModel::setRoot(const Path& root)
{
    _Root = root;
	produceTreeStructureChanged(getPath(_Root),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, boost::any(root)));
}

const Path& FileSystemTreeModel::getRootPath(void) const
{
    return _Root;
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

