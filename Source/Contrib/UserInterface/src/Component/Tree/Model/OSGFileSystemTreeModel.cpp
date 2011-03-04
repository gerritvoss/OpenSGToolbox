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

#include "OSGFileSystemTreeModel.h"
#include <boost/filesystem/operations.hpp>
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFileSystemTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGFileSystemTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FileSystemTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

boost::any FileSystemTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
        BoostPath ThePath = boost::any_cast<BoostPath>(parent);

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

UInt32 FileSystemTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
        BoostPath ThePath = boost::any_cast<BoostPath>(parent);

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
        BoostPath ParentPath = boost::any_cast<BoostPath>(parent);
        BoostPath ChildPath = boost::any_cast<BoostPath>(child);

        if(!ParentPath.empty() &&
           boost::filesystem::exists(ParentPath))
        {
            boost::filesystem::directory_iterator end_iter;
            UInt32 Count(0);
            for ( boost::filesystem::directory_iterator dir_itr( ParentPath ); dir_itr != end_iter; ++dir_itr )
            {
                try
                {
                    if(boost::filesystem::equivalent(dir_itr->path(), ChildPath))
                    {
                        return Count;
                    }
                }
                catch(boost::filesystem::filesystem_error &)
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
    return boost::any(getInternalRoot());
}

bool FileSystemTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
        BoostPath ThePath = boost::any_cast<BoostPath>(node);

        return !boost::filesystem::is_directory(ThePath);
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

bool FileSystemTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        BoostPath LeftPath = boost::any_cast<BoostPath>(left);
        BoostPath RightPath = boost::any_cast<BoostPath>(right);

        return boost::filesystem::equivalent(LeftPath, RightPath);
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

void FileSystemTreeModel::setRoot(const BoostPath& root)
{
    setInternalRoot(root);
}

const BoostPath& FileSystemTreeModel::getRootFilePath(void) const
{
    return getInternalRoot();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FileSystemTreeModel::FileSystemTreeModel(void) :
    Inherited()
{
}

FileSystemTreeModel::FileSystemTreeModel(const FileSystemTreeModel &source) :
    Inherited(source)
{
}

FileSystemTreeModel::~FileSystemTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FileSystemTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & InternalRootFieldMask)
    {
        produceTreeStructureChanged(getRootPath(),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, getRoot()));
    }
}

void FileSystemTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FileSystemTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
