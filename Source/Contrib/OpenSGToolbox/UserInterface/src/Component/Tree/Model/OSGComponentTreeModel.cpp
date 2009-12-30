/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef OSG_COMPILEUSERINTERFACELIB
#define OSG_COMPILEUSERINTERFACELIB
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGComponentTreeModel.h"
#include "Component/OSGComponent.h"
#include "Component/Container/OSGContainer.h"
#include "Component/Tree/OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComponentTreeModel
A UI ComponentTreeModel.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentTreeModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

boost::any ComponentTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
		ContainerPtr TheContainer = ContainerPtr::dcast(boost::any_cast<ComponentPtr>(parent));
        if(TheContainer != NullFC &&
           TheContainer->getChildren().size() > index)
        {
            return boost::any(TheContainer->getChildren(index));
        }
        else
        {
            return boost::any();
        }
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

boost::any ComponentTreeModel::getParent(const boost::any& node) const
{
    try
    {
        ComponentPtr TheComponent = boost::any_cast<ComponentPtr>(node);
        if(TheComponent != NullFC &&
            TheComponent != getInternalRootComponent() &&
            TheComponent->getParentContainer() != NullFC)
        {
            return boost::any(ComponentPtr::dcast(TheComponent->getParentContainer()));
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

UInt32 ComponentTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
		ContainerPtr TheContainer = ContainerPtr::dcast(boost::any_cast<ComponentPtr>(parent));
        if(TheContainer != NullFC)
        {
            return TheContainer->getChildren().getSize();
        }
        else
        {
            return 0;
        }
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

UInt32 ComponentTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    try
    {
        ContainerPtr ParentContainer = ContainerPtr::dcast(boost::any_cast<ComponentPtr>(parent));
        ComponentPtr ChildComponent = boost::any_cast<ComponentPtr>(child);
        if(ParentContainer != NullFC &&
           ChildComponent  != NullFC)
        {
            return ParentContainer->getChildIndex(ChildComponent);
        }
        else
        {
            return 0;
        }
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

boost::any ComponentTreeModel::getRoot(void) const
{
    return boost::any(getInternalRootComponent());
}

bool ComponentTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
		ContainerPtr TheContainer = ContainerPtr::dcast(boost::any_cast<ComponentPtr>(node));
        return TheContainer == NullFC;
    }
    catch(boost::bad_any_cast &)
    {
        return true;
    }
}

void ComponentTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    try
    {
        ComponentPtr NewComponent = boost::any_cast<ComponentPtr>(newValue);
        ComponentPtr OldComponent = boost::any_cast<ComponentPtr>(path.getLastPathComponent());
        if(NewComponent != NullFC &&
           OldComponent  != NullFC &&
           NewComponent != OldComponent &&
           OldComponent->getParentContainer() != NullFC)
        {
            ContainerPtr ParentContainer(OldComponent->getParentContainer());
            Int32 ChildIndex(ParentContainer->getChildIndex(OldComponent));
            if(ChildIndex >= 0)
            {
                beginEditCP(ParentContainer, Container::ChildrenFieldMask);
                    ParentContainer->getChildren()[ChildIndex] = NewComponent;
                endEditCP(ParentContainer, Container::ChildrenFieldMask);
                produceTreeStructureChanged(path.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, newValue));
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
}

void ComponentTreeModel::setRoot(ComponentPtr root)
{
    beginEditCP(ComponentTreeModelPtr(this), InternalRootComponentFieldMask);
        setInternalRootComponent(root);
    endEditCP(ComponentTreeModelPtr(this), InternalRootComponentFieldMask);
}


bool ComponentTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        ComponentPtr LeftComponent = boost::any_cast<ComponentPtr>(left);
        ComponentPtr RightComponent = boost::any_cast<ComponentPtr>(right);

        return LeftComponent == RightComponent;
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}
/*----------------------- constructors & destructors ----------------------*/

ComponentTreeModel::ComponentTreeModel(void) :
    Inherited()
{
}

ComponentTreeModel::ComponentTreeModel(const ComponentTreeModel &source) :
    Inherited(source)
{
}

ComponentTreeModel::~ComponentTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentTreeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & InternalRootComponentFieldMask)
    {
        produceTreeStructureChanged(getPath(getInternalRootComponent()),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, boost::any(getInternalRootComponent())));
    }
}

void ComponentTreeModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComponentTreeModel NI" << std::endl;
}


OSG_END_NAMESPACE

