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

#include "OSGComponentTreeModel.h"
#include "OSGComponent.h"
#include "OSGComponentContainer.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComponentTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

boost::any ComponentTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
		ComponentContainerRefPtr TheContainer = dynamic_pointer_cast<ComponentContainer>(boost::any_cast<ComponentWeakPtr>(parent));
        if(TheContainer != NULL &&
           TheContainer->getMFChildren()->size() > index)
        {
            return boost::any(ComponentRefPtr(TheContainer->getChildren(index)));
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
        ComponentRefPtr TheComponent = boost::any_cast<ComponentWeakPtr>(node);
        if(TheComponent != NULL &&
            TheComponent != getInternalRootComponent() &&
            TheComponent->getParentContainer() != NULL)
        {
            return boost::any(ComponentRefPtr(dynamic_cast<Component*>(TheComponent->getParentContainer())));
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
		ComponentContainerRefPtr TheContainer = dynamic_pointer_cast<ComponentContainer>(boost::any_cast<ComponentWeakPtr>(parent));
        if(TheContainer != NULL)
        {
            return TheContainer->getMFChildren()->getSize();
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
        ComponentContainerRefPtr ParentContainer = dynamic_pointer_cast<ComponentContainer>(boost::any_cast<ComponentWeakPtr>(parent));
        ComponentRefPtr ChildComponent = boost::any_cast<ComponentWeakPtr>(child);
        if(ParentContainer != NULL &&
           ChildComponent  != NULL)
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
    return boost::any(ComponentRefPtr(getInternalRootComponent()));
}

bool ComponentTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
		ComponentContainerRefPtr TheContainer = dynamic_pointer_cast<ComponentContainer>(boost::any_cast<ComponentWeakPtr>(node));
        return TheContainer == NULL;
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
        ComponentRefPtr NewComponent = boost::any_cast<ComponentWeakPtr>(newValue);
        ComponentRefPtr OldComponent = boost::any_cast<ComponentWeakPtr>(path.getLastPathComponent());
        if(NewComponent != NULL &&
           OldComponent  != NULL &&
           NewComponent != OldComponent &&
           OldComponent->getParentContainer() != NULL)
        {
            ComponentContainerRefPtr ParentContainer(OldComponent->getParentContainer());
            Int32 ChildIndex(ParentContainer->getChildIndex(OldComponent));
            if(ChildIndex >= 0)
            {
                (*ParentContainer->editMFChildren())[ChildIndex] = NewComponent;
                produceTreeStructureChanged(path.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, newValue));
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
}

void ComponentTreeModel::setRoot(ComponentRefPtr root)
{
    setInternalRootComponent(root);
}


bool ComponentTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        ComponentRefPtr LeftComponent = boost::any_cast<ComponentWeakPtr>(left);
        ComponentRefPtr RightComponent = boost::any_cast<ComponentWeakPtr>(right);

        return LeftComponent == RightComponent;
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void ComponentTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

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
