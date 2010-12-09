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

#include "OSGAbstractTreeModel.h"

#include <boost/bind.hpp>
#include "OSGTreeModelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void AbstractTreeModel::produceTreeNodeInserted(TreePath Parent, const boost::any& InsertedChild)
{
    //Produce an event for a created Tree Node
    boost::any ParentNode(Parent.getLastPathComponent());
    std::vector<UInt32> ChildIndicies(1, getIndexOfChild(ParentNode, InsertedChild));
    std::vector<boost::any> Children(1, getChild(ParentNode, ChildIndicies.front()));

    produceTreeNodesInserted(Parent, ChildIndicies, Children);
}

void AbstractTreeModel::produceTreeNodeRemoved(TreePath Parent, const boost::any& InsertedChild)
{
    //Produce an event for a created Tree Node
    boost::any ParentNode(Parent.getLastPathComponent());
    std::vector<UInt32> ChildIndicies/*(1, getIndexOfChild(ParentNode, InsertedChild))*/;
    std::vector<boost::any> Children/*(1, getChild(ParentNode, ChildIndicies.front()))*/;

    produceTreeNodesRemoved(Parent, ChildIndicies, Children);
}

void AbstractTreeModel::produceTreeNodeChanged(TreePath Parent, const boost::any& InsertedChild)
{
    //Produce an event for a created Tree Node
    boost::any ParentNode(Parent.getLastPathComponent());
    std::vector<UInt32> ChildIndicies(1, getIndexOfChild(ParentNode, InsertedChild));
    std::vector<boost::any> Children(1, getChild(ParentNode, ChildIndicies.front()));

    produceTreeNodesChanged(Parent, ChildIndicies, Children);
}

void AbstractTreeModel::produceTreeNodeWillBeRemoved(TreePath Parent, const boost::any& InsertedChild)
{
    //Produce an event for a created Tree Node
    boost::any ParentNode(Parent.getLastPathComponent());
    std::vector<UInt32> ChildIndicies(1, getIndexOfChild(ParentNode, InsertedChild));
    std::vector<boost::any> Children(1, getChild(ParentNode, ChildIndicies.front()));

    produceTreeNodesWillBeRemoved(Parent, ChildIndicies, Children);
}

void AbstractTreeModel::produceTreeNodesChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEventDetailsUnrecPtr Details = TreeModelEventDetails::create(this, getSystemTime(), Parent, ChildIndices, Children);

   Inherited::produceTreeNodesChanged(Details);
}

void AbstractTreeModel::produceTreeNodesInserted(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEventDetailsUnrecPtr Details = TreeModelEventDetails::create(this, getSystemTime(), Parent, ChildIndices, Children);

   Inherited::produceTreeNodesInserted(Details);
}

void AbstractTreeModel::produceTreeNodesWillBeRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEventDetailsUnrecPtr Details = TreeModelEventDetails::create(this, getSystemTime(), Parent, ChildIndices, Children);

   Inherited::produceTreeNodesWillBeRemoved(Details);
}

void AbstractTreeModel::produceTreeNodesRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEventDetailsUnrecPtr Details = TreeModelEventDetails::create(this, getSystemTime(), Parent, ChildIndices, Children);

   Inherited::produceTreeNodesRemoved(Details);
}

void AbstractTreeModel::produceTreeStructureChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEventDetailsUnrecPtr Details = TreeModelEventDetails::create(this, getSystemTime(), Parent, ChildIndices, Children);

   Inherited::produceTreeStructureChanged(Details);
}

/*----------------------- constructors & destructors ----------------------*/

AbstractTreeModel::AbstractTreeModel(void) :
    Inherited()
{
}

AbstractTreeModel::AbstractTreeModel(const AbstractTreeModel &source) :
    Inherited(source)
{
}

AbstractTreeModel::~AbstractTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
